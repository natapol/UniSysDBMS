/* 
   UniSysDB library
   Copyright (C) 2011 

   class Updater

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/


#include "query.h"

namespace unisys {
	
	
	Query::Query()
	{
		
	}
	
	Query::Query(Database * databaseHandlePt)
	{
		Query::databaseHandle = databaseHandlePt;
		Query::query = query;
	}
	
	Query & Query::setQuery(mongo::BSONObj const& query)
	{
		Query::query = mongo::Query(query);
	}
	
	Query & Query::setQuery(mongo::Query const& query)
	{
		Query::query = query;
	}
	
	Query & Query::setDbHandle(Database * databaseHandlePt)
	{
		Query::databaseHandle = databaseHandlePt;
	}
	
	Query & Query::sort(std::string const& field, int asc)
	{
		Query::query.sort(field, asc);
	}
	
	Query & Query::explain()
	{
		Query::query.explain();
	}
	
	Query & Query::where(const std::string &jscode)
	{
		Query::query.where(jscode);
	}
	
	std::string Query::toString() const
	{
		return Query::query.toString();
	}
	
	mongo::BSONObj Query::perform(const std::string &ns, int nToReturn, int nToSkip, 
		const mongo::BSONObj *fieldsToReturn, int queryOptions, int batchSize) throw (QueryError)
	{
		mongo::BSONArrayBuilder arrayTmp;
		
		std::string dbNS = (*databaseHandle).getDBName() + "." + ns;
		
		mongo::auto_ptr<mongo::DBClientCursor> cursor = (*databaseHandle).query(dbNS, Query::query, nToReturn, 
			nToSkip, fieldsToReturn, queryOptions, batchSize);
			
		while( cursor->more() ) {
			arrayTmp.append(cursor->next());
		}
		
		return arrayTmp.arr();
	}
	
	mongo::BSONObj Query::performOne(const std::string &ns, int nToReturn, int nToSkip, const mongo::BSONObj *fieldsToReturn, 
		int queryOptions, int batchSize) throw (QueryError)
	{
		std::string dbNS = (*databaseHandle).getDBName() + "." + ns;
		
		mongo::auto_ptr<mongo::DBClientCursor> cursor = (*databaseHandle).query(dbNS, Query::query, nToReturn, 
			nToSkip, fieldsToReturn, queryOptions, batchSize);
		if ( cursor->more() )
			return cursor->next();
		else
			return mongo::BSONObj();
	}
	
	mongo::BSONObj Query::queryById(const std::string &id) throw (QueryError)
	{
		Query::query = mongo::Query(BSON( "_id" << id ));
		return Query::performOne("node");
	}
	
	mongo::BSONObj Query::queryByRef(const std::string &id) throw (QueryError)
	{
		Query::query = BSON( "$or" << BSON_ARRAY( BSON("dataPrimarySource" << id) << BSON("dataXref.id" << id) ) );
		mongo::BSONObj fieldsToReturn = BSON("_id" << 1);
		
		return Query::perform("node", 0, 0, &fieldsToReturn);
	}
	
	bool Query::isRedundantcy(BioObject obj, bool strict) throw (QueryError)
	{
		bool redundant = false;
		
		std::string main = obj.getField("dataPrimarySource").toString();
		
		if ( strict ) {
			Query::query = mongo::Query(BSON( "$or" << BSON_ARRAY( BSON("dataPrimarySource" << main) << BSON("dataXref.id" << main) ) ));
		} else {
			Query::query = mongo::Query(BSON( "dataPrimarySource" << main ));
		}
		
		if ( !Query::performOne("node").isEmpty() )
			redundant = true;
		
		
		mongo::BSONObj beTmp = obj.getField("relation").Obj();
		
		mongo::BSONObjIterator i(beTmp);
		
		while ( i.more() ) {
			
			std::string id = i.next().Obj().getStringField("id");
			
			if ( strict ) {
				Query::query = mongo::Query(BSON( "$or" << BSON_ARRAY( BSON("dataPrimarySource" << id) << BSON("dataXref.id" << id) ) ));
			} else {
				Query::query = mongo::Query(BSON( "dataPrimarySource" << id ));
			}
			
			if ( !Query::performOne("node").isEmpty() )
				redundant = true;
		}
		
		return redundant;
	}
}

////////////g++ query.cpp database.cpp oboxmlBatchInsert.cpp updater.cpp updaterUpdate.cpp updaterRemove.cpp updaterInsert.cpp batchInsert.cpp ../parser/oboXML.cpp ../parser/stanza.cpp ../uni/*.cpp ../parser/xmlParser.cpp ../dataclass/*.cpp -lmongoclient -lboost_thread -lboost_filesystem -lboost_date_time -lboost_system -lboost_program_options -I/usr/include/mongo -I/data/Projects/UniSysDBLib/trunk -o test
//int
//main()
//{
//	unisys::Database c("test");
//	c.connect("129.16.106.203");
//	
//	unisys::Query q(&c);
//	std::cout << q.queryById("ontology", "unisys.obo:GO:0000001.000").toString() << std::endl;
//}

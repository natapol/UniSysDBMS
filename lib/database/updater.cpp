/* 
   UniSysDB library
   Copyright (C) 2011 

   class Updater

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/


#include "updater.h"

namespace unisys {

	Updater::Updater() { }
	
	Updater::Updater(Database * databaseHandlePt)
	{
		Updater::databaseHandle = databaseHandlePt;
	}
	
	void Updater::setDbHandle(Database * databaseHandlePt)
	{
		Updater::databaseHandle = databaseHandlePt;
	}
	
	IdRef Updater::idConverter(IdRef const& ref) throw (QueryError)
	{
		try {
			mongo::BSONObj get = (*Updater::databaseHandle).findOne( (*Updater::databaseHandle).dbname + ".idpair", 
				mongo::Query(BSON("_id" << ref.getId())) );
						
			if (!get.isEmpty()) {
				return IdRef(get.getStringField("internal"), ref.getNS());
			} else {
				throw QueryError("Id not found.");
			}
		} catch(mongo::DBException &e) {
			throw QueryError(e.what());
		}
	}
	
	IdRef Updater::idConverter(std::string const& ns, std::string const& id) throw (QueryError)
	{
		IdRef tmpRef(id, ns);
		return Updater::idConverter(tmpRef);
	}
	
	bool Updater::checkIdPair(BioObject obj, bool strict) const
	{
		std::string dbNS = (*databaseHandle).getDBName() + ".idpair";
		
		if (obj.hasField("dataPrimarySource")) {
			bool result = false;
			mongo::BSONObj beTmp = obj.getField("dataPrimarySource").Obj().copy();
		
			mongo::auto_ptr<mongo::DBClientCursor> cursor = (*databaseHandle).query(dbNS, BSON("_id" << beTmp.getStringField("id")));
			if ( cursor->more() ) {
				result = true;
			}
		
			if (strict && obj.hasField("dataXref")) {
				beTmp = obj.getField("dataXref").Obj();
				mongo::BSONObjIterator i(beTmp);
		
				while ( i.more() ) {
					mongo::BSONObj e = i.next().Obj();
					mongo::BSONObjBuilder tmp;
					mongo::auto_ptr<mongo::DBClientCursor> cursor = (*databaseHandle).query(dbNS, BSON("_id" << e.getStringField("id")));
					if ( cursor->more() ) {
						result = true;
					}
				}
				
				if (obj.hasField("interactionKey")) {
					std::string intKey = obj.getField("interactionKey").String();
					if (!intKey.empty()) {
						mongo::auto_ptr<mongo::DBClientCursor> cursor = (*databaseHandle).query(dbNS, BSON("_id" << beTmp.getStringField("id")));
						if ( cursor->more() ) {
							result = true;
						}
					}
				}
				
				if (obj.hasField("InChi")) {
					std::string inchiKey = obj.getField("InChi").String();
					if (!inchiKey.empty()) {
						mongo::auto_ptr<mongo::DBClientCursor> cursor = (*databaseHandle).query(dbNS, BSON("_id" << beTmp.getStringField("id")));
						if ( cursor->more() ) {
							result = true;
						}
					}
				}
			}
		
			return result;
		} else {
			throw DataError("dataPrimarySource field is missing");
		}
	}
	
//	void Updater::manageRelationField()
//	{
//		
//	}
	
}

/* 
   UniSysDB library
   Copyright (C) 2011 

   class Updater

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/


#include "updater.h"

namespace unisys {
	void Updater::update(std::string const& collectionNS, mongo::Query query, mongo::BSONObj bsonObj, bool upsert, bool multi) throw (UpdateError)
	{
		std::string ns = (*Updater::databaseHandle).dbname + "." + collectionNS;
		(*Updater::databaseHandle).update(ns, query, bsonObj, upsert, multi);
		
		std::string error = (*Updater::databaseHandle).getLastError();
		if( !error.empty() ) {
			throw UpdateError(error);
		}
	}
	
	//void Updater::updateIdPair(mongo::BSONObj const& bsonobj, bool isInsert) throw (UpdateError)
	//{
		//mongo::BSONObjIterator i(bsonobj);
		//std::string tmpResult;
		//while ( i.more() ) {
			//mongo::BSONElement element = i.next();
			//try {
				//Updater::insert("idpair", element.Obj());
			//}
			//catch (UpdateError &e) {
				//tmpResult += ",";
				//tmpResult += element.Obj().getStringField("_id");
			//}
		//}
		
		//if (!tmpResult.empty()) {
			//throw UpdateError(tmpResult.substr(1, tmpResult.length() - 1));
		//}
	//}
	
	//void Updater::updateRelationAdd(Object const& obj, bool upsert, bool multi) throw (UpdateError)
	//{
		//mongo::BSONObj bsonobj = obj.createRelationInsert();
		//mongo::BSONObjIterator i(bsonobj);
	
		//try {
			//while ( i.more() ) {
				//mongo::BSONObj e = i.next().Obj();
				//std::string ns = e.getStringField("ns");
				//std::string id = e.getObjectField("query").getStringField("_id");
				
				//mongo::Query query(BSON("_id" << Updater::idConverter(ns, id).getId())); // convert external id to internal
				//mongo::BSONObj inject = e.getObjectField("inject");
				//Updater::update(ns, query, inject, upsert, multi);
			//}
		//} catch (UpdateError &e) {
			////Updater::updateRelationDel(obj);
			//std::string errorString("Insert back relation ERROR with ");
			//errorString.append(e.what());
			//throw UpdateError(errorString);
		//}
	//}
	
	//void Updater::updateRelationDel(Object const& obj, bool isRemove, bool justOne, bool upsert, bool multi) throw (UpdateError)
	//{
		//mongo::BSONObj bsonobj = obj.createRelationRemove();
		//mongo::BSONObjIterator i(bsonobj.getObjectField("update"));
		
		//while ( i.more() ) {
			//mongo::BSONObj e = i.next().Obj();
			//std::string ns = e.getStringField("ns");
			//mongo::Query query(e.getObjectField("query"));
			//mongo::BSONObj inject = e.getObjectField("inject");
			//Updater::update(ns, query, inject, upsert, multi);
		//}
		
		
		//if (isRemove) {
			//mongo::BSONObjIterator j(bsonobj.getObjectField("remove"));
		
			//while ( j.more() ) {
				//mongo::BSONObj e = j.next().Obj();
				//std::string ns = e.getStringField("ns");
				//mongo::Query query(e.getObjectField("inject"));
				//Updater::remove(ns, query, justOne);
			//}
		//}
	//}
}

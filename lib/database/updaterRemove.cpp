/* 
   UniSysDB library
   Copyright (C) 2011 

   class Updater

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/


#include "updater.h"

namespace unisys {
	
	void Updater::remove(std::string const& collectionNS, mongo::Query q, bool justOne) throw (UpdateError)
	{
		std::string ns = (*Updater::databaseHandle).dbname + "." + collectionNS;
		(*Updater::databaseHandle).remove(ns, q, justOne);
		
		std::string error = (*Updater::databaseHandle).getLastError();
		if(!error.empty()) {
			throw UpdateError(error);
		}
	}
	
	
	
	void Updater::remove(std::string const& collectionNS, std::string const& id, bool removeRela, bool removeProduct) throw (UpdateError, QueryError)
	{
		Query query(Updater::databaseHandle);
		
		mongo::BSONObj object = query.queryById(id);
		
		if (object.isEmpty()) {
			throw QueryError("No data relate with this id");
		}
		if (removeRela) {
			try {
				Updater::remove("relation", mongo::Query("{source: \'" + id + "\'}"), 0);
				Updater::remove("relation", mongo::Query("{relationWith: \'" + id + "\'}"), 0);
			} catch (UpdateError &e) {
				Updater::insertRelation(BioObject(object));
				throw UpdateError("Cannot remove ralation document");
			}
		}
		
		try {
			Updater::remove("node", mongo::Query("{_id: \'" + id + "\'}"), 0);
		} catch (UpdateError &e) {
			Updater::insertRelation(BioObject(object));
			throw UpdateError("Cannot remove ralation document");
		}
	}
	
	void Updater::remove(std::string const& collectionNS, std::set<std::string> const& ids, bool removeRela, bool removeProduct) throw (UpdateError, QueryError)
	{
		std::set<std::string>::const_iterator cit;
		for (cit = ids.begin(); cit != ids.end(); cit++) {
			Updater::remove(collectionNS, *cit, removeRela, removeProduct);
		}
	}
	
	
}

///////////////g++ database.cpp updater.cpp updaterRemove.cpp updaterUpdate.cpp ../dataclass/*.cpp -lmongoclient -lboost_thread -lboost_filesystem -lboost_date_time -lboost_system -lboost_program_options -I/usr/include/mongo -I/data/Projects/UniSysDBLib/trunk -o test
//int main () {
//	unisys::Database c;
//	c.connect("localhost");
//	unisys::Updater u(&c);
//	u.remove("ins", "abc");
//}

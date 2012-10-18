/* 
   UniSysDB library
   Copyright (C) 2011 

   class Updater

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/


#include "updater.h"

namespace unisys {

	void Updater::insert(std::string const& collectionNS, mongo::BSONObj bsonObj) throw (UpdateError)
	{
		std::string ns = (*Updater::databaseHandle).dbname + "." + collectionNS;
		(*Updater::databaseHandle).insert(ns, bsonObj);
		
		std::string error = (*Updater::databaseHandle).getLastError();
		if(!error.empty()) {
			throw UpdateError(error);
		}
	}
	
	void Updater::insert(Tracking tracking) throw (UpdateError, DataError)
	{
		Updater::insert("tracking", tracking.toBSONObj());
	}
	
	void Updater::insertRelation(BioObject object) throw (UpdateError, DataError)
	{
		if (object.hasField("relation")) {
			mongo::BSONObj beTmp = object.getField("relation").Obj();
		
			mongo::BSONObjIterator i(beTmp);
		
			while ( i.more() ) {
				mongo::BSONObj e = i.next().Obj();
				Updater::insert("relation", e);
			}
		}
	}
	
	void Updater::insert(BioObject & object, bool strict) throw (UpdateError, DataError)
	{
		if (object.isValid()) {
			Updater::insert("node", object.toBSONObj());
			Updater::insert(object.createTrack());
			
			Updater::insertRelation(object);
			
			Updater::ensureIndexRelation();
			Updater::ensureIndexNode();
			
			if ( strcmp("SmallMolecule", object.getField("type").toString().c_str()) )
				Updater::ensureIndexChem();
			
		} else {
			throw DataError("Inserted data not valid");
		}
		
	}
	
}

/////////////////g++ updaterInsert.cpp database.cpp updater.cpp updaterUpdate.cpp updaterRemove.cpp query.cpp ../dataclass/*.cpp ../uni/uniString.cpp -lmongoclient -lboost_thread -lboost_filesystem -lboost_date_time -lboost_system -lboost_program_options -I/usr/include/mongo -I/data/Projects/UniSysDBLib/trunk -o test
//int main () {
//	unisys::Database c;
//	c.connect("localhost");
//	unisys::Updater u(&c);
//	
//	unisys::DNA test;
//	test.setLength(50000);
//	test.setMainName("1");
//	test.setDataPrimarySource(unisys::Xref("urn:miriam:ensembl:ENSG0000002"));
//	test.setComment("http://www.ensembl.org");
//	u.insert(test);
////	u.insert("ins", BSON("ref" << "588" << "_id" << "GO:0045165"));
//}

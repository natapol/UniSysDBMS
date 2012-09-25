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
	
	void Updater::insert(Ontology & ontology) throw (UpdateError, DataError)
	{
		Updater::updateRelationAdd(ontology);
		if (ontology.isValid()) {
			Updater::insert("ontology", ontology.toBSONObj());
			Updater::insert(ontology.createTrack());
		} else {
			throw DataError("Inserted data not valid");
		}
	}
	
	void Updater::insert(PhysicalEntity & pedata, bool strict) throw (UpdateError, DataError)
	{
		if (Updater::checkIdPair(pedata, strict)) {
			if (strict) {
				throw UpdateError("Strictly cross reference found.");
			}else {
				throw UpdateError("Cross refernce found.");
			}
		}
		
		// compare external id with id pair data
		try {
			Updater::updateRelationAdd(pedata);
		}
		catch (UpdateError &e) {
			throw DataError("Relation error");
		}
		
		if (pedata.isValid()) {
			Updater::insert("physicalentity", pedata.toBSONObj());
			Updater::insert(pedata.createTrack());
			Updater::updateIdPair(pedata.createIdPair(strict));
		} else {
			throw DataError("Inserted data not valid");
		}
		
		std::cout << "insert" << std::endl;
	}
	
	void Updater::insert(Interaction & intdata, bool strict) throw (UpdateError, DataError)
	{
		if (Updater::checkIdPair(intdata, strict)) {
			if (strict) {
				throw UpdateError("Strictly cross reference found.");
			}else {
				throw UpdateError("Cross refernce found.");
			}
		}
		
		try {
			Updater::updateRelationAdd(intdata);
		}
		catch (UpdateError &e) {
			throw DataError("Relation error");
		}
		
		intdata.setInteractionKey();
		
		if (intdata.isValid()) {
			Updater::insert("interaction", intdata.toBSONObj());
			Updater::insert(intdata.createTrack());
			Updater::updateIdPair(intdata.createIdPair(strict));
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

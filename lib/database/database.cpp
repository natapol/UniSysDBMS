/* 
   UniSysDB library
   Copyright (C) 2011 

   class Database

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/


#include "database.h"

namespace unisys {

	Database::Database(std::string const& dbname)
	{
		Database::dbname = dbname;
	}

	void Database::setDBName(std::string const& dbname)
	{
		Database::dbname = dbname;
	}

	std::string Database::getDBName()
	{
		return Database::dbname;
	}
	
	void Database::connect(std::string const& serverHostname)
	{
		try {
			mongo::DBClientConnection::connect(serverHostname);
		} catch(mongo::DBException &e) {
			throw ConnectionError();
		}
	}
	
	mongo::BSONObj Database::fetchDBRef(mongo::BSONObj const& bsonObj) throw (QueryError)
	{
		try {
			return Database::findOne(Database::dbname + "." + bsonObj.getStringField("$ref"), 
				mongo::Query(mongo::BSONObjBuilder().append("_id", bsonObj.getStringField("$id")).obj()));
		} catch(mongo::DBException &e) {
			throw QueryError(e.what());
		}
	}
}
//////g++ database.cpp -lmongoclient -lboost_thread -lboost_filesystem -lboost_system -lboost_program_options -I/usr/include/mongo -o test
//int main () {
//	unisys::Database c;
//	c.connect("aaaaaaaaaaaaa");
//	
//	std::cout << "aaaaaaaaaaaaaaaaaaa" << std::endl;
//	std::cout << c.fetchDBRef(BSON("$ref" << "obo" << "$id" << "GO:0045165")).toString() << std::endl;
//	exit(0);
//}

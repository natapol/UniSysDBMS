/* 
   UniSysDB library
   Copyright (C) 2011 

	Class OBO-XML

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

/** \file biopax.h
    \brief It contain BIOPAX class using for parsing 
	OWL (Web Ontology Language) format especially BIOPAX
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <vector>
#include "client/dbclient.h"
#include "exception/exception.h"

#ifndef _UNISYSDB_DATABASE_H_
#define _UNISYSDB_DATABASE_H_

namespace unisys {
	
	/** 
		\brief This class is a database handle class

		Database class is derived from mongo::DBClientConnection, used to handle the connection
		between client and database. In this derived class, there are some functions that specific
		to UniSysDB database data structure.
	*/
	class Database: public mongo::DBClientConnection {
	
		private:
			
			std::string dbname; ///< Database name, defualt is test
			
		public:
			
			friend class Updater;
			
			Database(std::string const& dbname = "test"); ///< Overloaded contructor with specific database name
			
			void connect(std::string const& serverHostname); ///< Overloaded interface of connection function
			
			void setDBName(std::string const& dbname); ///< Set or change database name
			
			std::string getDBName(); ///< Return database name
			/** 
				\brief Dereference boson database reference (DBRef)

				This function retreives bson database reference, which format is {"$ref": "collectionNS", "$id": "id"[, "$db": "databaseName"]},
				as an input and searches for the document that has "_id" as describe in DBRef from specified collection namespace.
				\param bsonObj boson object of DBRef
			*/
			mongo::BSONObj fetchDBRef(mongo::BSONObj const& bsonObj) throw (QueryError);
	};
}


#endif

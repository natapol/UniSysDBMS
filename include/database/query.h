/* 
   UniSysDB library
   Copyright (C) 2011 

	Class Updater and BatchUpdater

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

/** \file updater.h
    \brief It contain KGMLPlus and its subclass Graphic
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include "client/dbclient.h"
#include "database.h"
#include "dataclass/LitClass.h"
#include "dataclass/ObjClass.h"
#include "dataclass/DBClass.h"

#ifndef _UNISYSDB_QUERY_H_
#define _UNISYSDB_QUERY_H_
namespace unisys {
	
	class Query {
	
		private:
		
			Database * databaseHandle;
			
			mongo::Query query;
		
		public:
			
			Query();
			
			Query(Database * databaseHandlePt);
			
			Query & setQuery(mongo::Query const& query);
			
			Query & setQuery(mongo::BSONObj const& query);
			
			Query & setDbHandle(Database * databaseHandlePt);
			
			Query & sort(std::string const& field, int asc=1);
			
			Query & explain();
			
			Query & where(const std::string &jscode);
			
			std::string toString() const;
			
			mongo::BSONObj perform(const std::string &ns, int nToReturn=0, int nToSkip=0, const mongo::BSONObj *fieldsToReturn=0, 
				int queryOptions=0, int batchSize=0) throw (QueryError);
			
			mongo::BSONObj performOne(const std::string &ns, int nToReturn=0, int nToSkip=0, const mongo::BSONObj *fieldsToReturn=0, 
				int queryOptions=0, int batchSize=0) throw (QueryError);
				
			mongo::BSONObj queryById(const std::string &ns, const std::string &id) throw (QueryError);
	};
}
#endif

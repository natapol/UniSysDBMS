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
	
	void Updater::ensureIndex(std::string const& collectionNS, mongo::BSONObj bsonObj)
	{
		std::string ns = (*Updater::databaseHandle).dbname + "." + collectionNS;
		(*Updater::databaseHandle).ensureIndex(ns, bsonObj);
		
		std::string error = (*Updater::databaseHandle).getLastError();
		if(!error.empty()) {
			throw UpdateError(error);
		}
	}
	
	void Updater::ensureIndexRelation()
	{
		Updater::ensureIndex( "node", BSON() )
	}
	
	void Updater::ensureIndexNode()
	{
		Updater::ensureIndex( "relation", BSON() )
	}
}

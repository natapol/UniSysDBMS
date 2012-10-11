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
	
	void Updater::ensureIndex(std::string const& collectionNS, mongo::BSONObj keys, bool unique, 
				const string & name, bool cache, bool background, int v) throw (UpdateError)
	{
		std::string ns = (*Updater::databaseHandle).dbname + "." + collectionNS;
		(*Updater::databaseHandle).ensureIndex(ns, keys, unique, name, cache, background, v);
		
		std::string error = (*Updater::databaseHandle).getLastError();
		if(!error.empty()) {
			throw UpdateError(error);
		}
	}
	
	void Updater::ensureIndexRelation()
	{
		Updater::ensureIndex( "relation", BSON("source" << 1) );
		Updater::ensureIndex( "relation", BSON("relationWith" << 1) );
		Updater::ensureIndex( "relation", BSON("source" << 1 << "relationWith" << 1) );
	}
	
	void Updater::ensureIndexNode()
	{
		Updater::ensureIndex( "node", BSON("dataPrimarySource.id" << 1) );
		Updater::ensureIndex( "node", BSON("dataXref.id" << 1) );
	}
}

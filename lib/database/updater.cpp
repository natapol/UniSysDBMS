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
	
}

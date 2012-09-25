/* 
	UniSysDB library
	Copyright (C) 2011 

	class Tracking

	

	Author: Natapol Pornputtapong <natapol@chalmers.se>
*/
#include "DBClass.h"

namespace unisys {
	void Tracking::initField()
	{
		DataObj::addFieldSet("oid");
		DataObj::addFieldSet("activity");
		DataObj::addFieldSet("timeStamp");
	}
	
	Tracking::Tracking(mongo::BSONObj const& bsonObj)
	{
		Tracking::initField();
		DataObj::addWithCheck(bsonObj);
	}
	
	Tracking::Tracking(std::string const& objectID, std::string const& activity)
	{
		DataObj::genOID();
		DataObj::append("oid", objectID);
		DataObj::append("activity", activity);
		DataObj::appendTimeStamp("timeStamp");
	}
	
	std::string Tracking::toString() const
	{
		boost::posix_time::ptime tmp = boost::posix_time::from_time_t(Tracking::data.getIntField("timeStamp"));
		return "Target: " + std::string( Tracking::data.getStringField("oid") ) + " \"" + std::string( Tracking::data.getStringField("activity") ) + "\" [" 
			+ std::string( boost::posix_time::to_simple_string(tmp) ) + "]";
	}
}
///////////////////g++ tracking.cpp dataobject.cpp -lmongoclient -lboost_thread -lboost_system -lboost_filesystem -lboost_program_options -lboost_date_time -I/usr/include/mongo -I/data/Projects/UniSysDBLib/trunk -o test
//int main () {
//	mongo::BSONObj bosonTmp = BSON(mongo::GENOID << "oid" << "Test" << "activity" << "bla bla bla" << "timeStamp" << (long long)time(NULL));
//	unisys::Tracking abc(bosonTmp);
//	std::cout << abc.toBSONObj().toString() << std::endl;
//	std::cout << abc.toString() << std::endl;
//}

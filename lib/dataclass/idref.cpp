/* 
   UniSysDB library
   Copyright (C) 2011 

   class IdRef, PEIdRef, IntIdRef and OBOIdRef

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

#include "DBClass.h"

namespace unisys {

	void IdRef::initField()
	{
		DataObj::addFieldSet("$ref");
		DataObj::addFieldSet("$id");
	}
	
	IdRef::IdRef()
	{
		IdRef::initField();
	}
	
	IdRef::IdRef(mongo::BSONObj const& bsonObj)
	{
		IdRef::initField();
		DataObj::addWithCheck(bsonObj);
	}
	
	IdRef::IdRef(std::string const& DBId, std::string const& collectionNS)
	{
		IdRef::initField();
		IdRef::initMember(DBId, collectionNS);
	}
	
	void IdRef::initMember(std::string const& DBId, std::string const& collectionNS)
	{
		IdRef::data = mongo::BSONObj().copy();
		DataObj::append("$ref", collectionNS);
		DataObj::append("$id", DBId);
	}
	
	std::string IdRef::getId() const
	{
		return IdRef::data.getStringField("$id");
	}
	
	std::string IdRef::getNS() const
	{
		return IdRef::data.getStringField("$ref");
	}
	
	bool IdRef::isValid() const
	{
		if( strcmp(IdRef::data.getStringField("$id"), "") != 0 && 
			( strcmp(IdRef::data.getStringField("$ref"), "ontology") == 0 || strcmp(IdRef::data.getStringField("$ref"), "physicalentity") == 0 
				|| strcmp(IdRef::data.getStringField("$ref"), "interaction") == 0 ) )
			return true;
		else
			return false;
	}
	
//	mongo::BSONObj IdRef::fetch(Database & db) const
//	{
//		return db.fetchDBRef(IdRef::data);
//	}
//	
	
}
///////////////////c++ idref.cpp ../database/database.cpp dataobject.cpp -lmongoclient -lboost_thread -lboost_system -lboost_filesystem -lboost_program_options -I/usr/include/mongo -I/data/Projects/UniSysDBLib/trunk -o test
//int main () {
//	unisys::Database c;
//	c.connect("localhost");
//	
//	std::set<unisys::OntoIdRef> test;
//	unisys::OntoIdRef abc1 ("GO:0045165");
//	unisys::OntoIdRef abc2 ("GO:0045138");
//	test.insert(abc1);
//	test.insert(abc2);
//	std::set<unisys::OntoIdRef>::iterator it;
//	
//	for(it = test.begin(); it!= test.end(); it++)
//		std::cout << (*it).toString() << std::endl;

//	std::cout << abc1.toString() << std::endl;
//	std::cout << abc2.fetch(c).toString() << std::endl;
//	exit(0);
//}

/* 
   UniSysDB library
   Copyright (C) 2011-2012 

   class ontology

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

#include "ObjClass.h"

namespace unisys {

	void Ontology::initField()
	{
		DataObj::addFieldSet("term", true);
		DataObj::addFieldSet("definition", true);
		DataObj::addFieldSet("namespace", true);
	}
	
	Ontology::Ontology(): Object() { Ontology::initField(); }
	
	Ontology::Ontology(mongo::BSONObj const& bsonObj): Object()
	{
		Ontology::initField();
		DataObj::addWithCheck(bsonObj);
	}
	
	void Ontology::setTerm(std::string const& term)
	{
		DataObj::set("term", term);
	}
	
	void Ontology::setDefinition(std::string const& definition)
	{
		DataObj::set("definition", definition);
	}
	
	void Ontology::setNS(std::string const& ns)
	{
		DataObj::set("namespace", ns);
	}
	
}
////////g++ LitClass.cpp miriam.cpp idref.cpp dataobject.cpp ontology.cpp object.cpp ../uni/*.cpp ../database/database.cpp -lmongoclient -lboost_system -lboost_thread -lboost_filesystem -lboost_program_options -I/usr/include/mongo -I/data/Projects/UniSysDBLib/trunk -o test

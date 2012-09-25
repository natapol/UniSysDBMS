/* 
   UniSysDB library
   Copyright (C) 2011 

   class OBOXML

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/


#include "oboXML.h"

namespace unisys {

	OBOXML::OBOXML()
	{

	}

	OBOXML::OBOXML(std::string const& fileName)
	{
		XMLNode xMainNode = XMLNode::openFileHelper(fileName.c_str(), "obo");
	
		for (int i = 0; i < xMainNode.nChildNode(); i++) {
			XMLNode childNode = xMainNode.getChildNode(i).deepCopy();
			if (strcmp(childNode.getName(), "source") == 0) {
				OBOXML::source = childNode;
			} else if (strcmp(childNode.getName(), "header") == 0) {
				OBOXML::header = childNode;
			} else {
				Stanza stanza (childNode);
				OBOXML::stanzas.push_back(stanza);
			}
		}
	}


	std::vector<Stanza>::iterator OBOXML::stanzasBegin()
	{
		return OBOXML::stanzas.begin();
	}

	std::vector<Stanza>::iterator OBOXML::stanzasEnd()
	{
		return OBOXML::stanzas.end();
	}
	
	std::vector<Stanza>::const_iterator OBOXML::stanzasBegin() const
	{
		return OBOXML::stanzas.begin();
	}
	
	std::vector<Stanza>::const_iterator OBOXML::stanzasEnd() const
	{
		return OBOXML::stanzas.end();
	}
	
//	std::string getOntology() const
//	{
//		std::string tmpStr;
//		tmpStr = OBOXML::header.getChildNode("ontology").getText();
//		if () {
//			
//		}
//		return 
//	}
}
///////g++ -o test oboXML.cpp Stanza.cpp xmlParser.cpp -lmongoclient -lboost_thread -lboost_filesystem -lboost_program_options -I/usr/include/mongo -I/data/Projects/UniSysDBLib/trunk
//int main () {
//	OBOXML oboxml ("../sample/go_daily-termdb.obo-xml");
//	std::vector<Stanza>::iterator cit;
//	for (cit = oboxml.stanzasBegin(); cit != oboxml.stanzasEnd(); cit++) {
//		std::cout << (*cit).getType() << std::endl;
//		std::cout << (*cit).getId() << std::endl;
//		std::cout << (*cit).getName() << std::endl;
//		std::cout << (*cit).toOBOBSONObj().toString() << std::endl;
//	}
//	exit(0);
//}

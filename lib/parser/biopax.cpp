/* 
   UniSysDB library
   Copyright (C) 2011 

   class BIOPAX

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/


#include "biopax.h"

namespace unisys {
	BIOPAX2::BIOPAX2()
	{
		
	}
	
	BIOPAX2::BIOPAX2(std::string fileName)
	{
		BIOPAX2::biopax = XMLNode::openFileHelper(fileName.c_str(), "rdf:RDF");
		
		for (int i = 0; i < BIOPAX2::biopax.nChildNode(); i++) {
			XMLNode tmpNode = BIOPAX2::biopax.getChildNode(i);
			if (strcmp("owl:Ontology", tmpNode.getName()) != 0) {
				BIOPAX_obj tmpBioObj(tmpNode);
				BIOPAX2::objects.insert(std::pair<std::string, BIOPAX_obj>(tmpBioObj.getId(), tmpBioObj));
			}
		}
	}
	
	XMLNode BIOPAX2::getOWLNode() const
	{
		return BIOPAX2::biopax.getChildNode("owl:Ontology");
	}
	
	BIOPAX2::biopaxObjMap::const_iterator BIOPAX2::begin() const
	{
		return BIOPAX2::objects.begin();
	}
	
	BIOPAX2::biopaxObjMap::const_iterator BIOPAX2::end() const
	{
		return BIOPAX2::objects.end();
	}
	
//	XMLNode BIOPAX2::createBiologicalReactionData() const
//	{
//		XMLNode tmpNode = XMLNode::createXMLTopNode("biochemicalReaction");
//		
//		BIOPAX2::biopaxObjMap::const_iterator mapIt;
//		
//		for (mapIt = BIOPAX2::objects.begin(); mapIt != BIOPAX2::objects.end(); mapIt++) {
//			if ( mapIt->second.getType().compare("biochemicalReaction") ) {
//				
//				for ( int i = 0; i < mapIt->second.nChildNode(); i++ ) {
//					if ( strcmp(mapIt->second.getChildNode(i).getName(),"") == 0 ) {
//						
//					}
//				}
//				
//			}
//		}
//	}
	
	
}

//////////g++ biopax_new.cpp biopaxobj.cpp xmlParser.cpp -I/data/Projects/UniSysDBLib/trunk -I/usr/include/mongo -lboost_system -o test
//int main () {
//	unisys::BIOPAX2 abc("../sample/rhea-biopax.owl");
//	
//	exit(0);
//}

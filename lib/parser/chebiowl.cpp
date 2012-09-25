/* 
   UniSysDB library
   Copyright (C) 2011 

   class OBOXML

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/


#include "chebiowl.h"

namespace unisys {
	
	ChEBIOWL::ChEBIOWL()
	{
	
	}
	
	ChEBIOWL::ChEBIOWL(std::string const& filename)
	{
		ChEBIOWL::parse(filename);
	}
	
	void ChEBIOWL::parse(std::string const& filename)
	{
		XMLNode xml = XMLNode::parseFile(filename.c_str(), "rdf:RDF");
		
		for (int i = 0; i < xml.nChildNode(); i++) {
			std::string tagName = xml.getChildNode(i).getName();
			if (tagName.compare("owl:Ontology") == 0) {
				ChEBIOWL::owlOntology = xml.getChildNode(i).deepCopy();
			} else if (tagName.compare("owl:Class") == 0) {
				ChEBIOWL::classList.push_back(ChEBIOWLClass(xml.getChildNode(i)));
			}
		}
	}
	
	std::vector<ChEBIOWLClass> ChEBIOWL::getClassList() const
	{
		return ChEBIOWL::classList;
	}
	
	std::string ChEBIOWL::getVersion() const
	{
		return ChEBIOWL::owlOntology.getChildNode("owl:versionIRI").getText();
	}
	
	XMLNode ChEBIOWL::getFileAnnotation() const
	{
		return ChEBIOWL::owlOntology.deepCopy();
	}
}
//////////g++ -o test chebiowlclass.cpp chebiowl.cpp xmlParser.cpp -I/data/Projects/UniSysDBLib/trunk
//int main () {
//	unisys::ChEBIOWL tmp("/data/Databases/ChEBI/chebi.owl");
//	std::cout << tmp.getFileAnnotation().createXMLString() << std::endl;
//}

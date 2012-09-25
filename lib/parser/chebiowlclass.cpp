/* 
   UniSysDB library
   Copyright (C) 2011 

   class OBOXML

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/


#include "chebiowl.h"
#include <sstream>

namespace unisys {

	void ChEBIOWLClass::parseSubClassOf(XMLNode xml) throw (ParsingError)
	{
		try {
			std::string tmpStr;
		
			if (xml.nChildNode() == 0 && xml.nAttribute() > 0) {
				tmpStr = xml.getAttribute("rdf:resource");
				std::string resource = tmpStr.substr(tmpStr.rfind("/") + 1, tmpStr.length());
	//			std::cout << resource << std::endl;
				if (resource.find("_") != std::string::npos) resource.replace(resource.find("_"), 1, ":");
				ChEBIOWLClass::subClassOf["SecondaryId"].insert(resource);
			} else if (xml.nChildNode() == 1) {
				XMLNode tmpXML = xml.getChildNode(0);
			
				tmpStr = tmpXML.getChildNode("owl:onProperty", 0).getAttribute("rdf:resource");
				std::string propety = tmpStr.substr(tmpStr.rfind("#") + 1, tmpStr.length());
			
				tmpStr = tmpXML.getChildNode("owl:someValuesFrom", 0).getAttribute("rdf:resource");
				std::string resource = tmpStr.substr(tmpStr.rfind("/") + 1, tmpStr.length());
	//			std::cout << propety << " " << resource << std::endl;
				if (resource.find("_") != std::string::npos) resource.replace(resource.find("_"), 1, ":");
			
				ChEBIOWLClass::subClassOf[propety].insert(resource);
			}
		}
		catch (std::out_of_range &e) {
			throw ParsingError("CHEBI id parsing error");
		}
	}
	
	void ChEBIOWLClass::parseAnnotation(XMLNode xml) throw (ParsingError)
	{
		try {
			std::string name = xml.getName();
			std::string text = xml.getText();
	//		std::cout << name << " " << text << std::endl;
			ChEBIOWLClass::AnnotationProperties[name].insert(text);
		}
		catch (std::out_of_range &e) {
			throw ParsingError("CHEBI id parsing error");
		}
	}
	
	ChEBIOWLClass::ChEBIOWLClass()
	{
		
	}
	
	ChEBIOWLClass::ChEBIOWLClass(XMLNode xml)
	{
		ChEBIOWLClass::parse(xml);
	}
	
	void ChEBIOWLClass::parse(XMLNode xml) throw (ParsingError)
	{
		try {
			std::string tmpStr = xml.getAttribute("rdf:about");
			ChEBIOWLClass::chebiId = tmpStr.substr(tmpStr.rfind("/") + 1, tmpStr.length());
			ChEBIOWLClass::chebiId.replace(ChEBIOWLClass::chebiId.find("_"), 1, ":");
			for (int i = 0; i < xml.nChildNode(); i++) {
				std::string name = xml.getChildNode(i).getName();
				if (name.compare("rdfs:subClassOf") == 0) {
					ChEBIOWLClass::parseSubClassOf(xml.getChildNode(i));
				} else if (name.compare("rdfs:label") == 0) {
					ChEBIOWLClass::label = xml.getChildNode(i).getText();
				} else if (name.compare("InChI") == 0) {
					ChEBIOWLClass::inchi = xml.getChildNode(i).getText();
				} else if (name.compare("InChIKey") == 0) {
					ChEBIOWLClass::inchiKey = xml.getChildNode(i).getText();
				} else if (name.compare("SMILES") == 0) {
					ChEBIOWLClass::smiles = xml.getChildNode(i).getText();
				} else {
					ChEBIOWLClass::parseAnnotation(xml.getChildNode(i));
				}
			}
		}
		catch (std::out_of_range &e) {
			throw ParsingError("CHEBI id parsing error");
		}
	}
	
	std::string ChEBIOWLClass::getId() const
	{
		return ChEBIOWLClass::chebiId;
	}
	
	std::set<std::string> ChEBIOWLClass::getPropertyList() const
	{
		std::set<std::string> tmpSet;
		
		std::map<std::string, std::set<std::string> >::const_iterator mapCit;
		for (mapCit = ChEBIOWLClass::AnnotationProperties.begin(); mapCit != ChEBIOWLClass::AnnotationProperties.end(); mapCit++) {
			tmpSet.insert(mapCit->first);
		}
		
		return tmpSet;
	}
	
	std::string ChEBIOWLClass::getFormula() const
	{
		size_t start = ChEBIOWLClass::inchi.find("/") + 1;
		size_t length = ChEBIOWLClass::inchi.find("/", start + 1) - start;
		if (start != std::string::npos)
			return ChEBIOWLClass::inchi.substr(start, length);
		else
			return "";
	}
	
	std::string ChEBIOWLClass::getInChi() const
	{
		return ChEBIOWLClass::inchi;
	}
	
	std::string ChEBIOWLClass::getInChiKey() const
	{
		return ChEBIOWLClass::inchiKey;
	}
	
	std::string ChEBIOWLClass::getSMILES() const
	{
		return ChEBIOWLClass::smiles;
	}
	
	std::string ChEBIOWLClass::getLabel() const
	{
		return ChEBIOWLClass::label;
	}
	
	std::map<std::string, std::set<std::string> > ChEBIOWLClass::getSubClassOf() const
	{
		return ChEBIOWLClass::subClassOf;
	}
	
	std::map<std::string, std::set<std::string> > ChEBIOWLClass::getAnnotationProperties() const
	{
		return ChEBIOWLClass::AnnotationProperties;
	}
	
	std::set<std::string> ChEBIOWLClass::getSpSubClassOf(std::string const& subClassType) const
	{
		std::map<std::string, std::set<std::string> >::const_iterator cit = ChEBIOWLClass::subClassOf.find(subClassType);
		if (cit == ChEBIOWLClass::subClassOf.end())
			return std::set<std::string>();
		else
			return cit->second;
	}
	
	std::set<std::string> ChEBIOWLClass::getSpAnnotationProperty(std::string const& propertiesName) const
	{
		std::map<std::string, std::set<std::string> >::const_iterator cit = ChEBIOWLClass::AnnotationProperties.find(propertiesName);
		if (cit == ChEBIOWLClass::AnnotationProperties.end())
			return std::set<std::string>();
		else
			return cit->second;
	}
}

//////////g++ -o test chebiowlclass.cpp xmlParser.cpp -I/data/Projects/UniSysDBLib/trunk
//int main() {
//std::stringstream strStream;
//strStream << "<owl:Class rdf:about=\"http://purl.obolibrary.org/obo/CHEBI_10003\">";
//strStream << "<rdfs:label rdf:datatype=\"http://www.w3.org/2001/XMLSchema#string\">vistamycin</rdfs:label>";
//strStream << "<rdfs:subClassOf rdf:resource=\"http://purl.obolibrary.org/obo/CHEBI_22479\"/>";
//strStream << "<rdfs:subClassOf>";
//strStream << "<owl:Restriction>";
//strStream << "<owl:onProperty rdf:resource=\"http://purl.obolibrary.org/obo#is_enantiomer_of\"/>";
//strStream << "<owl:someValuesFrom rdf:resource=\"http://purl.obolibrary.org/obo/CHEBI_6714\"/>";
//strStream << "</owl:Restriction>";
//strStream << "</rdfs:subClassOf>";
//strStream << "<Synonym rdf:datatype=\"http://www.w3.org/2001/XMLSchema#string\">(1R,2R,3S,4R,6S)-4,6-diamino-3-hydroxy-2-(beta-D-ribofuranosyloxy)cyclohexyl 2,6-diamino-2,6-dideoxy-alpha-D-glucopyranoside</Synonym>";
//strStream << "<Synonym rdf:datatype=\"http://www.w3.org/2001/XMLSchema#string\">C17H34N4O10</Synonym>";
//strStream << "<InChI rdf:datatype=\"http://www.w3.org/2001/XMLSchema#string\">InChI=1S/C17H34N4O10/c18-2-6-10(24)12(26)8(21)16(28-6)30-14-5(20)1-4(19)9(23)15(14)31-17-13(27)11(25)7(3-22)29-17/h4-17,22-27H,1-3,18-21H2/t4-,5+,6-,7-,8-,9+,10-,11-,12-,13-,14-,15-,16-,17+/m1/s1</InChI>";
//strStream << "<InChIKey rdf:datatype=\"http://www.w3.org/2001/XMLSchema#string\">InChIKey=NSKGQURZWSPSBC-VVPCINPTSA-N</InChIKey>";
//strStream << "<xref rdf:datatype=\"http://www.w3.org/2001/XMLSchema#string\">KEGG COMPOUND:25546-65-0</xref>";
//strStream << "<xref rdf:datatype=\"http://www.w3.org/2001/XMLSchema#string\">KEGG COMPOUND:C01759</xref>";
//strStream << "<SMILES rdf:datatype=\"http://www.w3.org/2001/XMLSchema#string\">NC[C@H]1O[C@H](O[C@@H]2[C@@H](N)C[C@@H](N)[C@H](O)[C@H]2O[C@@H]2O[C@H](CO)[C@@H](O)[C@H]2O)[C@H](N)[C@@H](O)[C@@H]1O</SMILES>";
//strStream << "<Synonym rdf:datatype=\"http://www.w3.org/2001/XMLSchema#string\">Ribostamycin</Synonym>";
//strStream << "<Synonym rdf:datatype=\"http://www.w3.org/2001/XMLSchema#string\">Vistamycin</Synonym>";
//strStream << "</owl:Class>";
//std::string tmpStr = strStream.str();

//XMLNode testXML = XMLNode::parseString(tmpStr.c_str());

//unisys::ChEBIOWLClass testClass(testXML);

////Unisys::printCont(testClass.getSpAnnotationProperty("Synonym"));

//std::cout << testClass.getInChi() << std::endl;
//}

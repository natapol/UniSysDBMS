/* 
	UniSysDB library
	Copyright (C) 2011 

	Class ClassBean

	Compile: 	xmlParser.cpp

	Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

/** \file classbean.cpp
    \brief Implementtion file for ClassBean class
*/

#include "restBioPortal.h"

namespace unisys {
	
	ClassBean::ClassBean()
	{
	
	}
			
	ClassBean::ClassBean(XMLNode xml)
	{
		ClassBean::id = xml.getChildNode("id").getText();
		
		if (xml.nChildNode("fullId") > 0) ClassBean::fullId = xml.getChildNode("fullId").getText();
		
		if (xml.nChildNode("label") > 0) ClassBean::label = xml.getChildNode("label").getText();
		
		if (xml.nChildNode("type") > 0) ClassBean::type = xml.getChildNode("type").getText();
		
		if (xml.nChildNode("synonyms") > 0) {
			for (int i = 0; i < xml.getChildNode("synonyms").nChildNode(); i++) {
				ClassBean::synonyms.insert(xml.getChildNode("synonyms").getChildNode(i).getText());
			}
		}
		
		if (xml.nChildNode("definitions") > 0) {
			for (int i = 0; i < xml.getChildNode("definitions").nChildNode(); i++) {
				ClassBean::definitions.insert(xml.getChildNode("definitions").getChildNode(i).getText());
			}
		}
		
		if (xml.nChildNode("relations") > 0) {
			for (int i = 0; i < xml.getChildNode("relations").nChildNode(); i++) {
				XMLNode entryXML = xml.getChildNode("relations").getChildNode(i);
			
				ClassBean::relationStruct entry;
				
				entry.type = entryXML.getChildNode("string").getText();
				
			
				for (int j = 0; j < entryXML.getChildNode("list").nChildNode(); j++) {
					ClassBean tmpBean;
					if (strcmp(entryXML.getChildNode("list").getChildNode(j).getName(),"classBean") == 0) {
						tmpBean = ClassBean(entryXML.getChildNode("list").getChildNode(j));
						entry.list.insert(std::pair<std::string, unisys::ClassBean>(tmpBean.getId(), tmpBean));
					} else {
						entry.list.insert(std::pair<std::string, unisys::ClassBean>(entryXML.getChildNode("list").getChildNode(j).getText(), tmpBean));
					}
				}
			
				if (entryXML.nChildNode("int") > 0) {
					entry.count = atoi(entryXML.getChildNode("int").getText());
				} else {
					entry.count = entry.list.size();
				}
				
				ClassBean::relations.push_back(entry);
			}
		}
		
	}
	
	std::string ClassBean::getId() const
	{
		return ClassBean::id;
	}
	
	std::string ClassBean::getFullId() const
	{
		return ClassBean::fullId;
	}
	
	std::string ClassBean::getLabel() const
	{
		return ClassBean::label;
	}
	
	std::string ClassBean::getType() const
	{
		return ClassBean::type;
	}
	
	std::set<std::string> ClassBean::getSynonyms() const
	{
		return ClassBean::synonyms;
	}
	
	std::set<std::string> ClassBean::getDefinitions() const
	{
		return ClassBean::definitions;
	}
	
	std::vector<ClassBean::relationStruct> ClassBean::getRelations() const
	{
		return ClassBean::relations;
	}
	
	std::set<std::string> ClassBean::relationStruct::getIdList()
	{
		std::set<std::string> tmpSet;
		std::map<std::string, ClassBean>::iterator it;
		for (it = ClassBean::relationStruct::list.begin(); it != ClassBean::relationStruct::list.end(); it++) {
			tmpSet.insert(it->first);
		}
		
		return tmpSet;
	}
	
	
}

/////////////g++ classbean.cpp /data/Projects/UniSysDBLib/trunk/parser/xmlParser.cpp -I/data/Projects/UniSysDBLib/trunk -o test

//int main () {
//	
//	XMLNode xml = XMLNode::openFileHelper("1007.xml");
//	
//	unisys::ClassBean bean(xml.getChildNodeByPath("success/data/classBean"));
//	

//	std::vector<unisys::ClassBean::relationStruct> tmp = bean.getRelations();
//	std::vector<unisys::ClassBean::relationStruct>::iterator it;
//	for (it = tmp.begin(); it != tmp.end(); it++)
//		std::cout << it->type << "  " << it->count << std::endl;
////	std::cout <<  << std::endl;
//	
//	exit(0);
//}

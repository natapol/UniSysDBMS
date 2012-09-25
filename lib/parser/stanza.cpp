/* 
   UniSysDB library
   Copyright (C) 2011 

   class Stanza

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/


#include "oboXML.h"

using namespace unisys;

Stanza::Stanza()
{

}
		
Stanza::Stanza(XMLNode const& xmlnode)
{
	Stanza::xml = xmlnode;
}

std::string Stanza::getNS() const
{
	return Stanza::xml.getChildNode("namespace", 0).getText();;
}

std::string Stanza::getId() const
{
	return Stanza::xml.getChildNode("id", 0).getText();
}

std::string Stanza::getName() const
{
	return Stanza::xml.getChildNode("name", 0).getText();
}

std::string Stanza::getDefinition() const
{
	try {
		return Stanza::xml.getChildNode("def").getChildNode("defstr").getText();
	}
	catch (std::logic_error) {
		return "";
	}
	
}

bool Stanza::isObsolete() const
{
	if (Stanza::xml.getChildNode("is_obsolete").isEmpty()) {
		return false;
	} else if (strcmp(Stanza::xml.getChildNode("is_obsolete").getText(),"1")) {
		return true;
	} else {
		return false;
	}
}

std::map<std::string, std::set<std::string> > Stanza::getRelationship() const
{
	std::map<std::string, std::set<std::string> > tmpMap;
	for (int i = 0; i < Stanza::xml.nChildNode("is_a"); i++) {
		tmpMap["is_a"].insert(Stanza::xml.getChildNode("is_a", i).getText());
	}
	
	for (int i = 0; i < Stanza::xml.nChildNode("relationship"); i++) {
		XMLNode tmp = Stanza::xml.getChildNode("relationship", i);
		tmpMap[tmp.getChildNode("type").getText()].insert(tmp.getChildNode("to").getText());
	}
	return tmpMap;
}

XMLNode Stanza::toXML() const
{
	return Stanza::xml.deepCopy();
}



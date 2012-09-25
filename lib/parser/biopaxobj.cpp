/* 
   UniSysDB library
   Copyright (C) 2011 

   class BIOPAX_obj

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/


#include "biopax.h"

namespace unisys {

	BIOPAX_obj::BIOPAX_obj()
	{
	
	}
	
	BIOPAX_obj::BIOPAX_obj(XMLNode node)
	{
		BIOPAX_obj::object = node;
	}
	
	std::string BIOPAX_obj::getId() const
	{
		std::string id;
		if (BIOPAX_obj::object.getAttribute("rdf:about"))
			id = BIOPAX_obj::object.getAttribute("rdf:about");
		else
			id = BIOPAX_obj::object.getAttribute("rdf:ID");
			
		if (id[0] == '#') id.erase(0,1);
		return id;
	}
	
	std::string BIOPAX_obj::getType() const
	{
		return BIOPAX_obj::object.getName();
	}
	
	XMLNode BIOPAX_obj::getChildNode(int i) const
	{
		return BIOPAX_obj::object.getChildNode(i);
	}
	
	XMLNode BIOPAX_obj::getChildNode(std::string name, int i) const
	{
		return BIOPAX_obj::object.getChildNode(name.c_str(), i);
	}
	
	XMLNode BIOPAX_obj::getChildNode(std::string name) const
	{
		return BIOPAX_obj::object.getChildNode(name.c_str());
	}
	
	int BIOPAX_obj::nChildNode() const
	{
		return BIOPAX_obj::object.nChildNode();
	}
	
	int BIOPAX_obj::nChildNode(std::string name) const
	{
		return BIOPAX_obj::object.nChildNode(name.c_str());
	}
	
	std::string BIOPAX_obj::getPropertyValue(std::string name) const
	{
		return BIOPAX_obj::object.getAttribute(name.c_str());
	}
	
	XMLAttribute BIOPAX_obj::getAttribute(int i) const
	{
		return BIOPAX_obj::object.getAttribute(i);
	}
	
	std::string BIOPAX_obj::getAttributeValue(int i) const
	{
		return BIOPAX_obj::object.getAttributeValue(i);
	}
	
	std::string BIOPAX_obj::getAttributeName(int i) const
	{
		return BIOPAX_obj::object.getAttributeName(i);
	}
	
	int BIOPAX_obj::nAttribute() const
	{
		return BIOPAX_obj::object.nAttribute();
	}
	
}


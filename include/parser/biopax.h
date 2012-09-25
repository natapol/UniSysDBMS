/* 
   UniSysDB library
   Copyright (C) 2011 

	Class BIOPAX

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

/** \file biopax.h
    \brief It contain BIOPAX class using for parsing 
	OWL (Web Ontology Language) format especially BIOPAX
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <map>
#include <vector>
#include "xmlParser.h"

#ifndef _UNISYSDB_BIOPAX_H_
#define _UNISYSDB_BIOPAX_H_

namespace unisys {

	/** 
		\brief This class is used to parse OWL format
		
		some description.
	*/
	class BIOPAX_obj
	{
		private:
		
			XMLNode object;
		
		public:
		
			BIOPAX_obj(); ///< Defualt constructor
			
			BIOPAX_obj(XMLNode node);
			
			std::string getId() const;
			
			std::string getType() const;
			
			XMLNode getChildNode(int i=0) const;
			
			XMLNode getChildNode(std::string name, int i) const;
			
			XMLNode getChildNode(std::string name) const;
			
			int nChildNode() const;
			
			int nChildNode(std::string name) const;
			
			std::string getPropertyValue(std::string name) const;
			
			XMLAttribute getAttribute(int i=0) const;
			
			std::string getAttributeValue(int i=0) const;
			
			std::string getAttributeName(int i=0) const;
			
			int nAttribute() const;
	
	};
	
	/** 
		\brief This class is used to parse OWL format
		
		Data structure using to store information from Tag-Value pair line except; name and id tag
	*/
	class BIOPAX2
	{
		private:
		
			XMLNode biopax;
			
			std::map<std::string, BIOPAX_obj> objects; ///< All objects map with their ids
		
		public:
			
			typedef std::map<std::string, BIOPAX_obj> biopaxObjMap;
			
			BIOPAX2(); ///< Defualt constructor
			
			BIOPAX2(std::string fileName); ///< Constructor with fileName as parameter
			
			XMLNode getOWLNode() const;
			
			biopaxObjMap::const_iterator begin() const;
			
			biopaxObjMap::const_iterator end() const;
			
//			XMLNode createBiologicalReactionData() const;
	};
}
#endif

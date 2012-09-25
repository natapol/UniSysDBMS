/* 
   UniSysDB library
   Copyright (C) 2011 

	Class OBO-XML

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

/** \file oboXML.h
    \brief It contain OBOXML and Stanza class using for parsing 
	OBO-XML format
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <vector>
#include "client/dbclient.h" //mongodb lib
#include "parser/xmlParser.h" //unisysdb lib


#ifndef _UNISYSDB_OBOXML_H_
#define _UNISYSDB_OBOXML_H_

namespace unisys {
	/** 
		\brief This class is used to parse OWL format

		some description.
	*/
	class Stanza {
	
		private:
			XMLNode xml;
		
		public:
		
			Stanza();
		
			Stanza(XMLNode const& xmlnode);
		
			std::string getNS() const;
		
			std::string getId() const;
		
			std::string getName() const;
		
			std::string getDefinition() const;
			
			bool isObsolete() const;
			
			std::map<std::string, std::set<std::string> > getRelationship() const;
			
			XMLNode toXML() const;
		
	};

	/** 
		\brief This class is used to parse OWL format

		some description.
	*/

	class OBOXML {
	
		private:
			XMLNode source;
		
			XMLNode header;
		
			std::vector<Stanza> stanzas;
			
		public:
			
			OBOXML();
			
			OBOXML(std::string const& filename);
			
			std::vector<Stanza>::iterator stanzasBegin();
			
			std::vector<Stanza>::iterator stanzasEnd();
			
			std::vector<Stanza>::const_iterator stanzasBegin() const;
			
			std::vector<Stanza>::const_iterator stanzasEnd() const;
			
//			std::string getOntology() const;
	};
}
#endif

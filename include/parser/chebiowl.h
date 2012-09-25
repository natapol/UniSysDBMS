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
#include <set>
#include <map>
#include "parser/xmlParser.h"
#include "exception/exception.h"

#ifndef _UNISYSDB_CHEBIOWL_H_
#define _UNISYSDB_CHEBIOWL_H_

namespace unisys {
	
	/** 
		\brief To handle owl:class tag of ChEBI OWL format

		some description.
	*/
	class ChEBIOWLClass 
	{
		private:
			
			std::string chebiId; ///< ChEBI ID in /CHEBI:\d+/ format
			
			std::string label; ///< Name of ChEBI entity
			
			std::string inchi;
			
			std::string inchiKey;
			
			std::string smiles;
			
			std::map<std::string, std::set<std::string> > subClassOf; ///< Relationship tag
			
			std::map<std::string, std::set<std::string> > AnnotationProperties; ///< Annotation tag except InChi, InChiKey and SMILES
			
			void parseSubClassOf (XMLNode xml) throw (ParsingError); ///< Parsing SubClassOf tag
			
			void parseAnnotation (XMLNode xml) throw (ParsingError); ///< Parsing Annotation tag
			
		public:
			
			ChEBIOWLClass();
			
			ChEBIOWLClass(XMLNode xml);
			
			void parse(XMLNode xml) throw (ParsingError);
			
			std::string getId() const;
			
			std::map<std::string, std::set<std::string> > getSubClassOf() const;
			
			std::map<std::string, std::set<std::string> > getAnnotationProperties() const;
			
			std::set<std::string> getPropertyList() const;
			
			std::string getFormula() const;
			
			std::string getInChi() const;
			
			std::string getInChiKey() const;
			
			std::string getSMILES() const;
			
			std::string getLabel() const;
			
			std::set<std::string> getSpSubClassOf(std::string const& subClassType) const;
			
			std::set<std::string> getSpAnnotationProperty(std::string const& propertiesName) const;
			
	};
	
	/** 
		\brief Used to parse ChEBI OWL format

		some description.
	*/
	class ChEBIOWL 
	{
		private:
			
			XMLNode owlOntology; ///< Ontology tag with file information.
			
			std::vector<ChEBIOWLClass> classList; ///< vector of ChEBIOWLClass
			
		public:
			
			ChEBIOWL();
			
			ChEBIOWL(std::string const& filename);
			
			void parse(std::string const& filename);
			
			std::vector<ChEBIOWLClass> getClassList() const;
			
			std::string getVersion() const;
			
			XMLNode getFileAnnotation() const;
			
	};
}

#endif

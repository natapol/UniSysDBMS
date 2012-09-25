/* 
   UniSysDB library
   Copyright (C) 2011 

	Class 

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

/** \file kgml.h
    \brief It contain KGMLPlus and its subclass Graphic
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "soapOntologyQuerySoapBindingProxy.h" // get proxy. These two header files can only be included one time.
#include "OntologyQuerySoapBinding.nsmap" // import the generated namespace mapping table

namespace unisys {

	namespace soapOLS {
	
		std::string getVersion();
		/** 
			\brief Static member function to retrieve the unique URI from MIRIAM SOAP-based webservice

			\param name data collection type (examples: "uniprot", "ChEBI"; case insensitive)
			\param id identifier (examples: "GO:0045202", "P62158")
			\param type type of the URI the user wants to recover ('URN' or 'URL' default is 'URN')
	
		*/
		std::string getTermById(std::string const& id, std::string const& ontologyName = "GO");
		
	}
}

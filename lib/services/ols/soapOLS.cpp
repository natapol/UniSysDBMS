/* 
   UniSysDB library
   Copyright (C) 2011 

   class Miriam

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/
#include "soapOLS.h"

namespace unisys {

	std::string soapOLS::getVersion()
	{
		OntologyQuerySoapBindingProxy service;
		
		_ns1__getVersion input;
		_ns1__getVersionResponse output;
		
		if (service.getVersion(& input, & output) == SOAP_OK) {
			return output.getVersionReturn;
		} else {
			std::cerr << service.error << std::endl;
			return "";
		}
	}
	
	std::string soapOLS::getTermById(std::string const& id, std::string const& ontologyName)
	{
		OntologyQuerySoapBindingProxy service;
		
		_ns1__getTermById input;
		_ns1__getTermByIdResponse output;
		
		input.termId = id;
		input.ontologyName = ontologyName;
		
		

		if (service.getTermById(& input, & output) == SOAP_OK) {
			return output.getTermByIdReturn;
		} else {
			std::cerr << service.error << std::endl;
			return "";
		}
	}
	
}
//////wsdl2h http://www.ebi.ac.uk/ontology-lookup/OntologyQuery.wsdl > OLSWS.h
//////soapcpp2 -C -i -x -I/usr/share/gsoap/import OLSWS.h
//////g++ soapOLS.cpp soapOntologyQuerySoapBindingProxy.cpp soapC.cpp -lgsoap++ -o test
int main () {
//	std::cout << unisys::soapOLS::getVersion() << std::endl;
	std::cout << unisys::soapOLS::getTermById("CHEBI:60272", "CHEBI") << std::endl;
}

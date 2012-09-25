/* 
	UniSysDB library
	Copyright (C) 2011 

	Class restMiriam
	
	Compile: 	restMiriam.cpp ../rest/rest.cpp -lcurl

	Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

/** \file restMiriam.cpp
    \brief Implementtion file for restMiriam class
*/

#include "restMiriam.h"

namespace unisys {
	
	const std::string RestMiriam::baseURL = "http://www.ebi.ac.uk/miriamws/main/rest";
	
	RestMiriam::RestMiriam(){
	
	}
	
	std::vector<std::string> RestMiriam::resolve(std::string urn, bool getDeprecated) throw (RESTServiceError)
	{
		std::vector<std::string> output;
		
		std::string url = RestMiriam::baseURL + "/resolve/" + urn;
		
		RestMiriam::perform(url);
		XMLNode xmlResult = RestMiriam::getResultInXML().getChildNode("uris");
		
		for (int i = 0; i < xmlResult.nChildNode("uri"); i++) {
			XMLNode child = xmlResult.getChildNode(i);
			if (child.isAttributeSet("deprecated")) {
				if (getDeprecated)
					output.push_back(child.getText());
			} else {
				output.push_back(child.getText());
			}
		}
		
		return output;
	}

}

////////////g++ restMiriam.cpp ../rest/rest.cpp /data/Projects/UniSysDBLib/trunk/lib/parser/xmlParser.cpp -lcurl -I/data/Projects/UniSysDBLib/trunk/lib -I/data/Projects/UniSysDBLib/trunk/include -I/data/Projects/UniSysDBLib/trunk/include/parser -o test

//int main () {
//	unisys::REST::globalInit();
//	
//	
//	unisys::RestMiriam rest;
//	
//	std::vector<std::string> resolve = rest.resolve("urn:miriam:uniprot:P62158");
//	
//	for (int i = 0; i < resolve.size(); i++) {
//		std::cout << resolve[i] << std::endl;
//	}
//	
//	unisys::REST::globalClean();
//	exit(0);
//}

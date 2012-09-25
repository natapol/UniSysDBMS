/* 
	UniSysDB library
	Copyright (C) 2011 

	Class restBioPortal
	
	Compile: 	restBioPortalSearchResult.cpp restBioPortalResult.cpp xmlParser.cpp
				restBioPortalTermResult.cpp classbean.cpp rest.cpp -lcurl
   
	Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

/** \file restBioPortal.cpp
    \brief Implementtion file for restBioPortal class
*/

#include "restBioPortal.h"

namespace unisys {

//	const std::string apikey = "b65d2e41-2d75-4499-9b91-bdfcda29c2f1";
	
	const std::string RestBioPortal::baseURL = "http://rest.bioontology.org/bioportal";

	RestBioPortal::RestBioPortal()
	{
	
	}
	

	XMLNode RestBioPortal::listAllLastestOntologies(std::string const& apikey)
	{
		std::string url = RestBioPortal::baseURL + "/ontologies?apikey=" + apikey;
		
		RestBioPortal::perform(url);
		return REST::getResultInXML();
	}
	
	XMLNode RestBioPortal::getSpecificOntology(std::string const& apikey, std::string const& ontologyVersionId)
	{
		std::string url = RestBioPortal::baseURL + "/ontologies/" + ontologyVersionId + "?apikey=" + apikey;
		
		RestBioPortal::perform(url);
		return REST::getResultInXML();
	}
	
	RestBioPortalSearchResult RestBioPortal::search(std::string const& apikey, std::string const& query, std::string const& ontologyids, 
		bool isexactmatch, bool includeproperties, int maxnumhits, bool includedefinitions)
	{
		char maxnumhitsVar[10];
		sprintf (maxnumhitsVar, "%d", maxnumhits);
		
		char isexactmatchVal;
		if (isexactmatch) isexactmatchVal = '1'; else isexactmatchVal = '0';
		
		char includepropertiesVal;
		if (includeproperties) includepropertiesVal = '1'; else includepropertiesVal = '0';
		
		std::string includedefinitionsVar;
		if (includedefinitions) includedefinitionsVar = "true"; else includedefinitionsVar = "false";
		
		
		std::string url = RestBioPortal::baseURL + "/search/" + REST::cleanString(query) + "?ontologyids=" + ontologyids + "&isexactmatch=" + isexactmatchVal 
							+ "&includeproperties=" + includepropertiesVal + "&maxnumhits=" + maxnumhitsVar + "&includedefinitions=" + includedefinitionsVar 
							+ "&apikey=" + apikey;
							
		RestBioPortal::perform(url);
		RestBioPortalSearchResult resultTmp(REST::getResultInXML());
		return resultTmp;
	}

	RestBioPortalTermResult RestBioPortal::term(std::string const& apikey, std::string const& ontology_virtual_id, std::string const& concept_id, 
		bool light, bool norelation, int maxnumchildren)
	{
		
		char lightVal;
		if(light) lightVal = '1'; else lightVal = '0';
		
		char norelationVal;
		if(norelation) norelationVal = '1'; else norelationVal = '0';
		/// /virtual/ontology/{ontology virtual id}/{concept id}
		std::string url = RestBioPortal::baseURL + "/virtual/ontology/" + ontology_virtual_id + "/" + concept_id + "?light=" + lightVal 
			+ "&norelation=" + norelationVal + "&apikey=" + apikey;
							
		
		char maxnumchildrenVal[10];
		if (maxnumchildren > -1) {
			sprintf(maxnumchildrenVal, "%d", maxnumchildren);
			url += "&maxnumchildren=";
			url += maxnumchildrenVal;
		}
		////
		RestBioPortal::perform(url);
		RestBioPortalTermResult resultTmp(REST::getResultInXML());
		return resultTmp;
		
	}
}

////////g++ restBioPortal.cpp restBioPortalSearchResult.cpp restBioPortalResult.cpp restBioPortalTermResult.cpp classbean.cpp ../rest/rest.cpp /data/Projects/UniSysDBLib/trunk/parser/xmlParser.cpp -lcurl -I/data/Projects/UniSysDBLib/trunk -o test

//int main () {
//	unisys::REST::globalInit();
//	
//	std::string apikey = "b65d2e41-2d75-4499-9b91-bdfcda29c2f1";
//	
//	unisys::RestBioPortal rest;
//	
////	std::cout << rest.listAllLastestOntologies(apikey).createXMLString() << std::endl;
////	std::cout << rest.getSpecificOntology(apikey, "46512").createXMLString() << std::endl;
////	unisys::RestBioPortalSearchResult searchResult = rest.search(apikey, "aluminium ion", "", true);
//	unisys::RestBioPortalTermResult searchResult = rest.term(apikey, "1007", "CHEBI:28984", false, false, 2);
//	unisys::ClassBean bean;
//	bean = searchResult.getClassBean();
//	
//	std::cout << bean.getType() << std::endl;

//	
//	unisys::REST::globalClean();
//	exit(0);
//}

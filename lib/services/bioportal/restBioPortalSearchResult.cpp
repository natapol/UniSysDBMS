/* 
	UniSysDB library
	Copyright (C) 2011 

	Class restBioPortalSearchResult

	Compile: 	restBioPortal.cpp restBioPortalResult.cpp rest.cpp xmlParser.cpp -lcurl

	Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

/** \file restBioPortalSearchResult.cpp
    \brief Implementtion file for restBioPortalSearchResult class
*/

#include "restBioPortal.h"

namespace unisys {

	RestBioPortalSearchResult::RestBioPortalSearchResult()
	{
	
	}
	
	RestBioPortalSearchResult::RestBioPortalSearchResult(XMLNode xml)
	{

		if (strcmp(xml.getChildNode(0).getName(), "success") == 0) {
			RestBioPortalSearchResult::accessedResource = xml.getChildNodeByPath("success/accessedResource").getText();
			RestBioPortalSearchResult::accessDate = xml.getChildNodeByPath("success/accessDate").getText();
			
			XMLNode searchResultListTmp = xml.getChildNodeByPath("success/data/page/contents/searchResultList");
			for (int i = 0; i < searchResultListTmp.nChildNode(); i++) {
				RestBioPortalSearchResult::searchResultList.push_back(searchResultListTmp.getChildNode(i).deepCopy());
			}
			
			XMLNode ontologyHitListTmp = xml.getChildNodeByPath("success/data/page/contents/ontologyHitList");
			for (int i = 0; i < ontologyHitListTmp.nChildNode(); i++) {
				RestBioPortalSearchResult::ontologyHitList.push_back(ontologyHitListTmp.getChildNode(i).deepCopy());
			}
			
		} else {
			RestBioPortalSearchResult::parseError(xml);
		}
	}
	
	
	size_t RestBioPortalSearchResult::nSearchResults() const
	{
		return RestBioPortalSearchResult::searchResultList.size();
	}
	
	std::vector<XMLNode> RestBioPortalSearchResult::getSearchResultList() const
	{
		return RestBioPortalSearchResult::searchResultList;
	}
	
	std::vector<XMLNode> RestBioPortalSearchResult::getOntologyHitList() const
	{
		return RestBioPortalSearchResult::ontologyHitList;
	}

}

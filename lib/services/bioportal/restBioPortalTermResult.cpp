/* 
	UniSysDB library
	Copyright (C) 2011 

	Class restBioPortalTermResult

	Compile: 	restBioPortal.cpp restBioPortalSearchResult.cpp restBioPortalResult.cpp 
				classbean.cpp rest.cpp -lcurl

	Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

/** \file restBioPortalTermResult.cpp
    \brief Implementtion file for restBioPortalTermResult class
*/

#include "restBioPortal.h"

namespace unisys {
	
	RestBioPortalTermResult::RestBioPortalTermResult()
	{
		
	}
			
	RestBioPortalTermResult::RestBioPortalTermResult(XMLNode xml)
	{
		if (strcmp(xml.getChildNode(0).getName(), "success") == 0) {
			RestBioPortalTermResult::accessedResource = xml.getChildNodeByPath("success/accessedResource").getText();
			RestBioPortalTermResult::accessDate = xml.getChildNodeByPath("success/accessDate").getText();
			RestBioPortalTermResult::classBean = ClassBean(xml.getChildNodeByPath("success/data/classBean"));
		} else {
			RestBioPortalTermResult::parseError(xml);
		}
	}
	
	ClassBean RestBioPortalTermResult::getClassBean() const
	{
		return RestBioPortalTermResult::classBean;
	}
}

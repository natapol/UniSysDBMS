/* 
	UniSysDB library
	Copyright (C) 2011 

	Class restBioPortalResult

	Compile: 	xmlParser.cpp rest.cpp -lcurl

	Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

/** \file restBioPortalResult.cpp
    \brief Implementtion file for restBioPortalResult class
*/

#include "restBioPortal.h"

namespace unisys {

	RestBioPortalResult::RestBioPortalResult()
	{
	
	}
	
	void RestBioPortalResult::parseError(XMLNode xml)
	{
		RestBioPortalResult::accessedResource = xml.getChildNodeByPath("errorStatus/accessedResource").getText();
		RestBioPortalResult::accessDate = xml.getChildNodeByPath("errorStatus/accessDate").getText();
		RestBioPortalResult::errorLongMessage = xml.getChildNodeByPath("errorStatus/longMessage").getText();
		RestBioPortalResult::errorCode = xml.getChildNodeByPath("errorStatus/errorCode").getText();
	}
	
	bool RestBioPortalResult::isError() const
	{
		if (RestBioPortalResult::errorCode.compare("") == 0)
			return false;
		else
			return true;
	}
	
	std::string RestBioPortalResult::getError(bool codeOnly) const
	{
		if (RestBioPortalResult::isError()) {
			if (codeOnly)
				return RestBioPortalResult::errorCode;
			else
				return RestBioPortalResult::errorCode + ": " + RestBioPortalResult::errorLongMessage;
		} else {
			return "";
		}
	}

	std::string RestBioPortalResult::getAccessedResource() const
	{
		return RestBioPortalResult::accessedResource;
	}
	
	std::string RestBioPortalResult::getAccessDate() const
	{
		return RestBioPortalResult::accessDate;
	}
}

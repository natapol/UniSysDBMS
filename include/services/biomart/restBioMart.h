/* 
	UniSysDB library
	Copyright (C) 2011 

	Class restBioPortal restBioPortalResult restBioPortalSearchResult restBioPortalTermResult and ClassBean

	Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

/** \file restBioPortal.h
    \brief BioPortal's REST service library
    
    This library contains search and term command.
    The serach command is used for retrieving the ontology that related with the query word from specific or non-specific ontology class.
    The term command is difference. This command is used for retrieving the information from BioPortal of exact ID from the specific ontology class
*/
#include <vector>
#include <set>
#include <map>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <sstream>
#include "services/rest/rest.h"

#ifndef _UNISYSDB_REST_BIOMART_H_
#define _UNISYSDB_REST_BIOMART_H_

#define BIOMART_VERSION "0.8"

namespace unisys {

	/** 
	\brief General class for taking care the response from BioPortal's REST service.

	*/
	class RestBioMartResult {
		private:
			
			XMLNode responseXML;
			
			std::string header;
			
		public:
			
			friend class RestBioMart;
			
			static std::string bioMartVersion()
			{
				return BIOMART_VERSION;
			}
			
			RestBioMartResult();
			
//			std::string getResultTab(std::string const& specific = "") const;
			
	};
	
	/** 
	\brief General class for taking care the response from BioPortal's REST service.

	*/
	class RestBioMart: public REST {
		
		private:
			
			std::string serviceURL;
			
		public:
			
			static std::string bioMartVersion()
			{
				return BIOMART_VERSION;
			}
			
			RestBioMart(); ///< Default constructor
			
			RestBioMart(std::string const& URL);
			
			void setServiceURL(std::string const& URL);
			
			std::string getServiceURL() const;
			
			XMLNode query(XMLNode queryXML);
			
	};
}
#endif

/*
	UniSysDB library
	Copyright (C) 2011

	Class restMiriam

	Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

/** \file restMiriam.h
    \brief Miriam's REST service library

    This library contains interfaces of Miriam's REST service
*/
#include <vector>
#include <set>
#include <map>
#include <string>
#include "services/rest/rest.h"

#ifndef _UNISYSDB_REST_MIRIAM_H_
#define _UNISYSDB_REST_MIRIAM_H_

namespace unisys {

	/**
		\brief General class for taking care the response from BioPortal's REST service.

	*/
	class RestMiriam: public REST {
		
		public:
			
			static const std::string baseURL;
			
			RestMiriam();
			
			/**
				\brief return URL from provided Miriam URN
				\param urn input miriam URN
				\param getDeprecated -
			*/
			std::vector<std::string> resolve(std::string urn, bool getDeprecated = false) throw (RESTServiceError);
	
	};

}
#endif

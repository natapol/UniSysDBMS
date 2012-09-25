/* 
   UniSysDB library
   Copyright (C) 2011 

	Class REST

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

/** \file rest.h
    \brief It contains the library to handle the REST service request and response
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <curl/curl.h>
#include "parser/xmlParser.h"
#include "exception/exception.h"

#ifndef _UNISYSDB_REST_H_
#define _UNISYSDB_REST_H_

namespace unisys {
	/** 
		\brief Used for managing the request and response of REST service.
		
		This class connects to REST service through the cURL library, but it has very limit capability when comparing with cURL library. 

	*/
	class REST {

		protected:
		
			static std::string buffer; ///< Static member function for getting results from static callback member function
			
			CURL * curlHandle; ///< cURL library handler
			
			CURLcode curlResult; ///< cURL library response handler
			
			std::string result; ///< The results of REST service in string
			
			XMLNode xmlResult; ///< The results of REST service in string
			
			bool isResponseError() throw (RESTServiceError);
			
		public:
		
			static void globalInit(); ///< Init function of cURL library. Just do it on time in one program.
			
			static void globalClean(); ///< Setting destructor of cURL library. Just do it on time in one program.
			
			static std::string cleanString(std::string const& str); ///< Used for clean the restrict charactors in string; like space, &, $, % etc.
			
			static size_t callback(void *ptr, size_t size, size_t count, FILE *data); ///< static member function for processing results from libcurl
		
			REST(); ///< Default constructor. Do the curl_easy_init and set some option to cURL library handler.
			
			~REST(); ///< Default destructor. Do the curl_easy_clean and release the memory of cURL library handler.
			
			std::string getResult();
			
			XMLNode getResultInXML() throw (ParsingError);
			
			void perform(std::string const& url) throw (RESTServiceError); ///< Perform the request with HEAD method to the service and take the response back.
			
			void performPOST(std::string const& url, std::string const& postFields) throw (RESTServiceError); ///< Perform the request with POST method to the service and take the response back.
			
			void performHTTPGET(std::string const& url) throw (RESTServiceError); ///< Perform the request with HTTPGET method to the service and take the response back.
			
			void print(); ///< Print out the value in REST::xmlResult. (Just for debugging)
	};
}
#endif

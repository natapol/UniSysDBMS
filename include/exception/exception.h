/* 
   UniSysDB library
   Copyright (C) 2011 

	Class exception

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

/** \file biopax.h
    \brief It contain BIOPAX class using for parsing 
	OWL (Web Ontology Language) format especially BIOPAX
*/

#include <exception>
#include <stdexcept>

#ifndef _UNISYSDB_EXCEPTION_H_
#define _UNISYSDB_EXCEPTION_H_

namespace unisys {
	
	enum dbStatus {
		DB_OK,
		DB_CANNOT_CONNECT,
		DB_CANNOT_INSERT
	};
	
	class UniSysError: public std::exception
	{
		public:
			std::string errorMsg;
			
			~UniSysError() throw() {}
	};
	
	class ConnectionError: public UniSysError
	{
		public:
			virtual const char* what() const throw()
			{
				return "cannot connect";
			}
	};
	
	class UpdateError: public UniSysError
	{
		public:
		
			UpdateError(std::string const& str) { errorMsg = str; }
			
			virtual const char* what() const throw()
			{
				return errorMsg.c_str();
			}
			
	};
	
	class QueryError: public UniSysError
	{
		public:
		
			QueryError(std::string const& str) { errorMsg = str; }
			
			virtual const char* what() const throw()
			{
				return errorMsg.c_str();
			}
			
	};
	
	class DataError: public UniSysError
	{
		public:
		
			DataError(std::string const& str) { errorMsg = str; }
			
			virtual const char* what() const throw()
			{
				return errorMsg.c_str();
			}
			
	};
	
	class ParsingError: public UniSysError
	{
		public:
		
			ParsingError(std::string const& str) { errorMsg = str; }
			
			virtual const char* what() const throw()
			{
				return errorMsg.c_str();
			}
			
	};
	
	class RESTServiceError: public UniSysError
	{
		public:
		
			RESTServiceError(std::string const& str) { errorMsg = str; }
			
			virtual const char* what() const throw()
			{
				return errorMsg.c_str();
			}
			
	};
}

#endif

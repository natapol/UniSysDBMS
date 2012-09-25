/* 
	UniSysDB library
	Copyright (C) 2011 

	Class REST
	
	Compile: xmlParser.cpp -lcurl
	
	Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

/** \file rest.cpp
    \brief It contain KGMLPlus and its subclass Graphic
*/

#include "rest.h"
#include <sstream>
namespace unisys {
	
	std::string REST::buffer = "";
	
	void REST::globalInit()
	{
		curl_global_init(CURL_GLOBAL_ALL);
	}
	
	void REST::globalClean()
	{
		curl_global_cleanup();
	}
	
	std::string REST::cleanString(std::string const& str)
	{
		std::string tmpStr;
		
		for (size_t i = 0; i < str.length(); i++) {
			switch (str.at(i))
			{
				case '\t': tmpStr.append("%09"); break;
				case '\n': tmpStr.append("%0A"); break;
				case ' ': tmpStr.append("%20"); break;
				case '!': tmpStr.append("%21"); break;
				case '"': tmpStr.append("%22"); break;
				case '$': tmpStr.append("%24"); break;
				case '%': tmpStr.append("%25"); break;
				case '&': tmpStr.append("%26"); break;
				case '*': tmpStr.append("%2A"); break;
				case '+': tmpStr.append("%2B"); break;
				case ',': tmpStr.append("%2C"); break;
//				case '-': tmpStr.append("%2D"); break;
				case '/': tmpStr.append("%2F"); break;
				case ':': tmpStr.append("%3A"); break;
				case ';': tmpStr.append("%3B"); break;
				case '<': tmpStr.append("%3C"); break;
				case '=': tmpStr.append("%3D"); break;
				case '>': tmpStr.append("%3E"); break;
				case '?': tmpStr.append("%3F"); break;
				case '@': tmpStr.append("%40"); break;
				default: tmpStr.append(1, str.at(i));
			}
		}
		return tmpStr;
		
	}
	
	size_t REST::callback(void *ptr, size_t size, size_t count, FILE *data)
	{	
		int numbytes = size*count;
		char lastchar = *((char *) ptr + numbytes - 1);
		*((char *) ptr + numbytes - 1) = '\0';
		REST::buffer.append((char *)ptr);
		REST::buffer.append(1,lastchar);
		*((char *) ptr + numbytes - 1) = lastchar;  // Might not be necessary.
		
		return size*count;
	}
	
//	void REST::checkResponse(XMLNode response) throw(RESTServiceError)
//	{
////		std::string title = response.getChildNode();
//	}
	
//	bool isResponseError() throw(RESTServiceError)
//	{
//		
//	}

	REST::REST()
	{
	
		curlHandle = curl_easy_init();
		
		curl_easy_setopt(REST::curlHandle, CURLOPT_WRITEFUNCTION, REST::callback);
		
	}
	
	REST::~REST()
	{
		curl_easy_cleanup(REST::curlHandle);
	}
	
	std::string REST::getResult()
	{
		return REST::result;
	}
	
	XMLNode REST::getResultInXML() throw (ParsingError)
	{
		XMLResults xmlresult;
		XMLNode tmpXML = XMLNode::parseString(REST::result.c_str(), NULL, &xmlresult);
		if (xmlresult.error == 0) {
			return tmpXML.deepCopy();
		} else {
			throw ParsingError("No XML tag found, No result was returned from REST service.");
//			throw ParsingError(XMLNode::getError(xmlresult.error));
		}
	}
	
	void REST::perform(std::string const& url) throw(RESTServiceError)
	{
		char errorBuffer[CURL_ERROR_SIZE];
		
		REST::buffer = ""; // clear buffer
		
		curl_easy_setopt(REST::curlHandle, CURLOPT_URL, url.c_str());
		curl_easy_setopt(REST::curlHandle, CURLOPT_ERRORBUFFER, errorBuffer);
		CURLcode code = curl_easy_perform(REST::curlHandle);
		
		// clear CURLOPT_URL
		curl_easy_setopt(REST::curlHandle, CURLOPT_URL, "");
		
		// check error
		if (code == 0) {
			REST::result = REST::buffer;
		} else {
			throw RESTServiceError(errorBuffer);
		}
	}
	
	void REST::performPOST(std::string const& url, std::string const& postFields) throw (RESTServiceError)
	{
		char errorBuffer[CURL_ERROR_SIZE];
		
		REST::buffer = ""; // clear buffer
		
		curl_easy_setopt(REST::curlHandle, CURLOPT_URL, url.c_str());
		curl_easy_setopt(REST::curlHandle, CURLOPT_POST, 1);
		curl_easy_setopt(REST::curlHandle, CURLOPT_POSTFIELDS, postFields.c_str());
		curl_easy_setopt(REST::curlHandle, CURLOPT_ERRORBUFFER, errorBuffer);
		CURLcode code = curl_easy_perform(REST::curlHandle);
		
		// clear CURLOPT_URL and CURLOPT_POSTFIELDS
		curl_easy_setopt(REST::curlHandle, CURLOPT_URL, "");
		curl_easy_setopt(REST::curlHandle, CURLOPT_POSTFIELDS, "");
		
		// reset handle to HEAD request
		curl_easy_setopt(REST::curlHandle, CURLOPT_POST, 0);
		curl_easy_setopt(REST::curlHandle, CURLOPT_NOBODY, 1);
		
		// check error
		if (code == 0) {
			REST::result = REST::buffer;
		} else {
			throw RESTServiceError(errorBuffer);
		}
	}
	
	void REST::performHTTPGET(std::string const& url) throw (RESTServiceError)
	{
		char errorBuffer[CURL_ERROR_SIZE];
		
		REST::buffer = ""; // clear buffer
		
		curl_easy_setopt(REST::curlHandle, CURLOPT_URL, url.c_str());
		curl_easy_setopt(REST::curlHandle, CURLOPT_HTTPGET, 1);
		curl_easy_setopt(REST::curlHandle, CURLOPT_ERRORBUFFER, errorBuffer);
		CURLcode code = curl_easy_perform(REST::curlHandle);
		
		// clear CURLOPT_URL
		curl_easy_setopt(REST::curlHandle, CURLOPT_URL, "");
		
		// reset handle to HEAD request
		curl_easy_setopt(REST::curlHandle, CURLOPT_HTTPGET, 0);
		curl_easy_setopt(REST::curlHandle, CURLOPT_NOBODY, 1);
		
		// check error
		if (code == 0) {
			REST::result = REST::buffer;
		} else {
			throw RESTServiceError(errorBuffer);
		}
	}
	
	void REST::print()
	{
		std::cout << REST::result << std::endl;
	}
}




///////////////////g++ rest.cpp /data/Projects/UniSysDBLib/trunk/parser/xmlParser.cpp -lcurl -I/data/Projects/UniSysDBLib/trunk -o test
//int main ()
//{
//	unisys::REST::globalInit();
//	
////	unisys::REST rest;
////	rest.perform("http://rest.bioontology.org/bioportal/ontologies?apikey=b65d2e41-2d75-4499-9b91-bdfcda29c2f1");
////	rest.printXML();
//	
//	
////	unisys::REST rest;
////	rest.perform("http://www.biomart.org/biomart/martservice?type=registry");
////	rest.printXML();
//	
//	
//	std::stringstream strStream;
//	
//	strStream << "<!DOCTYPE Query>";
//	strStream << "<Query client=\"webbrowser\" processor=\"XML\" limit=\"-1\" header=\"1\">";
//	strStream << "<Dataset name=\"hsapiens_gene_ensembl\" config=\"gene_ensembl_config_1\">";
//	strStream << "<Attribute name=\"external_gene_id\"/><Attribute name=\"ensembl_gene_id\"/>";
//	strStream << "<Attribute name=\"chromosome_name\"/><Attribute name=\"start_position\"/>";
//	strStream << "<Attribute name=\"end_position\"/><Attribute name=\"strand\"/>";
//	strStream << "<Attribute name=\"band\"/><Attribute name=\"transcript_count\"/>";
//	strStream << "<Attribute name=\"gene_biotype\"/><Attribute name=\"status\"/>";
//	strStream << "</Dataset>";
//	strStream << "</Query>";
//	std::string tmpStr = strStream.str();
//	XMLNode testXML = XMLNode::parseString(tmpStr.c_str());
//	
//	unisys::REST rest;
//	std::string postOpt = "query=" + unisys::REST::cleanString(testXML.createXMLString());
//	
//	rest.perform("http://central.biomart.org/martservice/portal");
//	rest.print();
//	std::cout << "\n\n\n\n\n\n\n--------------------\n\n\n\n\n\n\n" << std::endl;
//	rest.performPOST("http://central.biomart.org/martservice/results", postOpt);
//	
////	rest.getResultInXML();
//	rest.print();
//	
//	
//	unisys::REST::globalClean();
//	exit(0);
//}

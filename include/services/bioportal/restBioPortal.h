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
#include "services/rest/rest.h"

#ifndef _UNISYSDB_REST_BIOPORTAL_H_
#define _UNISYSDB_REST_BIOPORTAL_H_

namespace unisys {

	/**
		\brief General class for taking care the response from BioPortal's REST service.

	*/
	class RestBioPortalResult {

		protected:

			std::string errorCode; ///< Store an error code from REST response. This value will be presented only when REST response the error back.

			std::string errorLongMessage; ///< Store an error message from REST response, same as errorCode.

			std::string accessedResource; ///< Store The resource name that the library has accessed.

			std::string accessDate; ///< Store The time that the REST service taking response.

			void parseError(XMLNode xml); ///< The protected member function is that for parsing the error response.

		public:

			RestBioPortalResult(); ///< Default constructor

			bool isError() const; ///< To check the response, is it error or not?

			std::string getError(bool codeOnly = false) const; ///< Return the error message.

			std::string getAccessedResource() const; ///< Return accessedResource.

			std::string getAccessDate() const; ///< Return accessDate.

	};

	/**
		\brief General class for taking care the response from BioPortal's search command of REST service.

		This class is derived from restBioPortalResult class with the specific contructor to parse the response
		XML document from the BioPortal's search command.

	*/
	class RestBioPortalSearchResult: public RestBioPortalResult {
		private:

			std::vector<XMLNode> searchResultList; ///< Store the ontology terms and their information which are match with the query.

			std::vector<XMLNode> ontologyHitList; ///< Store the detail of ontology class which the result come from.

		public:

			RestBioPortalSearchResult(); ///< Default constructor

			RestBioPortalSearchResult(XMLNode xml); ///< Overload constructor for parsing XML response.

			size_t nSearchResults() const; ///< Return the number of result.

			std::vector<XMLNode> getSearchResultList() const; ///< Return the list of result.

			std::vector<XMLNode> getOntologyHitList() const; ///< Return the ontology details of result.

	};
	/**
		\brief This class is for taking care of the specific structure of response data call classBean.

		This class is normally used for parsing the response of term command.

	*/
	class ClassBean {

		public:
			/**
				\typedef relationStruct

				\brief For collecting the data in the relations node.

			*/
			typedef struct relationDataStructure {

				std::string type; ///< Type of relation

				int count; ///< Number of element that related with the relation

				std::map<std::string, ClassBean> list; ///< List of element

				std::set<std::string> getIdList(); ///< Return a list of element id.

			} relationStruct;

		private:
			std::string id; ///< ID

			std::string fullId; ///< Full ID of the class in URI format

			std::string label;

			std::string type;

			std::set<std::string> synonyms;

			std::set<std::string> definitions;

			std::vector<relationStruct> relations;

		public:



			ClassBean(); ///< Default constructor

			ClassBean(XMLNode xml);  ///< Overload constructor for parsing XML response.

			std::string getId() const; ///< Return id

			std::string getFullId() const; ///< Return fullId

			std::string getLabel() const; ///< Return label

			std::string getType() const; ///< Returntype

			std::set<std::string> getSynonyms() const; ///< Return the list of synonym

			std::set<std::string> getDefinitions() const; ///< Return the list of definition

			std::vector<relationStruct> getRelations() const; ///< Return the list of relation data structure
	};

	/**
		\brief This class is for parsing the response of term command.

	*/
	class RestBioPortalTermResult: public RestBioPortalResult {
		private:

			ClassBean classBean; ///< A response has one classBean

		public:

			RestBioPortalTermResult(); ///< Default constructor

			RestBioPortalTermResult(XMLNode xml); ///< Overload constructor for parsing XML response.

			ClassBean getClassBean() const; ///< Return classBean

	};

	/**
		\brief The main class of BioPortal REST service library.

	*/
	class RestBioPortal: public REST {

		private:
//			static const std::string apikey;

		public:
			static const std::string baseURL; ///< The base URI of BioPortal REST service.

			RestBioPortal(); ///< Default constructor

			XMLNode listAllLastestOntologies(std::string const& apikey); ///< List all of the lastest ontology classes and thier details.

			XMLNode getSpecificOntology(std::string const& apikey, std::string const& ontologyVersionId); ///< Retern the detail of specific ontology class id.

			/** search
				\brief Searching for related ontology term

				The REST service structure for seach command.
					Signature: ./search/{query}[?{optional args}]&apikey={YourAPIKey}
					Alt Signature: ./search/?query={uri-encoded query}[&{optional args}]&apikey={YourAPIKey}

				\param apikey - API key. This is a mandatory parameter. You can get one from BioPortal website.
				\param query - Query word (examples: "aluminium", "software")
				\param ontologyids - Ontology class id. You can specify nothing or more than one seperated with comma without space. ("1007" for ChEBI ontology, "1007,1104")
				\param isexactmatch - Exact match or not. (default: false)
				\param includeproperties - Return the property information or not. (default: false)
				\param maxnumhits - Maximum number of result. (default: 1000)
				\param includedefinitions - If a search result is a hit for a term, adding this parameter will include the definition in the search result xml. (default: true)
			*/
			RestBioPortalSearchResult search(std::string const& apikey, std::string const& query, std::string const& ontologyids, bool isexactmatch = false,
				bool includeproperties = false, int maxnumhits = 1000, bool includedefinitions = true);
			/** term
				\brief Retrieving the information of the specific ontology id from specific ontology class

				The REST service structure for seach term.
					Virtual Signature: ./virtual/ontology/{ontology virtual id}/{concept id}
					Alt Virtual Signature: ./virtual/ontology/{ontology virtual id}?conceptid={uri-encoded concept id}

				\param apikey - API key. This is a mandatory parameter. You can get one from BioPortal website.
				\param ontology_virtual_id - Ontology class identifier (examples: "1007", "1104")
				\param concept_id - Ontology term identifier (examples: "CHEBI:28984")
				\param light - Light version of result or not(default: false)
				\param norelation - Don't return the relation fields (default: false)
				\param maxnumchildren - An integer that sets threshold on the number of children in the SubClass relation for a term. If a term contains more children than the "maxnumchildren", the SubClass relation returns an empty list. The ChildCount relation still contains the correct number of children. If this parameter set to minus number, this parameter will not set.(default: -1)
			*/
			RestBioPortalTermResult term(std::string const& apikey, std::string const& ontology_virtual_id, std::string const& concept_id,
				bool light = false, bool norelation = false, int maxnumchildren = -1);
	};

}
#endif

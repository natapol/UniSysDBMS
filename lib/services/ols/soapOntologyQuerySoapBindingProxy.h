/* soapOntologyQuerySoapBindingProxy.h
   Generated by gSOAP 2.8.4 from OLSWS.h

Copyright(C) 2000-2011, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
1) GPL or 2) Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#ifndef soapOntologyQuerySoapBindingProxy_H
#define soapOntologyQuerySoapBindingProxy_H
#include "soapH.h"

class SOAP_CMAC OntologyQuerySoapBindingProxy : public soap
{ public:
	/// Endpoint URL of service 'OntologyQuerySoapBindingProxy' (change as needed)
	const char *soap_endpoint;
	/// Constructor
	OntologyQuerySoapBindingProxy();
	/// Constructor with copy of another engine state
	OntologyQuerySoapBindingProxy(const struct soap&);
	/// Constructor with endpoint URL
	OntologyQuerySoapBindingProxy(const char *url);
	/// Constructor with engine input+output mode control
	OntologyQuerySoapBindingProxy(soap_mode iomode);
	/// Constructor with URL and input+output mode control
	OntologyQuerySoapBindingProxy(const char *url, soap_mode iomode);
	/// Constructor with engine input and output mode control
	OntologyQuerySoapBindingProxy(soap_mode imode, soap_mode omode);
	/// Destructor frees deserialized data
	virtual	~OntologyQuerySoapBindingProxy();
	/// Initializer used by constructors
	virtual	void OntologyQuerySoapBindingProxy_init(soap_mode imode, soap_mode omode);
	/// Delete all deserialized data (uses soap_destroy and soap_end)
	virtual	void destroy();
	/// Disables and removes SOAP Header from message
	virtual	void soap_noheader();
	/// Get SOAP Header structure (NULL when absent)
	virtual	const SOAP_ENV__Header *soap_header();
	/// Get SOAP Fault structure (NULL when absent)
	virtual	const SOAP_ENV__Fault *soap_fault();
	/// Get SOAP Fault string (NULL when absent)
	virtual	const char *soap_fault_string();
	/// Get SOAP Fault detail as string (NULL when absent)
	virtual	const char *soap_fault_detail();
	/// Close connection (normally automatic, except for send_X ops)
	virtual	int soap_close_socket();
	/// Force close connection (can kill a thread blocked on IO)
	virtual	int soap_force_close_socket();
	/// Print fault
	virtual	void soap_print_fault(FILE*);
#ifndef WITH_LEAN
	/// Print fault to stream
	virtual	void soap_stream_fault(std::ostream&);
	/// Put fault into buffer
	virtual	char *soap_sprint_fault(char *buf, size_t len);
#endif

	/// Web service operation 'getVersion' (returns error code or SOAP_OK)
	virtual	int getVersion(_ns1__getVersion *ns1__getVersion, _ns1__getVersionResponse *ns1__getVersionResponse) { return getVersion(NULL, NULL, ns1__getVersion, ns1__getVersionResponse); }
	virtual	int getVersion(const char *endpoint, const char *soap_action, _ns1__getVersion *ns1__getVersion, _ns1__getVersionResponse *ns1__getVersionResponse);

	/// Web service operation 'getTermById' (returns error code or SOAP_OK)
	virtual	int getTermById(_ns1__getTermById *ns1__getTermById, _ns1__getTermByIdResponse *ns1__getTermByIdResponse) { return getTermById(NULL, NULL, ns1__getTermById, ns1__getTermByIdResponse); }
	virtual	int getTermById(const char *endpoint, const char *soap_action, _ns1__getTermById *ns1__getTermById, _ns1__getTermByIdResponse *ns1__getTermByIdResponse);

	/// Web service operation 'getTermMetadata' (returns error code or SOAP_OK)
	virtual	int getTermMetadata(_ns1__getTermMetadata *ns1__getTermMetadata, _ns1__getTermMetadataResponse *ns1__getTermMetadataResponse) { return getTermMetadata(NULL, NULL, ns1__getTermMetadata, ns1__getTermMetadataResponse); }
	virtual	int getTermMetadata(const char *endpoint, const char *soap_action, _ns1__getTermMetadata *ns1__getTermMetadata, _ns1__getTermMetadataResponse *ns1__getTermMetadataResponse);

	/// Web service operation 'getTermXrefs' (returns error code or SOAP_OK)
	virtual	int getTermXrefs(_ns1__getTermXrefs *ns1__getTermXrefs, _ns1__getTermXrefsResponse *ns1__getTermXrefsResponse) { return getTermXrefs(NULL, NULL, ns1__getTermXrefs, ns1__getTermXrefsResponse); }
	virtual	int getTermXrefs(const char *endpoint, const char *soap_action, _ns1__getTermXrefs *ns1__getTermXrefs, _ns1__getTermXrefsResponse *ns1__getTermXrefsResponse);

	/// Web service operation 'getOntologyNames' (returns error code or SOAP_OK)
	virtual	int getOntologyNames(_ns1__getOntologyNames *ns1__getOntologyNames, _ns1__getOntologyNamesResponse *ns1__getOntologyNamesResponse) { return getOntologyNames(NULL, NULL, ns1__getOntologyNames, ns1__getOntologyNamesResponse); }
	virtual	int getOntologyNames(const char *endpoint, const char *soap_action, _ns1__getOntologyNames *ns1__getOntologyNames, _ns1__getOntologyNamesResponse *ns1__getOntologyNamesResponse);

	/// Web service operation 'getOntologyLoadDate' (returns error code or SOAP_OK)
	virtual	int getOntologyLoadDate(_ns1__getOntologyLoadDate *ns1__getOntologyLoadDate, _ns1__getOntologyLoadDateResponse *ns1__getOntologyLoadDateResponse) { return getOntologyLoadDate(NULL, NULL, ns1__getOntologyLoadDate, ns1__getOntologyLoadDateResponse); }
	virtual	int getOntologyLoadDate(const char *endpoint, const char *soap_action, _ns1__getOntologyLoadDate *ns1__getOntologyLoadDate, _ns1__getOntologyLoadDateResponse *ns1__getOntologyLoadDateResponse);

	/// Web service operation 'getAllTermsFromOntology' (returns error code or SOAP_OK)
	virtual	int getAllTermsFromOntology(_ns1__getAllTermsFromOntology *ns1__getAllTermsFromOntology, _ns1__getAllTermsFromOntologyResponse *ns1__getAllTermsFromOntologyResponse) { return getAllTermsFromOntology(NULL, NULL, ns1__getAllTermsFromOntology, ns1__getAllTermsFromOntologyResponse); }
	virtual	int getAllTermsFromOntology(const char *endpoint, const char *soap_action, _ns1__getAllTermsFromOntology *ns1__getAllTermsFromOntology, _ns1__getAllTermsFromOntologyResponse *ns1__getAllTermsFromOntologyResponse);

	/// Web service operation 'getRootTerms' (returns error code or SOAP_OK)
	virtual	int getRootTerms(_ns1__getRootTerms *ns1__getRootTerms, _ns1__getRootTermsResponse *ns1__getRootTermsResponse) { return getRootTerms(NULL, NULL, ns1__getRootTerms, ns1__getRootTermsResponse); }
	virtual	int getRootTerms(const char *endpoint, const char *soap_action, _ns1__getRootTerms *ns1__getRootTerms, _ns1__getRootTermsResponse *ns1__getRootTermsResponse);

	/// Web service operation 'getTermsByName' (returns error code or SOAP_OK)
	virtual	int getTermsByName(_ns1__getTermsByName *ns1__getTermsByName, _ns1__getTermsByNameResponse *ns1__getTermsByNameResponse) { return getTermsByName(NULL, NULL, ns1__getTermsByName, ns1__getTermsByNameResponse); }
	virtual	int getTermsByName(const char *endpoint, const char *soap_action, _ns1__getTermsByName *ns1__getTermsByName, _ns1__getTermsByNameResponse *ns1__getTermsByNameResponse);

	/// Web service operation 'getTermsByExactName' (returns error code or SOAP_OK)
	virtual	int getTermsByExactName(_ns1__getTermsByExactName *ns1__getTermsByExactName, _ns1__getTermsByExactNameResponse *ns1__getTermsByExactNameResponse) { return getTermsByExactName(NULL, NULL, ns1__getTermsByExactName, ns1__getTermsByExactNameResponse); }
	virtual	int getTermsByExactName(const char *endpoint, const char *soap_action, _ns1__getTermsByExactName *ns1__getTermsByExactName, _ns1__getTermsByExactNameResponse *ns1__getTermsByExactNameResponse);

	/// Web service operation 'getPrefixedTermsByName' (returns error code or SOAP_OK)
	virtual	int getPrefixedTermsByName(_ns1__getPrefixedTermsByName *ns1__getPrefixedTermsByName, _ns1__getPrefixedTermsByNameResponse *ns1__getPrefixedTermsByNameResponse) { return getPrefixedTermsByName(NULL, NULL, ns1__getPrefixedTermsByName, ns1__getPrefixedTermsByNameResponse); }
	virtual	int getPrefixedTermsByName(const char *endpoint, const char *soap_action, _ns1__getPrefixedTermsByName *ns1__getPrefixedTermsByName, _ns1__getPrefixedTermsByNameResponse *ns1__getPrefixedTermsByNameResponse);

	/// Web service operation 'getTermParents' (returns error code or SOAP_OK)
	virtual	int getTermParents(_ns1__getTermParents *ns1__getTermParents, _ns1__getTermParentsResponse *ns1__getTermParentsResponse) { return getTermParents(NULL, NULL, ns1__getTermParents, ns1__getTermParentsResponse); }
	virtual	int getTermParents(const char *endpoint, const char *soap_action, _ns1__getTermParents *ns1__getTermParents, _ns1__getTermParentsResponse *ns1__getTermParentsResponse);

	/// Web service operation 'getTermChildren' (returns error code or SOAP_OK)
	virtual	int getTermChildren(_ns1__getTermChildren *ns1__getTermChildren, _ns1__getTermChildrenResponse *ns1__getTermChildrenResponse) { return getTermChildren(NULL, NULL, ns1__getTermChildren, ns1__getTermChildrenResponse); }
	virtual	int getTermChildren(const char *endpoint, const char *soap_action, _ns1__getTermChildren *ns1__getTermChildren, _ns1__getTermChildrenResponse *ns1__getTermChildrenResponse);

	/// Web service operation 'getTermRelations' (returns error code or SOAP_OK)
	virtual	int getTermRelations(_ns1__getTermRelations *ns1__getTermRelations, _ns1__getTermRelationsResponse *ns1__getTermRelationsResponse) { return getTermRelations(NULL, NULL, ns1__getTermRelations, ns1__getTermRelationsResponse); }
	virtual	int getTermRelations(const char *endpoint, const char *soap_action, _ns1__getTermRelations *ns1__getTermRelations, _ns1__getTermRelationsResponse *ns1__getTermRelationsResponse);

	/// Web service operation 'getChildrenFromRoot' (returns error code or SOAP_OK)
	virtual	int getChildrenFromRoot(_ns1__getChildrenFromRoot *ns1__getChildrenFromRoot, _ns1__getChildrenFromRootResponse *ns1__getChildrenFromRootResponse) { return getChildrenFromRoot(NULL, NULL, ns1__getChildrenFromRoot, ns1__getChildrenFromRootResponse); }
	virtual	int getChildrenFromRoot(const char *endpoint, const char *soap_action, _ns1__getChildrenFromRoot *ns1__getChildrenFromRoot, _ns1__getChildrenFromRootResponse *ns1__getChildrenFromRootResponse);

	/// Web service operation 'isObsolete' (returns error code or SOAP_OK)
	virtual	int isObsolete(_ns1__isObsolete *ns1__isObsolete, _ns1__isObsoleteResponse *ns1__isObsoleteResponse) { return isObsolete(NULL, NULL, ns1__isObsolete, ns1__isObsoleteResponse); }
	virtual	int isObsolete(const char *endpoint, const char *soap_action, _ns1__isObsolete *ns1__isObsolete, _ns1__isObsoleteResponse *ns1__isObsoleteResponse);

	/// Web service operation 'getTermsByAnnotationData' (returns error code or SOAP_OK)
	virtual	int getTermsByAnnotationData(_ns1__getTermsByAnnotationData *ns1__getTermsByAnnotationData, _ns1__getTermsByAnnotationDataResponse *ns1__getTermsByAnnotationDataResponse) { return getTermsByAnnotationData(NULL, NULL, ns1__getTermsByAnnotationData, ns1__getTermsByAnnotationDataResponse); }
	virtual	int getTermsByAnnotationData(const char *endpoint, const char *soap_action, _ns1__getTermsByAnnotationData *ns1__getTermsByAnnotationData, _ns1__getTermsByAnnotationDataResponse *ns1__getTermsByAnnotationDataResponse);
};
#endif
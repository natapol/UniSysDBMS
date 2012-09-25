/* 
	UniSysDB library
	Copyright (C) 2011 

	Class restBioPortal
	
	Compile: 	restBioPortalSearchResult.cpp restBioPortalResult.cpp xmlParser.cpp
				restBioPortalTermResult.cpp classbean.cpp rest.cpp -lcurl
   
	Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

/** \file restBioPortal.cpp
    \brief Implementtion file for restBioPortal class
*/

#include "restBioMart.h"

namespace unisys {
	// RestBioMartResult //
	RestBioMartResult::RestBioMartResult()
	{
	
	}
	
	
	// RestBioMart //
	
	RestBioMart::RestBioMart()
	{
		RestBioMart::serviceURL = "http://central.biomart.org/martservice";
	}
	
	void RestBioMart::setServiceURL(std::string const& URL)
	{
		RestBioMart::serviceURL = URL;
	}
	
	std::string RestBioMart::getServiceURL() const
	{
		return RestBioMart::serviceURL;
	}
	
	
//	RestBioMartResult RestBioMart::query(std::string const& filename)
//	
//	XMLNode query(XMLNode queryXML)
}

///////////////////g++ rest.cpp restBioMart.cpp /data/Projects/UniSysDBLib/trunk/parser/xmlParser.cpp -lcurl -I/data/Projects/UniSysDBLib/trunk -o test
//int main ()
//{
////<!DOCTYPE Query>
////<Query client=\"true\" processor=\"TSV\" limit=\"-1\" header=\"1\">
////<Dataset name=\"hsapiens_gene_ensembl\" config=\"gene_ensembl_config\">
////<Attribute name=\"ensembl_gene_id\"/>
////<Attribute name=\"ensembl_peptide_id\"/>
////<Attribute name=\"canonical_transcript_stable_id\"/>
////<Attribute name=\"ensembl_transcript_id\"/>
////<Attribute name=\"description\"/>
////<Attribute name=\"end_position\"/>
////<Attribute name=\"start_position\"/>
////<Attribute name=\"chromosome_name\"/>
////<Attribute name=\"strand\"/>
////<Attribute name=\"transcript_start\"/>
////<Attribute name=\"transcript_end\"/>
////<Attribute name=\"external_gene_db\"/>
////<Attribute name=\"external_gene_id\"/>
////<Attribute name=\"external_transcript_id\"/>
////<Attribute name=\"transcript_db_name\"/>
////<Attribute name=\"percentage_gc_content\"/>
////<Attribute name=\"transcript_count\"/>
////<Attribute name=\"gene_biotype\"/>
////<Attribute name=\"transcript_biotype\"/>
////<Attribute name=\"status\"/>
////<Attribute name=\"source\"/>
////<Attribute name=\"transcript_status\"/>
////<Attribute name=\"uniprot_swissprot_accession\"/>
////<Attribute name=\"cell_type\"/>
////<Attribute name=\"atlas_celltype\"/>
////<Attribute name=\"development_stage\"/>
////</Dataset>
////</Query>
//	unisys::REST::globalInit();
//	unisys::RestBioMart a;
//	unisys::RestBioMartResult tmp = a.getRegistry();
//	std::cout << tmp.getResultTab("breast_mart_58") << std::endl;
//	
//	unisys::REST::globalClean();
//	exit(0);
//}

/* 
   UniSysDB library
   Copyright (C) 2011 

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

/** \file LitClass.h
    \brief It contain all literal dirived class
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include "client/dbclient.h"
#include "dataclass/DBClass.h"

#ifndef _UNISYSDB_DATA_CLASS_LITERAL_H_
#define _UNISYSDB_DATA_CLASS_LITERAL_H_

namespace unisys {
	/** 
		\brief Literal class

		This is the root of all literal classes.
	*/
	class Literal: public DataObj {
		private:
			
		
		protected:
			void initField(); ///< function for init field in the object
			
			Literal(); ///< Default constructor
			
		public:
			
			void setComment(std::string const& comment);
			
	};
	
	/** 
		\brief The C++ representative class for Cross reference data class.
		
		\verbatim
		BSON structure:
		{
			type: <database|publication>,
			comment: <string>,
			id: <stringIdOfXref>,
			detail: <string>,
		}
		\endverbatim
		
	*/
	class Xref: public Literal {

		private:
		
			void initField();
			
		public:
		
			Xref(); ///< Default constructor
			
			Xref(mongo::BSONObj const& bsonObj, bool isDatabase = true); ///< Overloaded constructor is used when retriving data in boson object from database and tranform to C++ object
			
			Xref(std::string const& uri, std::string const& detail = "", bool isDatabase = true); ///< Overloaded constructor
			
			bool operator<(Xref const& other) const; ///< Less than operator overload
			
			void setType(bool isDatabase = true); ///< Less than operator overload
			
			void setId(Miriam const& miriam, bool withVer = true); ///< Define cross reference ID with Miriam object
			
			void setId(std::string const& uri, std::string const& ns = "", unsigned int version = 0, bool withVer = true); ///< Define cross reference ID
			
			void setDetail(std::string const& detail); ///< define some detail of this cross reference
		
	};
	
	/** 
		\brief The C++ representative class for Score class in data structure.
		
		\verbatim
		BSON structure:
		{	
			comment: <string>, 
			scoreType: {$ref: <collname>, $id: <idvalue>}, #format by idref class 
			value: <number>, 
			unit: {$ref: <collname>, $id: <idvalue>} #format by idref class 
		}
		\endverbatim
	*/
	class Score: public Literal {

		private:
		
			void initField();
			
		public:
		
			Score(); ///< Default constructor
			
			Score(mongo::BSONObj const& bsonObj); ///< Overloaded constructor is used when retriving data in boson object from database and tranform to C++ object
			
			void setScoreType(OntoIdRef & ontoIdRef);
			
			void setValue(double value);
			
			void setUnit(OntoIdRef & ontoIdRef);
			
		

	};

	/** 
		\brief The C++ representative class for Biological Source data class. This class is designed to manage the biological data of source organism.

		\verbatim
		BSON structure:
		{	
			comment: <string>,
			genus: <string>,
			species: <string>,
			strain: <string>,
			taxonomicId: <XRefBSONStructure>
			cellType: {$ref: <collname>, $id: <idvalue>}, #format by idref class
			tissueType: {$ref: <collname>, $id: <idvalue>}, #format by idref class
			cellState: {$ref: <collname>, $id: <idvalue>}, #format by idref class
		}
		\endverbatim
	*/
	class BioSource: public Literal {

		private:
	
			void initField();
			
		public:
		
			BioSource(); ///< Default constructor
			
			BioSource(mongo::BSONObj const& bsonObj); ///< Overloaded constructor is used when retriving data in boson object from database and tranform to C++ object
			
			BioSource(std::string const& genus, std::string const& species = ".sp");
			
			void setSciName(std::string const& genus, std::string const& species = ".sp");
			
			void setStain(std::string const& strain);
			
			void setTaxonomicId(Xref & taxonomicId);
			
			void setTaxonomicId(std::string const& taxonomicId, std::string const& detail = "");
			
			void setCellType(OntoIdRef & ontoIdRef);
			
			void setCellType(std::string const& ontoId);
			
			void setTissueType(OntoIdRef & ontoIdRef);
			
			void setTissueType(std::string const& ontoId);
			
			void setCellState(OntoIdRef & ontoIdRef);
			
			void setCellState(std::string const& ontoId);
	};
	
	/** 
		\brief The C++ representative class for evidence data class.
		
		\verbatim
		BSON structure:
		{	
			comment: <string>,
			experimentMethod: {$ref: <collname>, $id: <idvalue>}, #format by idref class
			score: <ScoreBSONStructure>,
			biologicalSource: <BioSourceBSONStructure>,
			evidenceSource: <XRefBSONStructure>,
			publicationSupport: {<XRefBSONStructure>, <XRefBSONStructure>, ...}
		}\endverbatim
	*/
	class Evidence: public Literal {

		private:
		
			void initField();
		
		public:
			Evidence(); ///< Default constructor
			
			Evidence(mongo::BSONObj const& bsonObj); ///< Overloaded constructor is used when retriving data in boson object from database and tranform to C++ object
			
			void setExperimentMethod(OntoIdRef & ontoIdRef);
			
			void setExperimentMethod(std::string const& ontoId);
			
			void setConfidence(Score & score);
			
			void setBiologicalSource(BioSource & biologicalSource);
			
			void setEvidenceSource(Xref & evidenceSource);
			
			void setEvidenceSource(std::string const& evidenceSourceId, std::string const& detail = "");
			
			void insertPublicationSupport(Xref & publicationSupport);
			
			void insertPublicationSupport(std::string const& publicationSupportId, std::string const& detail = "");
			
	};

	/** 
		\brief The C++ representative class for annotation data class.

		\verbatim
		BSON structure:
		{	
			comment: <string>,
			definition: {$ref: <collname>, $id: <idvalue>}, #format by idref class
			evidence: <EvidenceBSONStructure>
		}
		\endverbatim
	*/
	class Annotation: public Literal {

		private:
		
			void initField();
			
		public:
			Annotation(); ///< Default constructor
			
			Annotation(mongo::BSONObj const& bsonObj); ///< Overloaded constructor is used when retriving data in boson object from database and tranform to C++ object
			
			void setDefinition(OntoIdRef & ontoIdRef);
			
			void setDefinition(std::string const& ontoId);
			
			void setEvidence(Evidence & evidence);
			
	};

	/** 
		\brief The C++ representative class for relationship data class.
		
		\verbatim
		BSON structure:
		{	
			comment: <string>,
			relationType: {$ref: <collname>, $id: <idvalue>}, #format by idref class
			relationWith: {$ref: <collname>, $id: <idvalue>}, #format by idref class
			evidence: <EvidenceBSONStructure>
		}
		\endverbatim
	*/
	class OntoRelationship: public Literal {

		protected:
		
			void initField();
			
		public:
		
			OntoRelationship(); ///< Default constructor
			
			OntoRelationship(mongo::BSONObj const& bsonObj); ///< Overloaded constructor is used when retriving data in boson object from database and tranform to C++ object
			
			OntoRelationship(std::string const& relationType, std::string const& relationWith);
			
			OntoRelationship(std::string const& relationType, std::string const& relationWith, Evidence evidence);
			
			void setOntoRelationship(std::string const& relationTypeOntoId, std::string const& relationWithId, bool const& isPhysicalEntity = true);
			
			void setRelationType(OntoIdRef ontoIdRef);
			
			void setRelationWith(IdRef IdRef);
			
			void setEvidence(Evidence & evidence);
			
	};
	/** 
		\brief The C++ representative class for relationship data class.
		
		\verbatim
		BSON structure:
		{	
			comment: <string>,
			type: <string>, #format by idref class
			coefficient: <float>,
			relationWith: {$ref: <collname>, $id: <idvalue>}, #format by idref class
			evidence: <EvidenceBSONStructure>
		}
		\endverbatim
	*/
	class Relation: public Literal {
		private:
		
			void initField();
			
		public:
			Relation();
			
			Relation(mongo::BSONObj const& bsonObj);
			
			void setType(std::string const& string);
			
			void setRelationWith(IdRef & IdRef);
			
			void setRelationWith(std::string const& IdRefId, std::string const& targetObjType = "physicalentity");
			
			void setCoefficient(double coefficient);
			
			void setEvidence(Evidence & evidence);
			
			std::string toRXNString(std::string const& compartment) const;
			
			bool isValid();
	};
	/** 
		\brief The C++ representative class for cellular location data class.

		\verbatim
		BSON structure:
		{	
			comment: <string>,
			location: {$ref: <collname>, $id: <idvalue>}, #format by idref class
			evidence: <EvidenceBSONStructure>
		}
		\endverbatim
	*/
	class CellularLocation: public Literal {

		private:
		
			void initField();
			
		public:
			CellularLocation(); ///< Default constructor
			
			CellularLocation(mongo::BSONObj const& bsonObj); ///< Overloaded constructor is used when retriving data in boson object from database and tranform to C++ object
			
			CellularLocation(std::string const& ontoId);
			
			CellularLocation(std::string const& ontoId, Evidence & evidence);
			
			void setLocation(OntoIdRef & ontoIdRef);
			
			void setLocation(std::string const& ontoId);
			
			void setEvidence(Evidence & evidence);
			

	};

	/** 
		\brief The C++ representative class for MathML data class.

		\verbatim
		BSON structure:
		{	
			comment: <string>,
			mathMLDetail: <string>
		}\endverbatim
	*/
	class MathML: public Literal {

		private:
		
			void initField();
			
		public:
		
			MathML(); ///< Default constructor
			
			MathML(mongo::BSONObj const& bsonObj); ///< Overloaded constructor is used when retriving data in boson object from database and tranform to C++ object
			
			void setMathMLDetail(std::string const& mathMLDetail);
			
			void setEvidence(Evidence & evidence);
			

	};
	

	/** 
		\brief The C++ representative class for kinetic parameter data class.
		
		\verbatim
		BSON structure:
		{	
			comment: <string>,
			term: {$ref: <collname>, $id: <idvalue>}, #format by idref class
			value: <number>,
			unit: {$ref: <collname>, $id: <idvalue>}, #format by idref class
			evidence: <EvidenceBSONStructure>
		}\endverbatim
	*/
	class KineticParameter: public Literal {

		private:
		
			void initField();
			
		public:
			
			KineticParameter(); ///< Default constructor
			
			KineticParameter(mongo::BSONObj const& bsonObj); ///< Overloaded constructor is used when retriving data in boson object from database and tranform to C++ object
			
			bool operator<(KineticParameter const& other) const; ///< Less than operator overload
			
			void setTerm(OntoIdRef & ontoIdRef);
			
			void setTerm(std::string const& ontoId);
			
			void setValue(double value);
			
			void setUnit(OntoIdRef & ontoIdRef);
			
			void setEvidence(Evidence & evidence);
			
	};

	/** 
		\brief The C++ representative class for sub-region data class.

		\verbatim
		BSON structure:
		{	
			comment: <string>,
			position: {{start: <number>, stop: <number>}, {start: <number>, stop: <number>}, ...},
			strand: <[-1|0|1]> default:0 = unknown,
			annotation: <AnnotationBSONStructure>
		}
		\endverbatim
	*/
	class SubRegion: public Literal {

		private:
		
			void initField();
			
		public:
		
			SubRegion(); ///< Default constructor
			
			SubRegion(mongo::BSONObj const& bsonObj); ///< Overloaded constructor is used when retriving data in boson object from database and tranform to C++ object
			
			void addPosition(unsigned int start, unsigned int stop);
			
			void setStrand(int strand = 0);
			
			void setAnnotation(Annotation & annotation);
			
	};

	/** 
		\brief The C++ representative class for metadata data class.

		\verbatim
		BSON structure:
		{	
			comment: <string>,
			detail: <string>
		}
		\endverbatim
	*/
	class Metadata: public Literal {

		private:
		
			void initField();
			
		public:
			Metadata(); ///< Default constructor
			
			Metadata(mongo::BSONObj const& bsonObj); ///< Overloaded constructor is used when retriving data in boson object from database and tranform to C++ object
			
			Metadata(std::string const& detail);
			
			void setDetail(std::string const& detail);
			
	};
}
#endif

/* 
   UniSysDB library
   Copyright (C) 2011-2012

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

/**
	\file ObjClass.h
	\brief It contain all object derived class
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "client/dbclient.h"
#include "dataclass/LitClass.h"


#ifndef _UNISYSDB_DATA_CLASS_OBJECT_H_
#define _UNISYSDB_DATA_CLASS_OBJECT_H_

namespace unisys {

	/** 
		\brief Root of all object classes This class does not have any interfaces.
		
		\verbatim
		BSON structure:
		{	
			_id: <string>, #madatory
			ontologyRelationship: {<RelationshipBOSON>, <RelationshipBOSON>, ...},
			relation: {<RelationBOSON>, <RelationBOSON>, ...}
		}
		\endverbatim
	*/
	
	class Object: public DataObj {
	
		protected:
			
			Object();
			
			void initField();
			
			void addRelation(Relation & relation);
			
			void addRelation(std::string const& type, std::string const& idRef, double coefficient = 0, bool canDuplicate = false);
			
		public:
			
			Object(mongo::BSONObj const& bsonObj); ///< Overloaded constructor is used when retriving data in boson object from database and tranform to C++ object
			
			void setId(Miriam const& miriam);
			
			void setId(std::string const& uri);
			
			std::set<Relation> getRelation(std::string const& type = "") const;
			
			Tracking createTrack(std::string activity = "") const;
	};

	/** 
		\brief This class is for miriam cross reference annotation

		\verbatim
		BSON structure:
		{	
			_id: <string>, #madatory
			ontologyRelationship: {<RelationshipBOSON>, <RelationshipBOSON>, ...},
			name: {<string>,<string>, ...}
			type: <string>, # pathway, collection, chemicalentity, dna, dnaregion, rna, protien, complex, control, molecularinteraction,
				genenticinteraction, biochemicalreaction, transport and reactiontransport
			comment: <string>,
			dataPrimarySource: <XrefBOSON>,
			functionAnnotation: {<AnnotationBOSON>, <AnnotationBOSON>, ...},
			evidence: {<EvidenceBOSON>, <EvidenceBOSON>, ...},
			dataXref: {<XrefBOSON>, <XrefBOSON>, ...}
		}
		\endverbatim
		
	*/
	class BioObject: public Object {
	
		protected:
		
			void initField();
			
			BioObject();
			
			void setType(std::string const& name);
		
		public:
			
			void setMainName(std::string const& name);
			
			void addSynonyms(std::string const& name, std::string const& sep_char = ",");
			
			void setComment(std::string const& comment);
			
			void setDataPrimarySource(Xref xref);
			
			void addAnnotation(Annotation & annotation);
			
			void addEvidence(Evidence & evidence);
			
			void addDataXref(Xref xref);
			
			mongo::BSONObj createIdPair(bool strict = true) const;
			
	};

	/** 
		\brief This class is for miriam cross reference annotation

		\verbatim
		BSON structure:
		{	
			_id: <string>, #madatory
			ontologyRelationship: {<RelationshipBOSON>, <RelationshipBOSON>, ...},
			name: {<string>,<string>, ...}
			comment: <string>,
			dataPrimarySource: <XrefBOSON>,
			functionAnnotation: {<AnnotationBOSON>, <AnnotationBOSON>, ...},
			evidence: {<EvidenceBOSON>, <EvidenceBOSON>, ...},
			dataxref: {<XrefBOSON>, <XrefBOSON>, ...},
			interaction: {<DbRef>, <DbRef>, ...},
			complex: {<DbRef>, <DbRef>, ...},
			subRegion: {<SubRegionBOSON>, <SubRegionBOSON>, ...}
		}
		\endverbatim
		
	*/
	class PhysicalEntity: public BioObject {

		protected:
			
			void initField();
			
			PhysicalEntity();
			
			
		public:
			
			void addCellularLocation(CellularLocation & cellularLocation); ///< to add 
			
			void addSubRegion(SubRegion & subRegion); ///< To add sub region
			
	};

	/** 
		\brief This class is for miriam cross reference annotation

		\verbatim
		BSON structure:
		{	
			_id: <string>, #madatory
			ontologyRelationship: {<RelationshipBOSON>, <RelationshipBOSON>, ...},
			names: {<string>,<string>, ...}
			comment: <string>,
			dataPrimarySource: <XrefBOSON>,
			functionAnnotation: {<AnnotationBOSON>, <AnnotationBOSON>, ...},
			evidence: {<EvidenceBOSON>, <EvidenceBOSON>, ...},
			dataxref: {<XrefBOSON>, <XrefBOSON>, ...},
			interaction: {<DbRef>, <DbRef>, ...},
			complex: {<DbRef>, <DbRef>, ...},
			subRegion: {<SubRegionBOSON>, <SubRegionBOSON>, ...},
			formular: <string>,
			InChi: <string>,
			smiles: <string>,
			InChiKey: <string>
		}
		\endverbatim
		
	*/
	class SmallMolecule: public PhysicalEntity {

		private:
	
			void initField();
			
		public:
	
			SmallMolecule(); ///< Default constructor
		
			SmallMolecule(mongo::BSONObj const& bsonObj); ///< Overloaded constructor is used when retriving data in boson object from database and tranform to C++ object
			
			void setFormula(std::string const& formula);
			
			void setInChi(std::string const& inchi, bool isParseFormula = true);
		
			void setSMILES(std::string const& smiles);
		
			void setInChiKey(std::string const& inchiKey);
			
			void addSpecificKineticParameter(KineticParameter & kineticParameter);
			
	};

	/** 
		\brief This class is for miriam cross reference annotation

		\verbatim
		BSON structure:
		{	
			_id: <string>, #madatory
			ontologyRelationship: {<RelationshipBOSON>, <RelationshipBOSON>, ...},
			name: {<string>,<string>, ...}
			comment: <string>,
			dataPrimarySource: <XrefBOSON>,
			functionAnnotation: {<AnnotationBOSON>, <AnnotationBOSON>, ...},
			evidence: {<EvidenceBOSON>, <EvidenceBOSON>, ...},
			dataxref: {<XrefBOSON>, <XrefBOSON>, ...},
			interaction: {<DbRef>, <DbRef>, ...},
			complex: {<DbRef>, <DbRef>, ...},
			subRegion: {<SubRegionBOSON>, <SubRegionBOSON>, ...},
			length: <int>,
			source: <BioSourceBOSON>,
			dnaRegion: {<DbRef>, <DbRef>, ...}
		}
		\endverbatim
		
	*/
	class DNA: public PhysicalEntity {
	
		private:
	
			void initField();
		
		public:
	
			DNA(); ///< Default constructor
		
			DNA(mongo::BSONObj const& bsonObj); ///< Overloaded constructor is used when retriving data in boson object from database and tranform to C++ object
			
			void setLength(int length);
			
			void setSource(BioSource & source);
		
			void addDNARegion(std::string const& dnaRegion);
			
	};

	/** 
		\brief This class is for miriam cross reference annotation

		\verbatim
		BSON structure:
		{	
			_id: <string>, #madatory
			ontologyRelationship: {<RelationshipBOSON>, <RelationshipBOSON>, ...},
			name: {<string>,<string>, ...}
			comment: <string>,
			dataPrimarySource: <XrefBOSON>,
			functionAnnotation: {<AnnotationBOSON>, <AnnotationBOSON>, ...},
			evidence: {<EvidenceBOSON>, <EvidenceBOSON>, ...},
			dataxref: {<XrefBOSON>, <XrefBOSON>, ...},
			interaction: {<DbRef>, <DbRef>, ...},
			complex: {<DbRef>, <DbRef>, ...},
			subRegion: {<SubRegionBOSON>, <SubRegionBOSON>, ...}
			position: <positionPairBSON>,
			dnaSource: <DbRef>,
			transcriptionProduct: {<DbRef>, <DbRef>, ...}
		}
		\endverbatim
		
	*/
	class DNARegion: public PhysicalEntity {

		private:
	
			void initField();
		
		public:
	
			DNARegion(); ///< Default constructor
			
			DNARegion(mongo::BSONObj const& bsonObj); ///< Overloaded constructor is used when retriving data in boson object from database and tranform to C++ object
			
			void setPosition(unsigned int start,unsigned int stop);
			
			void setDNASource(std::string const& peIdRef);
			
			void addTranscriptionProduct(std::string const& trans);
			
			
	};

	/** 
		\brief This class is for miriam cross reference annotation

		\verbatim
		BSON structure:
		{	
			_id: <string>, #madatory
			ontologyRelationship: {<RelationshipBOSON>, <RelationshipBOSON>, ...},
			name: {<string>,<string>, ...}
			comment: <string>,
			dataPrimarySource: <XrefBOSON>,
			functionAnnotation: {<AnnotationBOSON>, <AnnotationBOSON>, ...},
			evidence: {<EvidenceBOSON>, <EvidenceBOSON>, ...},
			dataxref: {<XrefBOSON>, <XrefBOSON>, ...},
			interaction: {<DbRef>, <DbRef>, ...},
			complex: {<DbRef>, <DbRef>, ...},
			subRegion: {<SubRegionBOSON>, <SubRegionBOSON>, ...},
			position: {<positionPairBSON>, <positionPairBSON>, ...},
			dnaRegionSource: <DbRef>,
			translationProduct: {<DbRef>, <DbRef>, ...}
		}
		\endverbatim
		
	*/
	class RNA: public PhysicalEntity {
		private:
			
			void initField();
			
		public:
			
			RNA(); ///< Default constructor
			
			RNA(mongo::BSONObj const& bsonObj); ///< Overloaded constructor is used when retriving data in boson object from database and tranform to C++ object
			
			void addPosition(unsigned int start, unsigned int stop);
			
			void setDNARegionSource(std::string const& peIdRef);
			
			void addTranslationProduct(std::string const& trans);
			

	};

	/** 
		\brief This class is for miriam cross reference annotation

		\verbatim
		BSON structure:
		{	
			_id: <string>, #madatory
			ontologyRelationship: {<RelationshipBOSON>, <RelationshipBOSON>, ...},
			name: {<string>,<string>, ...}
			comment: <string>,
			dataPrimarySource: <XrefBOSON>,
			functionAnnotation: {<AnnotationBOSON>, <AnnotationBOSON>, ...},
			evidence: {<EvidenceBOSON>, <EvidenceBOSON>, ...},
			dataxref: {<XrefBOSON>, <XrefBOSON>, ...},
			interaction: {<DbRef>, <DbRef>, ...},
			complex: {<DbRef>, <DbRef>, ...},
			subRegion: {<SubRegionBOSON>, <SubRegionBOSON>, ...},
			rnaSource: {<DbRef>, <DbRef>, ...},
			specificKineticParameter: {<KineticParameterBOSON>, <KineticParameterBOSON>, ...}
		}
		\endverbatim
		
	*/
	class Protein: public PhysicalEntity {
	
		private:
	
			void initField();
		
		public:
	
			Protein(); ///< Default constructor
		
			Protein(mongo::BSONObj const& bsonObj); ///< Overloaded constructor is used when retriving data in boson object from database and tranform to C++ object
			
			void addRNASource(std::string const& peIdRef);
			
			void addSpecificKineticParameter(KineticParameter & kineticParameter);
			
	};

	/** 
		\brief This class is for miriam cross reference annotation

		\verbatim
		BSON structure:
		{	
			_id: <string>, #madatory
			ontologyRelationship: {<RelationshipBOSON>, <RelationshipBOSON>, ...},
			name: {<string>,<string>, ...}
			comment: <string>,
			dataPrimarySource: <XrefBOSON>,
			functionAnnotation: {<AnnotationBOSON>, <AnnotationBOSON>, ...},
			evidence: {<EvidenceBOSON>, <EvidenceBOSON>, ...},
			dataxref: {<XrefBOSON>, <XrefBOSON>, ...},
			interaction: {<DbRef>, <DbRef>, ...},
			complex: {<DbRef>, <DbRef>, ...},
			subRegion: {<SubRegionBOSON>, <SubRegionBOSON>, ...},
			complexMember: {<DbRef>, <DbRef>, ...},
			specificKineticParameter: {<KineticParameterBOSON>, <KineticParameterBOSON>, ...}
		}
		\endverbatim
		
	*/
	class Complex: public PhysicalEntity {

		private:
	
			void initField();
		
		public:
	
			Complex(); ///< Default constructor
		
			Complex(mongo::BSONObj const& bsonObj); ///< Overloaded constructor is used when retriving data in boson object from database and tranform to C++ object
			
			void addComplexMember(std::string const& peIdRef);
			
			void addSpecificKineticParameter(KineticParameter & kineticParameter);
			
	};

	/** 
		\brief This class is for miriam cross reference annotation

		\verbatim
		BSON structure:
		{	
			_id: <string>, #madatory 
			ontologyRelationship: {<RelationshipBOSON>, <RelationshipBOSON>, ...},
			name: {<string>,<string>, ...}
			comment: <string>,
			dataPrimarySource: <XrefBOSON>,
			functionAnnotation: {<AnnotationBOSON>, <AnnotationBOSON>, ...},
			evidence: {<EvidenceBOSON>, <EvidenceBOSON>, ...},
			dataxref: {<XrefBOSON>, <XrefBOSON>, ...},
			participant: {<StoichiometryBOSON>, <StoichiometryBOSON>, ...},
			interactionKey: <string>
		}
		\endverbatim
		
	*/
	class Interaction: public BioObject {

		protected:
			
			void initField();
			
			Interaction();
			
			void setParticipant(mongo::BSONObj const& bsonObj);
			
		public:
			
			std::set<std::string> getParticipant() const;
			
			void setInteractionKey();
			
			std::string calInteractionKey();
			
			mongo::BSONObj toBSONObj();
	};

	/** 
		\brief This class is for miriam cross reference annotation

		\verbatim
		BSON structure:
		{	
			_id: <string>, #madatory
			type: <string>,
			ontologyRelationship: {<RelationshipBOSON>, <RelationshipBOSON>, ...},
			name: {<string>,<string>, ...}
			comment: <string>,
			dataPrimarySource: <XrefBOSON>,
			functionAnnotation: {<AnnotationBOSON>, <AnnotationBOSON>, ...},
			evidence: {<EvidenceBOSON>, <EvidenceBOSON>, ...},
			dataxref: {<XrefBOSON>, <XrefBOSON>, ...},
			participant: {<StoichiometryBOSON>, <StoichiometryBOSON>, ...},
			interactionKey: <string>,
			controlType: {<DbRef>, <DbRef>, ...},
			phenotype: {<DbRef>, <DbRef>, ...},
			modificationType: {<DbRef>, <DbRef>, ...}
		}
		\endverbatim
		
	*/
	class Control: public Interaction {

		private:
		
			void initField();
		
		public:
	
			Control(); ///< Default constructor
		
			Control(mongo::BSONObj const& bsonObj); ///< Overloaded constructor is used when retriving data in boson object from database and tranform to C++ object
			
			void addControlType(std::string const& ontoIdRef);
			
			void addPhenotype(std::string const& ontoIdRef);
			
			void addModificationType(std::string const& ontoIdRef);
			
			void setController(std::string const& peIdRef);
			
			void setControlled(std::string const& peIdRef);
			

	};

	/** 
		\brief This class is for miriam cross reference annotation

		\verbatim
		BSON structure:
		{	
			_id: <string>, #madatory
			type: <string>,
			ontologyRelationship: {<RelationshipBOSON>, <RelationshipBOSON>, ...},
			name: {<string>,<string>, ...}
			comment: <string>,
			dataPrimarySource: <XrefBOSON>,
			functionAnnotation: {<AnnotationBOSON>, <AnnotationBOSON>, ...},
			evidence: {<EvidenceBOSON>, <EvidenceBOSON>, ...},
			dataxref: {<XrefBOSON>, <XrefBOSON>, ...},
			participant: {<StoichiometryBOSON>, <StoichiometryBOSON>, ...},
			interactionKey: <string>,
			kineticLaw: <MathMLBOSON>,
		}
		\endverbatim
		
	*/
	class MolecularInteraction: public Interaction {

		private:
	
			void initField();
		
		public:
	
			MolecularInteraction(); ///< Default constructor
		
			MolecularInteraction(mongo::BSONObj const& bsonObj); ///< Overloaded constructor is used when retriving data in boson object from database and tranform to C++ object
			
			void setKineticLaw(MathML & kineticLaw);
			
			void addLeft(std::string const& peIdRef, double coefficient);
			
			void addRight(std::string const& peIdRef, double coefficient);
			
	};

	/** 
		\brief This class is for miriam cross reference annotation

		\verbatim
		BSON structure:
		{	
			_id: <string>, #madatory
			type: <string>,
			ontologyRelationship: {<RelationshipBOSON>, <RelationshipBOSON>, ...},
			name: {<string>,<string>, ...}
			comment: <string>,
			dataPrimarySource: <XrefBOSON>,
			functionAnnotation: {<AnnotationBOSON>, <AnnotationBOSON>, ...},
			evidence: {<EvidenceBOSON>, <EvidenceBOSON>, ...},
			dataxref: {<XrefBOSON>, <XrefBOSON>, ...},
			participant: {<StoichiometryBOSON>, <StoichiometryBOSON>, ...},
			interactionKey: <string>,
			interactionType: <DbRef>,
			phynotype: <DbRef>
		}
		\endverbatim
		
	*/
	class GeneticInteraction: public Interaction {

		private:
	
			void initField();
		
		public:
	
			GeneticInteraction(); ///< Default constructor
			
			GeneticInteraction(mongo::BSONObj const& bsonObj); ///< Overloaded constructor is used when retriving data in boson object from database and tranform to C++ object
			
			void setInteractionType(std::string const& ontoIdRef);
			
			void setPhenotype(std::string const& ontoIdRef);
			
			
	};

	/** 
		\brief This class is for miriam cross reference annotation

		\verbatim
		BSON structure:
		{	
			_id: <string>, #madatory
			type: <string>,
			ontologyRelationship: {<RelationshipBOSON>, <RelationshipBOSON>, ...},
			name: {<string>,<string>, ...}
			comment: <string>,
			dataPrimarySource: <XrefBOSON>,
			functionAnnotation: {<AnnotationBOSON>, <AnnotationBOSON>, ...},
			evidence: {<EvidenceBOSON>, <EvidenceBOSON>, ...},
			dataxref: {<XrefBOSON>, <XrefBOSON>, ...},
			participant: {<StoichiometryBOSON>, <StoichiometryBOSON>, ...},
			interactionKey: <string>,
			conversionDirection: <DbRef>,
			kineticLaw: {<MathMLBOSON>, <MathMLBOSON>, ...}
			spontaneous: <string>,
			functional: <string>
		}
		\endverbatim
		
	*/
	class Conversion: public Interaction {
		protected:
	
			void initField();
			
			Conversion();
			
		public:
			
			void addKineticLaw(MathML & kineticLaw);
			
			void addEnzyme(std::string const& peIdRef);
			
			void setSpontaneous(bool value = true);
			
			void setFunctional(bool value = true);
			
	};

	/** 
		\brief This class is for miriam cross reference annotation

		\verbatim
		BSON structure:
		{	
			_id: <string>, #madatory
			type: <string>,
			ontologyRelationship: {<RelationshipBOSON>, <RelationshipBOSON>, ...},
			name: {<string>,<string>, ...}
			comment: <string>,
			dataPrimarySource: <XrefBOSON>,
			functionAnnotation: {<AnnotationBOSON>, <AnnotationBOSON>, ...},
			evidence: {<EvidenceBOSON>, <EvidenceBOSON>, ...},
			dataxref: {<XrefBOSON>, <XrefBOSON>, ...},
			relation: {<StoichiometryBOSON>, <StoichiometryBOSON>, ...},
			interactionKey: <string>,
			conversionDirection: <DbRef>,
			kineticLaw: {<MathMLBOSON>, <MathMLBOSON>, ...}
			spontaneous: <string>,
			functional: <string>
		}
		\endverbatim
		
	*/
	class BiochemicalReaction: public Conversion {
		private:
		
			void initField();
			
		public:
	
			BiochemicalReaction(); ///< Default constructor
		
			BiochemicalReaction(mongo::BSONObj const& bsonObj); ///< Overloaded constructor is used when retriving data in boson object from database and tranform to C++ object
			
			void setConversionDirection(std::string const& direction = "=");
			
			void addLeft(std::string const& peIdRef, double coefficient); ///< Add left participants of reaction
			
			void addRight(std::string const& peIdRef, double coefficient); ///< Add right participants of reaction
			
			std::string toRXNString(std::string const& compartment) const;
	};

	/** 
		\brief This class is for miriam cross reference annotation

		\verbatim
		BSON structure:
		{	
			_id: <string>, #madatory
			type: <string>,
			ontologyRelationship: {<RelationshipBOSON>, <RelationshipBOSON>, ...},
			name: {<string>,<string>, ...}
			comment: <string>,
			dataPrimarySource: <XrefBOSON>,
			functionAnnotation: {<AnnotationBOSON>, <AnnotationBOSON>, ...},
			evidence: {<EvidenceBOSON>, <EvidenceBOSON>, ...},
			dataxref: {<XrefBOSON>, <XrefBOSON>, ...},
			participant: {<StoichiometryBOSON>, <StoichiometryBOSON>, ...},
			interactionKey: <string>,
			conversionDirection: <DbRef>,
			kineticLaw: {<MathMLBOSON>, <MathMLBOSON>, ...}
			spontaneous: <string>,
			functional: <string>
		}
		\endverbatim
		
	*/
	class Transport: public Conversion {

		private:
		
			void initField();
			
		public:
	
			Transport(); ///< Default constructor
		
			Transport(mongo::BSONObj const& bsonObj); ///< Overloaded constructor is used when retriving data in boson object from database and tranform to C++ object
			
			void addImport(std::string const& peIdRef, double coefficient);
			
			void addExport(std::string const& peIdRef, double coefficient);
			
			std::string toRXNString(std::string const& outside, std::string const& inside) const;
	};

	/** 
		\brief This class is for miriam cross reference annotation

		\verbatim
		BSON structure:
		{	
			_id: <string>, #madatory
			type: <string>,
			ontologyRelationship: {<RelationshipBOSON>, <RelationshipBOSON>, ...},
			name: {<string>,<string>, ...}
			comment: <string>,
			dataPrimarySource: <XrefBOSON>,
			functionAnnotation: {<AnnotationBOSON>, <AnnotationBOSON>, ...},
			evidence: {<EvidenceBOSON>, <EvidenceBOSON>, ...},
			dataxref: {<XrefBOSON>, <XrefBOSON>, ...},
			participant: {<StoichiometryBOSON>, <StoichiometryBOSON>, ...},
			interactionKey: <string>,
			conversionDirection: <DbRef>,
			kineticLaw: {<MathMLBOSON>, <MathMLBOSON>, ...}
			spontaneous: <string>,
			functional: <string>
		}
		\endverbatim
		
	*/
	class BiochemicalReactionWithTransport: public Conversion {

		private:
		
			void initField();
			
		public:
	
			BiochemicalReactionWithTransport(); ///< Default constructor
		
			BiochemicalReactionWithTransport(mongo::BSONObj const& bsonObj); ///< Overloaded constructor is used when retriving data in boson object from database and tranform to C++ object
			
			void addLeftIn(std::string const& peIdRef, double coefficient);
			
			void addLeftOut(std::string const& peIdRef, double coefficient);
			
			void addRightIn(std::string const& peIdRef, double coefficient);
			
			void addRightOut(std::string const& peIdRef, double coefficient);
			
			void addImport(std::string const& peIdRef, double coefficient);
			
			void addExport(std::string const& peIdRef, double coefficient);
			
			void setInteractionKey();
			
			/**
				\brief converse to a string of reaction
				\param outside
				\param inside
			*/
			std::string toRXNString(std::string const& outside, std::string const& inside) const;
	};
	
}

#endif

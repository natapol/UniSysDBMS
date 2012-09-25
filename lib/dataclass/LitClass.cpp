/* 
   UniSysDB library
   Copyright (C) 2011-2012

   class LitClass

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

#include "LitClass.h"

namespace unisys {
	
	/////////////
	// Literal //
	/////////////
	void Literal::initField()
	{
		DataObj::addFieldSet("comment");
	}
	
	Literal::Literal()
	{
		Literal::initField();
	}
	
	void Literal::setComment(std::string const& comment)
	{
		DataObj::set("comment", comment);
	}
	
	
	//////////
	// Xref //
	//////////
	void Xref::initField()
	{
		DataObj::addFieldSet("id", true);
		DataObj::addFieldSet("type", true);
		DataObj::addFieldSet("detail");
		
	}
	
	Xref::Xref(): Literal() { Xref::initField(); Xref::setType();}
			
	Xref::Xref(mongo::BSONObj const& bsonObj, bool isDatabase): Literal()
	{
		Xref::initField();
		Xref::setType(isDatabase);
		DataObj::addWithCheck(bsonObj);
		
	}
	
	Xref::Xref(std::string const& uri, std::string const& detail, bool isDatabase): Literal()
	{
		Xref::initField();
		Xref::setType(isDatabase);
		if (!uri.empty()) {
			Xref::setId(uri);
			Xref::setDetail(detail);
		}
	}
	
	bool Xref::operator<(Xref const& other) const
	{
		return strcmp(DataObj::data.getStringField("id"), other.data.getStringField("id")) == -1;
	}
	
	void Xref::setId(Miriam const& miriam, bool withVer)
	{
		if (withVer)
			Xref::set("id", miriam.toDBIdWithVer());
		else
			Xref::set("id", miriam.toDBId());
	}
	
	void Xref::setId(std::string const& id, std::string const& ns, unsigned int version, bool withVer)
	{
		Miriam tmpMiriam(id, ns, version);
		Xref::setId(tmpMiriam, withVer);
	}
	
	void Xref::setDetail(std::string const& detail)
	{
		DataObj::set("detail", detail);
	}
	
	void Xref::setType(bool isDatabase)
	{
		if (isDatabase)
			DataObj::set("type", "database");
		else
			DataObj::set("type", "publication");
	}
	
	///////////
	// Score //
	///////////
	void Score::initField()
	{
		DataObj::addFieldSet("scoreType", true);
		DataObj::addFieldSet("value", true);
		DataObj::addFieldSet("unit");
	}
	
	Score::Score(): Literal() { Score::initField(); }
			
	Score::Score(mongo::BSONObj const& bsonObj): Literal()
	{
		Score::initField();
		DataObj::addWithCheck(bsonObj);
	}
	
	void Score::setScoreType(OntoIdRef & ontoIdRef)
	{
		DataObj::set("scoreType", ontoIdRef.toBSONObj());
	}
	
	void Score::setValue(double value)
	{
		DataObj::set("value", value);
	}
	
	void Score::setUnit(OntoIdRef & ontoIdRef)
	{
		DataObj::set("unit", ontoIdRef.toBSONObj());
	}
	
	///////////////
	// BioSource //
	///////////////
	void BioSource::initField()
	{
		DataObj::addFieldSet("genus", true);
		DataObj::addFieldSet("species", true);
		DataObj::addFieldSet("strain");
		DataObj::addFieldSet("taxonomicId");
		DataObj::addFieldSet("cellType");
		DataObj::addFieldSet("tissueType");
		DataObj::addFieldSet("cellState");
	}
	
	BioSource::BioSource(): Literal() { BioSource::initField(); }
	
	BioSource::BioSource(mongo::BSONObj const& bsonObj): Literal()
	{
		BioSource::initField();
		DataObj::addWithCheck(bsonObj);
	}
	
	BioSource::BioSource(std::string const& genus, std::string const& species): Literal()
	{
		BioSource::initField();
		setSciName(genus, species);
	}
	
	void BioSource::setSciName(std::string const& genus, std::string const& species)
	{
		DataObj::set("genus", genus);
		DataObj::set("species", species);
	}
	
	void BioSource::setStain(std::string const& strain)
	{
		DataObj::set("strain", strain);
	}
	
	void BioSource::setTaxonomicId(Xref & taxonomicId)
	{
		DataObj::set("taxonomicId", taxonomicId.toBSONObj());
	}
	
	void BioSource::setTaxonomicId(std::string const& taxonomicId, std::string const& detail)
	{
		Xref tmp(taxonomicId, detail, false);
		DataObj::set("taxonomicId", tmp.toBSONObj());
	}
	
	void BioSource::setCellType(OntoIdRef & ontoIdRef)
	{
		DataObj::set("cellType", ontoIdRef.toBSONObj());
	}
	
	void BioSource::setCellType(std::string const& ontoId)
	{
		OntoIdRef tmp(ontoId);
		DataObj::set("cellType", tmp.toBSONObj());
	}
	
	void BioSource::setTissueType(OntoIdRef & ontoIdRef)
	{
		DataObj::set("tissueType", ontoIdRef.toBSONObj());
	}
	
	void BioSource::setTissueType(std::string const& ontoId)
	{
		OntoIdRef tmp(ontoId);
		DataObj::set("tissueType", tmp.toBSONObj());
	}
	
	void BioSource::setCellState(OntoIdRef & ontoIdRef)
	{
		DataObj::set("cellState", ontoIdRef.toBSONObj());
	}
	
	void BioSource::setCellState(std::string const& ontoId)
	{
		OntoIdRef tmp(ontoId);
		DataObj::set("cellState", tmp.toBSONObj());
	}

	//////////////
	// Evidence //
	//////////////

	void Evidence::initField()
	{
		DataObj::addFieldSet("experimentMethod", true);
		DataObj::addFieldSet("confidence");
		DataObj::addFieldSet("biologicalSource");
		DataObj::addFieldSet("evidenceSource", true);
		DataObj::addFieldSet("publicationSupport");
	}
	
	Evidence::Evidence(): Literal() { Evidence::initField(); }
			
	Evidence::Evidence(mongo::BSONObj const& bsonObj): Literal()
	{
		Evidence::initField();
		DataObj::addWithCheck(bsonObj);
	}
	
	void Evidence::setExperimentMethod(OntoIdRef & experimentMethod)
	{
		DataObj::set("experimentMethod", experimentMethod.toBSONObj());
	}
	
	void Evidence::setExperimentMethod(std::string const& experimentMethod)
	{
		OntoIdRef tmp(experimentMethod);
		DataObj::set("experimentMethod", tmp.toBSONObj());
	}
	
	void Evidence::setConfidence(Score & score)
	{
		DataObj::set("score", score.toBSONObj());
	}
	
	void Evidence::setBiologicalSource(BioSource & biologicalSource)
	{
		DataObj::set("biologicalSource", biologicalSource.toBSONObj());
	}
	
	void Evidence::setEvidenceSource(Xref & evidenceSource)
	{
		DataObj::set("evidenceSource", evidenceSource.toBSONObj());
	}
	
	void Evidence::setEvidenceSource(std::string const& evidenceSourceId, std::string const& detail)
	{
		Xref tmp(evidenceSourceId, detail, false);
		DataObj::set("evidenceSource", tmp.toBSONObj());
	}
	
	void Evidence::insertPublicationSupport(Xref & publicationSupport)
	{
		DataObj::appendArray("publicationSupport", publicationSupport.toBSONObj());
	}
	
	void Evidence::insertPublicationSupport(std::string const& publicationSupportId, std::string const& detail)
	{
		Xref tmp(publicationSupportId, detail, false);
		DataObj::appendArray("taxonomicId", tmp.toBSONObj());
	}
	
	
	////////////////
	// Annotation //
	////////////////
	void Annotation::initField()
	{
		DataObj::addFieldSet("definition", true);
		DataObj::addFieldSet("evidence");
	}
	
	Annotation::Annotation(): Literal() { Annotation::initField(); }
			
	Annotation::Annotation(mongo::BSONObj const& bsonObj): Literal()
	{
		Annotation::initField();
		DataObj::addWithCheck(bsonObj);
	}
	
	void Annotation::setDefinition(OntoIdRef & ontoIdRef)
	{
		DataObj::set("definition", ontoIdRef.toBSONObj());
	}
	
	void Annotation::setDefinition(std::string const& ontoId)
	{
		DataObj::set("definition", OntoIdRef(ontoId).toBSONObj());
	}
	
	void Annotation::setEvidence(Evidence & evidence)
	{
		DataObj::set("evidence", evidence.toBSONObj());
	}
	
	
	//////////////////////
	// OntoRelationship //
	//////////////////////
	void OntoRelationship::initField()
	{
		DataObj::addFieldSet("relationType", true);
		DataObj::addFieldSet("relationWith", true);
		DataObj::addFieldSet("evidence");
	}
	
	OntoRelationship::OntoRelationship(): Literal() { OntoRelationship::initField(); }
	
	OntoRelationship::OntoRelationship(mongo::BSONObj const& bsonObj): Literal()
	{
		OntoRelationship::initField();
		DataObj::addWithCheck(bsonObj);
	}
	
	OntoRelationship::OntoRelationship(std::string const& relationType, std::string const& relationWith)
	{
		setOntoRelationship(relationType, relationWith);
	}
	
	OntoRelationship::OntoRelationship(std::string const& relationType, std::string const& relationWith, Evidence evidence)
	{
		setOntoRelationship(relationType, relationWith);
		setEvidence(evidence);
	}
	
	void OntoRelationship::setOntoRelationship(std::string const& relationTypeOntoId, std::string const& relationWithId, bool const& isPhysicalEntity)
	{
		DataObj::set("relationType", OntoIdRef(relationTypeOntoId).toBSONObj());
		if (isPhysicalEntity)
			DataObj::set("relationWith", IdRef(relationWithId, "physicalentity").toBSONObj());
		else
			DataObj::set("relationWith", IdRef(relationWithId, "interaction").toBSONObj());
	}
	
	void OntoRelationship::setRelationType(OntoIdRef ontoIdRef)
	{
		DataObj::set("relationType", ontoIdRef.toBSONObj());
	}
	
	void OntoRelationship::setRelationWith(IdRef IdRef)
	{
		DataObj::set("relationWith", IdRef.toBSONObj());
	}
	
	void OntoRelationship::setEvidence(Evidence & evidence)
	{
		DataObj::set("evidence", evidence.toBSONObj());
	}
	
	//////////////
	// Relation //
	//////////////
	
	void Relation::initField()
	{
		DataObj::addFieldSet("comment");
		DataObj::addFieldSet("type", true);
		DataObj::addFieldSet("coefficient");
		DataObj::addFieldSet("relationWith", true);
		DataObj::addFieldSet("evidence");
	}
	
	Relation::Relation(): Literal() { Relation::initField(); }
	
	Relation::Relation(mongo::BSONObj const& bsonObj): Literal()
	{
		Relation::initField();
		DataObj::addWithCheck(bsonObj);
	}
	
	void Relation::setCoefficient(double coefficient)
	{
		DataObj::set("coefficient", coefficient);
	}
	
	void Relation::setType(std::string const& type)
	{
		DataObj::set("type", type);
	}
	
	void Relation::setRelationWith(IdRef & IdRef)
	{
		DataObj::set("relationWith", IdRef.toBSONObj());
	}
	
	void Relation::setRelationWith(std::string const& IdRefId, std::string const& targetObjType)
	{
		DataObj::set("relationWith", IdRef(IdRefId, targetObjType).toBSONObj());
	}
	
	void Relation::setEvidence(Evidence & evidence)
	{
		DataObj::set("evidence", evidence.toBSONObj());
	}
	
	bool Relation::isValid()
	{
		std::set<std::string> tmpSet;
		tmpSet.insert("left"); tmpSet.insert("right");
		tmpSet.insert("import"); tmpSet.insert("export");
		tmpSet.insert("leftIn"); tmpSet.insert("leftOut");
		tmpSet.insert("rightIn"); tmpSet.insert("rightOut");
		
		if ( tmpSet.find(std::string(Relation::data.getStringField("type"))) != tmpSet.end() )
			return Relation::data.hasField("coefficient") && DataObj::isValid();
		else
			return DataObj::isValid();
	}
	
	std::string Relation::toRXNString(std::string const& compartment) const
	{
		return std::string(DataObj::data.getStringField("coefficient")) + " " +
			DataObj::data.getFieldDotted("relationWith.$id").String() + " [" + compartment + "]";
	}
	
	//////////////////////
	// CellularLocation //
	//////////////////////
	void CellularLocation::initField()
	{
		DataObj::addFieldSet("location", true);
		DataObj::addFieldSet("evidence");
	}
	
	CellularLocation::CellularLocation(): Literal() { CellularLocation::initField(); }
			
	CellularLocation::CellularLocation(mongo::BSONObj const& bsonObj): Literal()
	{
		CellularLocation::initField();
		DataObj::addWithCheck(bsonObj);
	}
	
	CellularLocation::CellularLocation(std::string const& ontoId)
	{
		CellularLocation::initField();
		DataObj::set("location", OntoIdRef(ontoId).toBSONObj());
	}
	
	CellularLocation::CellularLocation(std::string const& ontoId, Evidence & evidence)
	{
		CellularLocation::initField();
		DataObj::set("location", OntoIdRef(ontoId).toBSONObj());
		DataObj::set("evidence", evidence.toBSONObj());
	}
	
	void CellularLocation::setLocation(OntoIdRef & ontoIdRef)
	{
		DataObj::set("location", ontoIdRef.toBSONObj());
	}
	
	void CellularLocation::setLocation(std::string const& ontoId)
	{
	 	DataObj::set("location", OntoIdRef(ontoId).toBSONObj());
	}
	
	void CellularLocation::setEvidence(Evidence & evidence)
	{
		DataObj::set("evidence", evidence.toBSONObj());
	}
	
	
	////////////
	// MathML //
	////////////
	void MathML::initField()
	{
		DataObj::addFieldSet("mathMLDetail", true);
		DataObj::addFieldSet("evidence");
	}
	
	MathML::MathML(): Literal() { MathML::initField(); }
			
	MathML::MathML(mongo::BSONObj const& bsonObj): Literal()
	{
		MathML::initField();
		DataObj::addWithCheck(bsonObj);
	}
	
	void MathML::setMathMLDetail(std::string const& mathMLDetail)
	{
		DataObj::set("mathMLDetail", mathMLDetail);
	}
	
	void MathML::setEvidence(Evidence & evidence)
	{
		DataObj::set("evidence", evidence.toBSONObj());
	}
	
	
	//////////////////////
	// KineticParameter //
	//////////////////////
	void KineticParameter::initField()
	{
		DataObj::addFieldSet("term", true);
		DataObj::addFieldSet("value", true);
		DataObj::addFieldSet("unit");
		DataObj::addFieldSet("evidence");
	}
	
	KineticParameter::KineticParameter(): Literal() { KineticParameter::initField(); }
			
	KineticParameter::KineticParameter(mongo::BSONObj const& bsonObj): Literal()
	{
		KineticParameter::initField();
		DataObj::addWithCheck(bsonObj);
	}
	
	void KineticParameter::setTerm(OntoIdRef & ontoIdRef)
	{
		DataObj::set("term", ontoIdRef.toBSONObj());
	}
	
	void KineticParameter::setTerm(std::string const& ontoId)
	{
		OntoIdRef tmp(ontoId);
		DataObj::set("term", tmp.toBSONObj());
	}
	
	void KineticParameter::setValue(double value)
	{
		DataObj::set("value", value);
	}
	
	void KineticParameter::setUnit(OntoIdRef & ontoIdRef)
	{
		DataObj::set("unit", ontoIdRef.toBSONObj());
	}
	
	void KineticParameter::setEvidence(Evidence & evidence)
	{
		DataObj::set("evidence", evidence.toBSONObj());
	}

	///////////////
	// SubRegion //
	///////////////
	void SubRegion::initField()
	{
		DataObj::addFieldSet("position", true);
		DataObj::addFieldSet("strand", true);
		DataObj::addFieldSet("annotation");
		DataObj::set("strand", 0);
	}
	
	SubRegion::SubRegion(): Literal() { SubRegion::initField(); }
			
	SubRegion::SubRegion(mongo::BSONObj const& bsonObj): Literal()
	{
		SubRegion::initField();
		DataObj::addWithCheck(bsonObj);
	}
	
	void SubRegion::addPosition(unsigned int start, unsigned int stop)
	{
		DataObj::appendArray("position", start, stop);
	}
	
	void SubRegion::setStrand(int strand)
	{
		if (strand < 0) {
			DataObj::set("strand", -1);
		} else if (strand > 0) {
			DataObj::set("strand", 1);
		} else {
			DataObj::set("strand", 0);
		}
	}
	
	void SubRegion::setAnnotation(Annotation & annotation)
	{
		DataObj::set("annotation", annotation.toBSONObj());
	}
	
	
	//////////////
	// Metadata //
	//////////////
	void Metadata::initField()
	{
		DataObj::addFieldSet("detail", true);
	}
	
	Metadata::Metadata(): Literal() { Metadata::initField(); }
	
	Metadata::Metadata(std::string const& detail): Literal()
	{
		Metadata::initField();
		Metadata::setDetail(detail);
	}
	
	Metadata::Metadata(mongo::BSONObj const& bsonObj): Literal()
	{
		Metadata::initField();
		DataObj::addWithCheck(bsonObj);
	}
	
	void Metadata::setDetail(std::string const& detail)
	{
		DataObj::set("detail", detail);
	}

}

/////////g++ LitClass.cpp miriam.cpp idref.cpp dataobject.cpp ../uni/*.cpp ../database/database.cpp -lmongoclient -lboost_system -lboost_thread -lboost_filesystem -lboost_program_options -I/usr/include/mongo -I/data/Projects/UniSysDBLib/trunk -o test
//int main () {
//	unisys::Xref abc("urn:miriam:abc:12345");
//	std::cout << abc.toString() << std::endl;
//}

/* 
   UniSysDB library
   Copyright (C) 2011-2012 

   class Interaction and its derived classes

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

#include "ObjClass.h"

namespace unisys {

	/////////////////
	// Interaction //
	/////////////////
	
	void Interaction::initField()
	{
		DataObj::addFieldSet("interactionKey", true);
	}
	
	Interaction::Interaction(): BioObject()
	{
		Interaction::initField();
	}
	
	std::string Interaction::calInteractionKey()
	{
		DataObj::sort();
		mongo::BSONObjBuilder tmp;
		mongo::BSONObjIterator i(DataObj::data);
		
		bool isInsert = false;
		
		while ( i.more() ) {
			mongo::BSONElement e = i.next();
			const char *fname = e.fieldName();
			if( strcmp("relation", fname) == 0 || strcmp("type", fname) == 0 || strcmp("conversionDirection", fname) == 0 ) {
				tmp.append(e);
			}
		}
		return tmp.obj().md5();
	}
	
	void Interaction::setInteractionKey()
	{
		DataObj::set("interactionKey", Interaction::calInteractionKey());
	}
	
	mongo::BSONObj Interaction::toBSONObj()
	{
		Interaction::setInteractionKey();
		return DataObj::toBSONObj();
	}
	
	// Control //
	void Control::initField()
	{
		DataObj::addFieldSet("subRegion");
		DataObj::addFieldSet("CellularLocation");
		DataObj::set("type", "Control");
	}
	
	Control::Control(): Interaction()
	{
		Control::initField();
	}

	Control::Control(mongo::BSONObj const& bsonObj): Interaction()
	{
		Control::initField();
		DataObj::addWithCheck(bsonObj);
	}
	
	void Control::setController(PEIdRef & peIdRef)
	{
		Object::addRelation("controller", peIdRef);
	}
	
	void Control::setControlled(PEIdRef & peIdRef)
	{
		Object::addRelation("controlled", peIdRef);
	}
	
	void Control::addControlType(OntoIdRef & ontoIdRef)
	{
		if (ontoIdRef.isValid())
			DataObj::appendArray("controlType", ontoIdRef.toBSONObj());
	}
	
	void Control::addPhenotype(OntoIdRef & ontoIdRef)
	{
		if (ontoIdRef.isValid())
			DataObj::appendArray("phenotype", ontoIdRef.toBSONObj());
	}
	
	void Control::addModificationType(OntoIdRef & ontoIdRef)
	{
		if (ontoIdRef.isValid())
			DataObj::appendArray("modificationType", ontoIdRef.toBSONObj());
	}
	
	
	// MolecularInteraction //
	void MolecularInteraction::initField()
	{
		DataObj::addFieldSet("subRegion");
		DataObj::addFieldSet("CellularLocation");
		DataObj::set("type", "MolecularInteraction");
	}
	
	MolecularInteraction::MolecularInteraction(): Interaction()
	{
		MolecularInteraction::initField();
	}

	MolecularInteraction::MolecularInteraction(mongo::BSONObj const& bsonObj): Interaction()
	{
		MolecularInteraction::initField();
		DataObj::addWithCheck(bsonObj);
	}
	
	void MolecularInteraction::setKineticLaw(MathML & kineticLaw)
	{
		DataObj::set("kineticLaw", kineticLaw.toBSONObj());
	}
	
	void MolecularInteraction::addLeft(PEIdRef & peIdRef, double coefficient)
	{
		Object::addRelation("left", peIdRef);
	}
	
	void MolecularInteraction::addRight(PEIdRef & peIdRef, double coefficient)
	{
		Object::addRelation("right", peIdRef);
	}
	
	
	// GeneticInteraction //
	void GeneticInteraction::initField()
	{
		DataObj::addFieldSet("subRegion");
		DataObj::addFieldSet("CellularLocation");
		DataObj::set("type", "GeneticInteraction");
	}
	
	GeneticInteraction::GeneticInteraction(): Interaction()
	{
		GeneticInteraction::initField();
	}

	GeneticInteraction::GeneticInteraction(mongo::BSONObj const& bsonObj): Interaction()
	{
		GeneticInteraction::initField();
		DataObj::addWithCheck(bsonObj);
	}
	
	void GeneticInteraction::setInteractionType(OntoIdRef & ontoIdRef)
	{
		DataObj::set("interactionType", ontoIdRef.toBSONObj());
	}
	
	void GeneticInteraction::setPhenotype(OntoIdRef & ontoIdRef)
	{
		DataObj::set("phenotype", ontoIdRef.toBSONObj());
	}
	
	// Conversion //
	void Conversion::initField()
	{
		DataObj::addFieldSet("kineticLaw");
		DataObj::addFieldSet("spontaneous", true);
		DataObj::addFieldSet("functional", true);
		Conversion::setFunctional();
		Conversion::setSpontaneous();
	}
	
	Conversion::Conversion(): Interaction()
	{
		Conversion::initField();
	}
	
	void Conversion::addEnzyme(PEIdRef & peIdRef)
	{
		Object::addRelation("enzyme", peIdRef);
	}
	
	void Conversion::addKineticLaw(MathML & kineticLaw)
	{
		if (kineticLaw.isValid())
			DataObj::appendArray("kineticLaw", kineticLaw.toBSONObj());
	}
	
	void Conversion::setSpontaneous(bool value)
	{
		DataObj::set("spontaneous", value);
	}
	
	void Conversion::setFunctional(bool value)
	{
		DataObj::set("functional", value);
	}
	
	// BiochemicalReaction //
	void BiochemicalReaction::initField()
	{
		DataObj::addFieldSet("conversionDirection", true);
		DataObj::set("type", "BiochemicalReaction");
	}
	
	BiochemicalReaction::BiochemicalReaction(): Conversion()
	{
		BiochemicalReaction::initField();
	}

	BiochemicalReaction::BiochemicalReaction(mongo::BSONObj const& bsonObj): Conversion()
	{
		BiochemicalReaction::initField();
		DataObj::addWithCheck(bsonObj);
	}
	
	void BiochemicalReaction::setConversionDirection(std::string const& direction)
	{
		if (direction.compare("=>") == 0 || direction.compare("<=>") == 0)
			DataObj::set("conversionDirection", direction);
		else
			DataObj::set("conversionDirection", "=");
	}
	
	void BiochemicalReaction::addLeft(PEIdRef & peIdRef, double coefficient)
	{
		Object::addRelation("left", peIdRef, coefficient);
	}
	
	void BiochemicalReaction::addRight(PEIdRef & peIdRef, double coefficient)
	{
		Object::addRelation("right", peIdRef, coefficient);
	}
	
	std::string BiochemicalReaction::toRXNString(std::string const& compartment) const
	{
		std::string tmpStr;
		std::set<Relation>::const_iterator cit;
		std::set<Relation> tmp;
		
		int start = 0;
		tmp = Object::getRelation("left");
		for (cit = tmp.begin(); cit != tmp.end(); cit++) {
			if (start = 1) { tmpStr += " + ";}
			tmpStr += (*cit).toRXNString(compartment);
			start = 1;
		}
		
		tmpStr += " ";
		tmpStr += BiochemicalReaction::data.getStringField("conversionDirection");
		tmpStr += " ";
		
		start = 0;
		tmp = Object::getRelation("right");
		for (cit = tmp.begin(); cit != tmp.end(); cit++) {
			if (start = 1) { tmpStr += " + ";}
			tmpStr += (*cit).toRXNString(compartment);
			start = 1;
		}
		
		return tmpStr;
	}
	
	// Transport //
	void Transport::initField()
	{
		DataObj::set("type", "Transport");
	}
	
	Transport::Transport(): Conversion()
	{
		Transport::initField();
	}

	Transport::Transport(mongo::BSONObj const& bsonObj): Conversion()
	{
		Transport::initField();
		DataObj::addWithCheck(bsonObj);
	}
	
	void Transport::addImport(PEIdRef & peIdRef, double coefficient)
	{
		Object::addRelation("import", peIdRef, coefficient);
	}
	
	void Transport::addExport(PEIdRef & peIdRef, double coefficient)
	{
		Object::addRelation("export", peIdRef, coefficient);
	}
	
	std::string Transport::toRXNString(std::string const& outside, std::string const& inside) const
	{
		std::string left;
		std::string right;
		
		std::set<Relation>::const_iterator cit;
		std::set<Relation> tmp;
		
		int start = 0;
		tmp = Object::getRelation("import");
		for (cit = tmp.begin(); cit != tmp.end(); cit++) {
			if (start = 1) { left += " + "; right += " + ";}
			left += (*cit).toRXNString(outside);
			right += (*cit).toRXNString(inside);
			start = 1;
		}
		
		tmp = Object::getRelation("export");
		for (cit = tmp.begin(); cit != tmp.end(); cit++) {
			if (start = 1) { left += " + "; right += " + ";}
			left += (*cit).toRXNString(inside);
			right += (*cit).toRXNString(outside);
			start = 1;
		}
		
		if (!left.empty() && !right.empty())
			return left + " " + "=>" + " " + right;
		else
			return "";
	}
	
	// BiochemicalReactionWithTransport //
	void BiochemicalReactionWithTransport::initField()
	{
		DataObj::set("type", "BiochemicalReactionWithTransport");
	}
	
	BiochemicalReactionWithTransport::BiochemicalReactionWithTransport(): Conversion()
	{
		BiochemicalReactionWithTransport::initField();
	}

	BiochemicalReactionWithTransport::BiochemicalReactionWithTransport(mongo::BSONObj const& bsonObj): Conversion()
	{
		BiochemicalReactionWithTransport::initField();
		DataObj::addWithCheck(bsonObj);
	}
	
	void BiochemicalReactionWithTransport::addLeftIn(PEIdRef & peIdRef, double coefficient)
	{
		Object::addRelation("leftin", peIdRef, coefficient);
	}
	
	void BiochemicalReactionWithTransport::addLeftOut(PEIdRef & peIdRef, double coefficient)
	{
		Object::addRelation("leftout", peIdRef, coefficient);
	}
	void BiochemicalReactionWithTransport::addRightIn(PEIdRef & peIdRef, double coefficient)
	{
		Object::addRelation("rightin", peIdRef, coefficient);
	}
	
	void BiochemicalReactionWithTransport::addRightOut(PEIdRef & peIdRef, double coefficient)
	{
		Object::addRelation("rightout", peIdRef, coefficient);
	}
	
	void BiochemicalReactionWithTransport::addImport(PEIdRef & peIdRef, double coefficient)
	{
		Object::addRelation("leftout", peIdRef, coefficient);
		Object::addRelation("rightin", peIdRef, coefficient);
	}
	
	void BiochemicalReactionWithTransport::addExport(PEIdRef & peIdRef, double coefficient)
	{
		Object::addRelation("leftin", peIdRef, coefficient);
		Object::addRelation("rightout", peIdRef, coefficient);
	}
	
	std::string BiochemicalReactionWithTransport::toRXNString(std::string const& outside, std::string const& inside) const
	{
		std::string left;
		std::string right;
		
		std::set<Relation>::const_iterator cit;
		std::set<Relation> tmp;
		
		int start = 0;
		
		tmp = Object::getRelation("leftin");
		for (cit = tmp.begin(); cit != tmp.end(); cit++) {
			if (start = 1) { left += " + "; }
			left += (*cit).toRXNString(inside);
			start = 1;
		}
		
		tmp = Object::getRelation("leftout");
		for (cit = tmp.begin(); cit != tmp.end(); cit++) {
			if (start = 1) { left += " + "; }
			left += (*cit).toRXNString(outside);
			start = 1;
		}
		
		tmp = Object::getRelation("rightin");
		for (cit = tmp.begin(); cit != tmp.end(); cit++) {
			if (start = 1) { right += " + "; }
			right += (*cit).toRXNString(inside);
			start = 1;
		}
		
		tmp = Object::getRelation("rightout");
		for (cit = tmp.begin(); cit != tmp.end(); cit++) {
			if (start = 1) { right += " + "; }
			right += (*cit).toRXNString(outside);
			start = 1;
		}
		
		if (!left.empty() && !right.empty())
			return left + " " + "=>" + " " + right;
		else
			return "";
	}
}
/////////////g++ interaction.cpp physicalEntity.cpp dataobject.cpp ../uni/*.cpp object.cpp LitClass.cpp miriam.cpp idref.cpp ../database/database.cpp -lmongoclient -lboost_system -lboost_thread -lboost_filesystem -lboost_program_options -I/usr/include/mongo -I/data/Projects/UniSysDBLib/trunk -o test
//int main () {
//	unisys::BiochemicalReactionWithTransport abc;
//	std::cout << abc.toRXNString("a", "b") << std::endl;
//	std::cout << abc.isValid() << std::endl;
//}

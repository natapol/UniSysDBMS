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
	
	void Control::setController(std::string const& peIdRef)
	{
		Object::addRelation("controller", Miriam(peIdRef).toDBId());
	}
	
	void Control::setControlled(std::string const& peIdRef)
	{
		Object::addRelation("controlled", Miriam(peIdRef).toDBId());
	}
	
	void Control::addControlType(std::string const& ontoIdRef)
	{
		DataObj::appendArray("controlType", Miriam(ontoIdRef).toDBId());
	}
	
	void Control::addPhenotype(std::string const& ontoIdRef)
	{
		DataObj::appendArray("phenotype", Miriam(ontoIdRef).toDBId());
	}
	
	void Control::addModificationType(std::string const& ontoIdRef)
	{
		DataObj::appendArray("modificationType", Miriam(ontoIdRef).toDBId());
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
	
	void MolecularInteraction::addLeft(std::string const& peIdRef, double coefficient)
	{
		Object::addRelation("left", Miriam(peIdRef).toDBId());
	}
	
	void MolecularInteraction::addRight(std::string const& peIdRef, double coefficient)
	{
		Object::addRelation("right", Miriam(peIdRef).toDBId());
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
	
	void GeneticInteraction::setInteractionType(std::string const& ontoIdRef)
	{
		DataObj::set("interactionType", Miriam(ontoIdRef).toDBId());
	}
	
	void GeneticInteraction::setPhenotype(std::string const& ontoIdRef)
	{
		DataObj::set("phenotype", Miriam(ontoIdRef).toDBId());
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
	
	void Conversion::addEnzyme(std::string const& peIdRef)
	{
		Object::addRelation("enzyme", Miriam(peIdRef).toDBId());
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
	
	void BiochemicalReaction::addLeft(std::string const& peIdRef, double coefficient)
	{
		Object::addRelation("left", Miriam(peIdRef).toDBId(), coefficient);
	}
	
	void BiochemicalReaction::addRight(std::string const& peIdRef, double coefficient)
	{
		Object::addRelation("right", Miriam(peIdRef).toDBId(), coefficient);
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
	
	void Transport::addImport(std::string const& peIdRef, double coefficient)
	{
		Object::addRelation("import", Miriam(peIdRef).toDBId(), coefficient);
	}
	
	void Transport::addExport(std::string const& peIdRef, double coefficient)
	{
		Object::addRelation("export", Miriam(peIdRef).toDBId(), coefficient);
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
	
	void BiochemicalReactionWithTransport::addLeftIn(std::string const& peIdRef, double coefficient)
	{
		Object::addRelation("leftin", Miriam(peIdRef).toDBId(), coefficient);
	}
	
	void BiochemicalReactionWithTransport::addLeftOut(std::string const& peIdRef, double coefficient)
	{
		Object::addRelation("leftout", Miriam(peIdRef).toDBId(), coefficient);
	}
	void BiochemicalReactionWithTransport::addRightIn(std::string const& peIdRef, double coefficient)
	{
		Object::addRelation("rightin", Miriam(peIdRef).toDBId(), coefficient);
	}
	
	void BiochemicalReactionWithTransport::addRightOut(std::string const& peIdRef, double coefficient)
	{
		Object::addRelation("rightout", Miriam(peIdRef).toDBId(), coefficient);
	}
	
	void BiochemicalReactionWithTransport::addImport(std::string const& peIdRef, double coefficient)
	{
		Object::addRelation("leftout", Miriam(peIdRef).toDBId(), coefficient);
		Object::addRelation("rightin", Miriam(peIdRef).toDBId(), coefficient);
	}
	
	void BiochemicalReactionWithTransport::addExport(std::string const& peIdRef, double coefficient)
	{
		Object::addRelation("leftin", Miriam(peIdRef).toDBId(), coefficient);
		Object::addRelation("rightout", Miriam(peIdRef).toDBId(), coefficient);
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

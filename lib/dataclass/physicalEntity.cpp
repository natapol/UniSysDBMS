/* 
   UniSysDB library
   Copyright (C) 2011-2012 

   class PhysicalEntity and its derived classes

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

#include "ObjClass.h"

namespace unisys {

	////////////////////
	// PhysicalEntity //
	////////////////////
	
	void PhysicalEntity::initField()
	{
		DataObj::addFieldSet("subRegion");
		DataObj::addFieldSet("CellularLocation");
	}
	
	PhysicalEntity::PhysicalEntity(): BioObject()
	{
		PhysicalEntity::initField();
	}
	
	void PhysicalEntity::addCellularLocation(CellularLocation & cellularLocation)
	{
		if (cellularLocation.isValid())
			DataObj::appendArray("cellularLocation", cellularLocation.toBSONObj());
	}
	
	void PhysicalEntity::addSubRegion(SubRegion & subRegion)
	{
		if (subRegion.isValid())
			DataObj::appendArray("subRegion", subRegion.toBSONObj());
	}
	
	
	// SmallMolecule //
	
	void SmallMolecule::initField()
	{
		DataObj::addFieldSet("inchiKey", true);
		DataObj::addFieldSet("inchi", true);
		DataObj::addFieldSet("formula");
		DataObj::addFieldSet("smiles");
		DataObj::addFieldSet("kineticParameter");
		DataObj::set("type", "SmallMolecule");
	}
	
	SmallMolecule::SmallMolecule(): PhysicalEntity()
	{
		SmallMolecule::initField();
	}
	
	SmallMolecule::SmallMolecule(mongo::BSONObj const& bsonObj): PhysicalEntity()
	{
		SmallMolecule::initField();
		DataObj::addWithCheck(bsonObj);
	}
	
	void SmallMolecule::setFormula(std::string const& formula)
	{
		DataObj::set("formula", formula);
	}
	
	void SmallMolecule::setInChi(std::string const& inchi, bool isParseFormula)
	{
		if (isParseFormula) {
			size_t start = inchi.find("/") + 1;
			size_t length = inchi.find("/", start + 1) - start;
			if (start != std::string::npos)
				DataObj::set("formula", inchi.substr(start, length));
		}
		DataObj::set("inchi", inchi);
	}

	void SmallMolecule::setSMILES(std::string const& smiles)
	{
		DataObj::set("smiles", smiles);
	}

	void SmallMolecule::setInChiKey(std::string const& inchiKey)
	{
		DataObj::set("inchiKey", inchiKey);
	}
	
	void SmallMolecule::addSpecificKineticParameter(KineticParameter & kineticParameter)
	{
		DataObj::appendArray("kineticParameter", kineticParameter.toBSONObj());
	}
	
	// DNA //
	
	void DNA::initField()
	{
		DataObj::addFieldSet("length", true);
		DataObj::addFieldSet("source", true);
		DataObj::set("type", "DNA");
	}
	
	DNA::DNA(): PhysicalEntity()
	{
		DNA::initField();
		DNA::setLength(0);
	}
	
	DNA::DNA(mongo::BSONObj const& bsonObj): PhysicalEntity()
	{
		DNA::initField();
		DataObj::addWithCheck(bsonObj);
	}
	
	void DNA::setLength(int length)
	{
		DataObj::set("length", length);
	}
	
	void DNA::setSource(BioSource & source)
	{
		DataObj::set("source", source.toBSONObj());
	}
	
	
	
	// DNARegion //
	
	void DNARegion::initField()
	{
		DataObj::addFieldSet("position", true);
		DataObj::set("type", "DNARegion");
	}
	
	DNARegion::DNARegion(): PhysicalEntity()
	{
		DNARegion::initField();
	}
	
	DNARegion::DNARegion(mongo::BSONObj const& bsonObj): PhysicalEntity()
	{
		DNARegion::initField();
		DataObj::addWithCheck(bsonObj);
	}
	
	void DNARegion::setPosition(unsigned int start,unsigned int stop)
	{
		DataObj::set("position", start, stop);
	}
	
	void DNARegion::setDNASource(std::string const& peIdRef)
	{
		Object::addRelation("dnaSource", Miriam(peIdRef).toDBId());
	}
	
	// RNA //
	void RNA::initField()
	{
		DataObj::addFieldSet("positions", true);
		DataObj::set("type", "RNA");
	}
	
	RNA::RNA(): PhysicalEntity()
	{
		RNA::initField();
	}
	
	RNA::RNA(mongo::BSONObj const& bsonObj): PhysicalEntity()
	{
		RNA::initField();
		DataObj::addWithCheck(bsonObj);
	}
	
	void RNA::addPosition(unsigned int start, unsigned int stop)
	{
		DataObj::appendArray("positions", start, stop);
	}
	
	void RNA::setDNARegionSource(std::string const& peIdRef)
	{
		Object::addRelation("dnaRegionSource", Miriam(peIdRef).toDBId());
	}
	
	// Protein //
	void Protein::initField()
	{
		DataObj::addFieldSet("kineticParameter");
		DataObj::set("type", "Protein");
	}
	
	Protein::Protein(): PhysicalEntity()
	{
		Protein::initField();
	}
	
	Protein::Protein(mongo::BSONObj const& bsonObj): PhysicalEntity()
	{
		Protein::initField();
		DataObj::addWithCheck(bsonObj);
	}
	
	void Protein::addRNASource(std::string const& peIdRef)
	{
		Object::addRelation("rnaSource", Miriam(peIdRef).toDBId());
	}
	
	void Protein::addSpecificKineticParameter(KineticParameter & kineticParameter)
	{
		DataObj::appendArray("kineticParameter", kineticParameter.toBSONObj());
	}
	
	
	// Complex //
	
	void Complex::initField()
	{
		DataObj::addFieldSet("kineticParameter");
		DataObj::set("type", "Complex");
	}
	
	Complex::Complex(): PhysicalEntity()
	{
		Complex::initField();
	}
	
	Complex::Complex(mongo::BSONObj const& bsonObj): PhysicalEntity()
	{
		Complex::initField();
		DataObj::addWithCheck(bsonObj);
	}
	
	void Complex::addComplexMember(std::string const& peIdRef)
	{
		Object::addRelation("complexMember", Miriam(peIdRef).toDBId());
	}
	
	void Complex::addSpecificKineticParameter(KineticParameter & kineticParameter)
	{
		DataObj::appendArray("kineticParameter", kineticParameter.toBSONObj());
	}
	
}


/////////g++ physicalEntity.cpp object.cpp dataobject.cpp ../uni/*.cpp LitClass.cpp miriam.cpp idref.cpp ../database/database.cpp -lmongoclient -lboost_system -lboost_thread -lboost_filesystem -lboost_program_options -I/usr/include/mongo -I/data/Projects/UniSysDBLib/trunk -o test
//int main () {


//}

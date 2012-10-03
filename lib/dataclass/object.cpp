/* 
   UniSysDB library
   Copyright (C) 2011-2012 

   class ObjClass

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

#include "ObjClass.h"

namespace unisys {

	Object::Object() { Object::initField(); }
	
	void Object::initField()
	{
		DataObj::addFieldSet("_id", true);
		DataObj::addFieldSet("ontologyRelationship");
		DataObj::addFieldSet("relation");
	}
	
	Object::Object(mongo::BSONObj const& bsonObj)
	{
		Object::initField();
		DataObj::addWithOutCheck(bsonObj);
	}
	
	
	void Object::setId(Miriam const& miriam)
	{
		DataObj::set("_id", miriam.toDBId());
	}
	
	void Object::setId(std::string const& uri)
	{
		Miriam tmpMiriam(uri);
		Object::setId(tmpMiriam);
	}
	
	void Object::addRelation(Relation & relation)
	{
		if (relation.isValid())
			Object::relations.insert(relation);
	}
	
	// add some code to check duplicate
	void Object::addRelation(std::string const& type, std::string const& idRef, double coefficient, bool canDuplicate)
	{
		Relation tmprelation;
		tmprelation.setType(type);
		tmprelation.setRelationWith(idRef);
		if (coefficient != 0)
			tmprelation.setCoefficient(coefficient);
		
		Object::addRelation(tmprelation);
	}
	
	
	
	std::set<Relation> Object::getRelation(std::string const& type) const
	{
		if (type.compare("") == 0) {
			return Object::relations;
		} else {
			std::set<Relation>::iterator it;
			std::set<Relation> result;
			for (it = Object::relations.begin(); it != Object::relations.end(); it++) {
				if ( strcmp( (*it).getField("type").toString(false).c_str(), type.c_str() ) ) {
					result.insert(*it);
				}
			}
			
			return result;
		}
	}
	
	Tracking Object::createTrack(std::string activity) const
	{
		if (activity.empty()) {
			activity = "Default activity message";
		}
		Tracking trackingTemp(DataObj::getField("_id").String(), activity);
		return trackingTemp;
	}
	
	
	///////////////
	// BioObject //
	///////////////
	
	void BioObject::initField()
	{
		DataObj::addFieldSet("names", true);
		DataObj::addFieldSet("type", true);
		DataObj::addFieldSet("comment");
		DataObj::addFieldSet("dataPrimarySource", true);
		DataObj::addFieldSet("functionAnnotation");
		DataObj::addFieldSet("evidence");
		DataObj::addFieldSet("dataXref");
		BioObject::setMainName("");
	}
	
	BioObject::BioObject(): Object()
	{
		BioObject::initField();
	}
	
	void BioObject::setMainName(std::string const& name)
	{
		mongo::BSONObjBuilder tmp;
		mongo::BSONObjIterator i(DataObj::data);
		
		bool isInsert = false;
		
		while ( i.more() ) {
			mongo::BSONElement e = i.next();
			const char *fname = e.fieldName();
			if(strcmp("names", fname)) {
				tmp.append(e);
			} else {
				std::vector<mongo::BSONElement> es = e.Array();
				
				mongo::BSONArrayBuilder arrayB;
				arrayB.append(name);
				for (int i = 1; i < es.size(); i++) {
					arrayB.append(es[i]);
				}
				tmp.append("names", arrayB.arr());
				
				isInsert = true;
			}
		}
		
		if (!isInsert) {
			mongo::BSONArrayBuilder arrayB;
			arrayB.append(name);
			tmp.append("names", arrayB.arr());
		}
		
		DataObj::data = tmp.obj();
	}
	
	void BioObject::addSynonyms(std::string const& name, std::string const& sep_char)
	{
		std::vector<std::string> strList;
		boost::algorithm::split( strList, name, boost::algorithm::is_any_of(sep_char), boost::algorithm::token_compress_off );
		for(int i = 0; i < strList.size(); i++)
			DataObj::appendArray("names", strList.at(i));
	}
	
	void BioObject::setComment(std::string const& comment)
	{
		DataObj::set("comment", comment);
	}
	
	void BioObject::setDataPrimarySource(Xref xref)
	{
		DataObj::set("dataPrimarySource", xref.toBSONObj());
	}
	
	void BioObject::addAnnotation(Annotation & annotation)
	{
		DataObj::appendArray("functionAnnotation", annotation.toBSONObj());
	}
	
	void BioObject::addEvidence(Evidence & evidence)
	{
		DataObj::appendArray("evidence", evidence.toBSONObj());
	}
	
	void BioObject::addDataXref(Xref xref)
	{
		DataObj::appendArray("dataXref", xref.toBSONObj());
	}
	
	
}
/////////g++ object.cpp LitClass.cpp miriam.cpp tracking.cpp idref.cpp dataobject.cpp ../uni/*.cpp -lmongoclient -lboost_date_time -lboost_system -lboost_thread -lboost_filesystem -lboost_program_options -I/usr/include/mongo -I/data/Projects/UniSysDBLib/trunk -o test
//int main () {


//}

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
	
	
	void Object::setId(Miriam const& miriam, bool withVer)
	{
		if (withVer)
			DataObj::set("_id", miriam.toDBIdWithVer());
		else
			DataObj::set("_id", miriam.toDBId());
	}
	
	void Object::setId(std::string const& id, std::string const& ns, unsigned int version, bool withVer)
	{
		Miriam tmpMiriam(id, ns, version);
		Object::setId(tmpMiriam, withVer);
	}
	
	void Object::addOntoRelationship(OntoRelationship & ontorelationship)
	{
		if (ontorelationship.isValid())
			DataObj::appendArray("ontologyRelationship", ontorelationship.toBSONObj());
	}
	
	void Object::addRelation(Relation & relation)
	{
		if (relation.isValid())
			DataObj::appendArray("relation", relation.toBSONObj());
	}
	
	// add some code to check duplicate
	void Object::addRelation(std::string const& type, IdRef & idRef, double coefficient, bool canDuplicate)
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
		std::vector<mongo::BSONElement> tmpVec = DataObj::data.getField("relation").Array();
		std::set<Relation> relation;
		for (int i = 0; i < tmpVec.size(); i++) {
			mongo::BSONObj obj = tmpVec[i].Obj();
			if ( strcmp(obj.getStringField("type"), type.c_str()) == 0 ) {
				relation.insert(Relation(obj));
			}
		}
		return relation;
	}
	
	mongo::BSONObj Object::createRelationInsert() const
	{
		mongo::BSONArrayBuilder arrayInj;
		
		std::string idTmp = DataObj::data.getStringField("_id");
		mongo::BSONObj beTmp = DataObj::data.getObjectField("relation");
		
		mongo::BSONObjIterator i(beTmp);
		
		while ( i.more() ) {
			
			mongo::BSONObj e = i.next().Obj();
			mongo::BSONObj query = BSON("_id" << e.getFieldDotted("relationWith.$id").String());
						
			std::string targetNS = e.getFieldDotted("relationWith.$ref").String();
						
			std::string type = e.getStringField("type");
						
			mongo::BSONObjBuilder tmpRela;
			
			tmpRela.append("type", type.append("-from"));
			
			tmpRela.append("relationWith", BSON("$ref" << "physicalentity" << "$id" << idTmp));
			mongo::BSONObj relation = tmpRela.obj();
			
			// query {_id: <id>}
			// inject {$addToSet: {relation: <RelationBSONStruct>}}
			arrayInj.append(BSON("ns" << targetNS << "query" << query << "inject" << BSON("$addToSet" << BSON("relation" << relation))));
		}
		mongo::BSONObj test = arrayInj.arr();
		std::cout << test.toString() << std::endl;
		
		return test;
	}
	
	mongo::BSONObj Object::createRelationRemove() const
	{
		mongo::BSONArrayBuilder arrayInj;
		mongo::BSONArrayBuilder arrayRem;
		
		std::string idTmp = DataObj::data.getStringField("_id");
		mongo::BSONObj beTmp = DataObj::data.getField("relation").Obj();
		
		mongo::BSONObjIterator i(beTmp);
		
		while ( i.more() ) {
			mongo::BSONObj e = i.next().Obj();
			std::string targetId = e.getFieldDotted("relationWith.$id").String();
			mongo::BSONObj query = BSON("_id" << targetId);
			
			std::string targetNS = e.getFieldDotted("relationWith.$ref").String();
			std::string type = e.getStringField("type");
			
			if (type.compare("sourceOf") == 0) {
				arrayRem.append(BSON("ns" << targetNS << "inject" << BSON("_id" << targetId)));
			} else {
				arrayInj.append(BSON("ns" << targetNS << "query" << query << "inject" << BSON("$pull" << BSON("relation" << BSON("relationWith.$id" << idTmp)))));
			}
		}
		
		return BSON("remove" << arrayRem.arr() << "update" << arrayInj.arr());
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
	
	mongo::BSONObj BioObject::createIdPair(bool strict) const
	{
		mongo::BSONArrayBuilder arrayTmp;
		
		std::string idTmp = DataObj::data.getStringField("_id");
		
//		Add IdPair with thier own Id
		mongo::BSONObjBuilder tmp1;
		tmp1.append("_id", idTmp);
		tmp1.append("internal", idTmp);
		tmp1.append("type", "main");
		arrayTmp.append(tmp1.obj());
		
//		Add IdPair from dataPrimarySource
		mongo::BSONObj beTmp = DataObj::data.getField("dataPrimarySource").Obj();
		
		mongo::BSONObjBuilder tmp2;
		tmp2.append("_id", beTmp.getStringField("id"));
		tmp2.append("internal", idTmp);
		tmp2.append("type", "main");
		arrayTmp.append(tmp2.obj());
		
		
//		Add IdPair from cross reference
		if (DataObj::data.hasField("dataXref") && strict) {
			beTmp = DataObj::data.getField("dataXref").Obj();
		
			mongo::BSONObjIterator i(beTmp);
		
			while ( i.more() ) {
				mongo::BSONObj e = i.next().Obj();
				mongo::BSONObjBuilder tmp;
				tmp.append("_id", e.getStringField("id"));
				tmp.append("internal", idTmp);
				tmp.append("type", "cross");
				arrayTmp.append(tmp.obj());
			}
		}
		
//		Add IdPair with interactionKey
		if (DataObj::data.hasField("interactionKey")) {
			mongo::BSONObjBuilder tmp;
			tmp.append("_id", DataObj::data.getStringField("interactionKey"));
			tmp.append("internal", idTmp);
			tmp.append("type", "main");
			arrayTmp.append(tmp.obj());
		}
		
//		Add IdPair with InCHi
		if (DataObj::data.hasField("InChi")) {
			mongo::BSONObjBuilder tmp;
			tmp.append("_id", DataObj::data.getStringField("InChi"));
			tmp.append("internal", idTmp);
			tmp.append("type", "main");
			arrayTmp.append(tmp.obj());
		}
		return arrayTmp.arr();
	}
	
}
/////////g++ object.cpp LitClass.cpp miriam.cpp tracking.cpp idref.cpp dataobject.cpp ../uni/*.cpp -lmongoclient -lboost_date_time -lboost_system -lboost_thread -lboost_filesystem -lboost_program_options -I/usr/include/mongo -I/data/Projects/UniSysDBLib/trunk -o test
//int main () {


//}

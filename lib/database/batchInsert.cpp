/* 
   UniSysDB library
   Copyright (C) 2011 

   class OBOXML

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/


#include "updater.h"
#define MIRIAM_ID_CONV toDBIdWithVer

namespace unisys {

	BatchInsert::BatchInsert()
	{
		
	}
	
	BatchInsert::BatchInsert(Database * databaseHandlePt)
	{
		Updater::setDbHandle(databaseHandlePt);
	}
	
	template <class myType>
	std::vector<mongo::BSONObj> BatchInsert::insert(std::vector<myType> dataList, std::string idNS, unsigned int startId, std::string idPrefix, 
		unsigned int version, bool withVer, bool dryrun) throw (UpdateError, DataError)
	{
		typename std::vector<myType>::const_iterator bsonCit;
		std::map< std::string, std::string> idMap;
		
		std::vector<mongo::BSONObj> tmpBSONArray;
		
		if (idNS.compare("") == 0) {
			idNS = "db";
		}
		
		for (bsonCit = dataList.begin(); bsonCit != dataList.end(); bsonCit++) {
			if ((*bsonCit).hasField("_id") && strcmp((*bsonCit).getField("_id").String(), "") != 0 && startId == 0) {
				idMap[(*bsonCit).getField("dataPrimarySource").Obj().getStringField("id")] = (*bsonCit).getField("_id").String();
			} else {
				if (startId == 0) {
					startId =1;
				}
				
				char buffer [10];
				sprintf(buffer, "%05d", startId);
				std::string instanceId(buffer);
				
				
				(*bsonCit).setId(idPrefix + instanceId, idNS, version, withVer);
				
				if ((*bsonCit).isValid) {
					idMap[(*bsonCit).getObjectField("dataPrimarySource").getStringField("id")] = idNS + ":" + instanceId;
					startId++;
				} else {
					tmpBSONArray.push_back((*bsonCit).toBSONObj());
				}
			}
		}
		
		//for (bsonCit = dataList.begin(); bsonCit != dataList.end(); bsonCit++) {
			//std::vector< mongo::BSONElement > beVector = (*bsonCit).getField("ontologyRelationship").Array();
			//std::vector< mongo::BSONElement >::iterator beVectorIt;
			
			//(*bsonCit).removeField("ontologyRelationship");
			
			//for (beVectorIt = beVector.begin(); beVectorIt != beVector.end(); beVectorIt++) {
				//OntoRelationship tmpOnto((*beVectorIt).Obj());
				//std::string relateId = tmpOnto.getField("relationWith").Obj().getStringField("$id");
				//std::string relateRef = tmpOnto.getField("relationWith").Obj().getStringField("$ref");
				//if (idMap.find(relateId) != idMap.end()) {
					//tmpOnto.setRelationWith(IdRef(relateId, relateRef));
				//}
				
				//(*bsonCit).addOntoRelationship(tmpOnto);
			//}
			
			//if (dryrun) {
				//std::cout << (*bsonCit).toString() << std::endl;
			//} else {
				//Updater::insert((*bsonCit));
			//}
		//}
		
		return tmpBSONArray;
	}
}

///////g++ batchInsert.cpp database.cpp updater*.cpp query.cpp ../parser/chebio*.cpp ../uni/*.cpp ../parser/xmlParser.cpp ../dataclass/*.cpp -lmongoclient -lboost_thread -lboost_filesystem -lboost_date_time -lboost_system -lboost_program_options -I/usr/include/mongo -I/data/Projects/UniSysDBLib/trunk -o test

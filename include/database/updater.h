/*
   UniSysDB library
   Copyright (C) 2011

	Class Updater and BatchUpdater

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

/** \file updater.h
    \brief It contain KGMLPlus and its subclass Graphic
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "client/dbclient.h"
#include "database.h"
#include "query.h"
#include "dataclass/LitClass.h"
#include "dataclass/ObjClass.h"
#include "dataclass/DBClass.h"
#include "parser/chebiowl.h"
#include "parser/oboXML.h"
#include "parser/biopax.h"
#include "parser/psimi.h"
//#include "uni/uniString.h"


#ifndef _UNISYSDB_UPDATER_H_
#define _UNISYSDB_UPDATER_H_
namespace unisys {

	std::string setMiriamURN(std::string db, XMLNode node);
	
	class Updater {

		protected:

			Database * databaseHandle;
			/**
				\brief compare cross reference to object in database compare all cross references to IdPair collection. If found, return true.
				\param ns boson object of BioObject class
				\param bsonobj compare all cross refernces and if obj is Interaction object, also compare with interactionKey
			*/
			IdRef idConverter(IdRef const& ref) throw (QueryError);
			/**
				\brief compare cross reference to object in database compare all cross references to IdPair collection. If found, return true.
				\param ns boson object of BioObject class
				\param bsonobj compare all cross refernces and if obj is Interaction object, also compare with interactionKey
			*/
			IdRef idConverter(std::string const& ns, std::string const& id) throw (QueryError);
			/**
				\brief compare cross reference to object in database compare all cross references to IdPair collection. If found, return true.
				\param obj boson object of BioObject class
				\param strict compare all cross refernces and if obj is Interaction object, also compare with interactionKey
			*/
			bool checkIdPair(BioObject obj, bool strict = true) const;			
			/**
				\brief compare cross reference to object in database compare all cross references to IdPair collection. If found, return true.
				\param bsonobj boson object of BioObject class
				\param isInsert compare all cross refernces and if obj is Interaction object, also compare with interactionKey
			*/
			void updateIdPair(mongo::BSONObj const& bsonobj, bool isInsert = true) throw (UpdateError);
			/**
				\brief compare cross reference to object in database
				\param collectionNS boson object of BioObject class
				\param query compare all cross refernces and if obj is Interaction object, also compare with interactionKey
				\param bsonObj boson object of BioObject class
				\param upsert compare all cross refernces and if obj is Interaction object, also compare with interactionKey
				\param multi compare all cross refernces and if obj is Interaction object, also compare with interactionKey
			*/
			void update(std::string const& collectionNS, mongo::Query query, mongo::BSONObj bsonObj, bool upsert = false, bool multi = false) throw (UpdateError);
			/**
				\brief compare cross reference to object in database
				\param collectionNS boson object of BioObject class
				\param bsonObj compare all cross refernces and if obj is Interaction object, also compare with interactionKey
			*/
			void insert(std::string const& collectionNS, mongo::BSONObj bsonObj) throw (UpdateError);
			/**
				\brief compare cross reference to object in database
				\param collectionNS boson object of BioObject class
				\param q compare all cross refernces and if obj is Interaction object, also compare with interactionKey
				\param justOne compare all cross refernces and if obj is Interaction object, also compare with interactionKey
			*/
			void remove(std::string const& collectionNS, mongo::Query q, bool justOne) throw (UpdateError);
			/**
				\brief compare cross reference to object in database
				\param obj boson object of BioObject class
				\param upsert compare all cross refernces and if obj is Interaction object, also compare with interactionKey
				\param multi boson object of BioObject class
			*/
			void updateRelationAdd(Object const& obj, bool upsert = false, bool multi = false) throw (UpdateError);
			/**
				\brief compare cross reference to object in database
				\param obj boson object of BioObject class
				\param isRemove compare all cross refernces and if obj is Interaction object, also compare with interactionKey
				\param justOne boson object of BioObject class
				\param upsert compare all cross refernces and if obj is Interaction object, also compare with interactionKey
				\param multi boson object of BioObject class
			*/
			void updateRelationDel(Object const& obj, bool isRemove = true, bool justOne = 0, bool upsert = false, bool multi = false) throw (UpdateError);
			
		public:

			Updater();

			Updater(Database * databaseHandlePt);

			void setDbHandle(Database * databaseHandlePt);

			// remove function

			void insert(Tracking tracking) throw (UpdateError, DataError);

			void insert(Ontology & ontology) throw (UpdateError, DataError);

			void insert(PhysicalEntity & data, bool strict = true) throw (UpdateError, DataError);

			void insert(Interaction & data, bool strict = true) throw (UpdateError, DataError);


			/////// remove function
			/**
				\brief compare cross reference to object in database
				\param collectionNS boson object of BioObject class
				\param id compare all cross refernces and if obj is Interaction object, also compare with interactionKey
				\param removeRela boson object of BioObject class
				\param removeProduct compare all cross refernces and if obj is Interaction object, also compare with interactionKey
			*/
			void remove(std::string const& collectionNS, std::string const& id, bool removeRela = true, bool removeProduct = true) throw (UpdateError);
			/**
				\brief compare cross reference to object in database
				\param collectionNS boson object of BioObject class
				\param ids compare all cross refernces and if obj is Interaction object, also compare with interactionKey
				\param removeRela boson object of BioObject class
				\param removeProduct compare all cross refernces and if obj is Interaction object, also compare with interactionKey
			*/
			void remove(std::string const& collectionNS, std::set<std::string> const& ids, bool removeRela = true, bool removeProduct = true) throw (UpdateError);

			/////// update function
			/**
				\brief compare cross reference to object in database
				\param ontology boson object of BioObject class
				\param check compare all cross refernces and if obj is Interaction object, also compare with interactionKey
			*/
			void update(Ontology const& ontology, bool check = true) throw (UpdateError, DataError);
			/**
				\brief compare cross reference to object in database
				\param physicalentity boson object of BioObject class
				\param check compare all cross refernces and if obj is Interaction object, also compare with interactionKey
			*/
			void update(PhysicalEntity & physicalentity, bool check = true) throw (UpdateError, DataError);
			/**
				\brief compare cross reference to object in database
				\param interaction boson object of BioObject class
				\param check compare all cross refernces and if obj is Interaction object, also compare with interactionKey
			*/
			void update(Interaction & interaction, bool check = true) throw (UpdateError, DataError);

	};

	class BatchInsert: public Updater {

		private:
			
			std::vector<mongo::BSONObj> insert(std::vector<mongo::BSONObj> dataList, std::string idNS = "", int startId = 1, bool dryrun = false) throw (UpdateError, DataError);
			
		public:

			BatchInsert();

			BatchInsert(Database * databaseHandlePt);
			
			template <class myType>
			std::vector<mongo::BSONObj> insert(std::vector<myType> dataList, std::string idNS = "", unsigned int startId = 0, std::string idPrefix = "", 
				unsigned int version = 0, bool withVer = true, bool dryrun = false) throw (UpdateError, DataError);
			
	};


}
#endif

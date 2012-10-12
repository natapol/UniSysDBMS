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
				\param obj boson object of BioObject class
				\param strict compare all cross refernces and if obj is Interaction object, also compare with interactionKey
			*/
			bool isRedundantcy(BioObject obj, bool strict = true) const;
			/**
				\brief compare cross reference to object in database compare all cross references to IdPair collection. If found, return true.
				\param bsonobj boson object of BioObject class
				\param isInsert compare all cross refernces and if obj is Interaction object, also compare with interactionKey
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
				\param collectionNS boson object of BioObject class
				\param q compare all cross refernces and if obj is Interaction object, also compare with interactionKey
				\param justOne compare all cross refernces and if obj is Interaction object, also compare with interactionKey
			*/
			void ensureIndex(std::string const& collectionNS, mongo::BSONObj keys, bool unique = false, 
				const std::string & name = "", bool cache = true, bool background = false, int v = -1) throw (UpdateError);
			/**
				\brief compare cross reference to object in database
				\param collectionNS boson object of BioObject class
				\param q compare all cross refernces and if obj is Interaction object, also compare with interactionKey
				\param justOne compare all cross refernces and if obj is Interaction object, also compare with interactionKey
			*/
			void ensureIndexRelation() throw (UpdateError);
			/**
				\brief compare cross reference to object in database
				\param collectionNS boson object of BioObject class
				\param q compare all cross refernces and if obj is Interaction object, also compare with interactionKey
				\param justOne compare all cross refernces and if obj is Interaction object, also compare with interactionKey
			*/
			void ensureIndexNode() throw (UpdateError);
			/**
				\brief compare cross reference to object in database
				\param collectionNS boson object of BioObject class
				\param q compare all cross refernces and if obj is Interaction object, also compare with interactionKey
				\param justOne compare all cross refernces and if obj is Interaction object, also compare with interactionKey
			*/
			void ensureIndexChem() throw (UpdateError);
		public:

			Updater();

			Updater(Database * databaseHandlePt);

			void setDbHandle(Database * databaseHandlePt);

			// remove function
			/**
				\brief compare cross reference to object in database
				\param collectionNS boson object of BioObject class
				\param id compare all cross refernces and if obj is Interaction object, also compare with interactionKey
				\param removeRela boson object of BioObject class
				\param removeProduct compare all cross refernces and if obj is Interaction object, also compare with interactionKey
			*/
			void insert(Tracking tracking) throw (UpdateError, DataError);
			/**
				\brief compare cross reference to object in database
				\param collectionNS boson object of BioObject class
				\param id compare all cross refernces and if obj is Interaction object, also compare with interactionKey
				\param removeRela boson object of BioObject class
				\param removeProduct compare all cross refernces and if obj is Interaction object, also compare with interactionKey
			*/
			void insert(BioObject & object, bool strict) throw (UpdateError, DataError);
			/**
				\brief compare cross reference to object in database
				\param collectionNS boson object of BioObject class
				\param id compare all cross refernces and if obj is Interaction object, also compare with interactionKey
				\param removeRela boson object of BioObject class
				\param removeProduct compare all cross refernces and if obj is Interaction object, also compare with interactionKey
			*/
			void insertRelation(BioObject & object) throw (UpdateError, DataError);
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
			void remove(std::string const& collectionNS, std::set<std::string> const& ids, bool removeRela = true, bool removeProduct = true) throw (UpdateError, QueryError);

			/////// update function
			/**
				\brief compare cross reference to object in database
				\param physicalentity boson object of BioObject class
				\param check compare all cross refernces and if obj is Interaction object, also compare with interactionKey
			*/
			void update(PhysicalEntity & physicalentity, bool check = true) throw (UpdateError, DataError);

	};

	//class BatchInsert: public Updater {

		//private:
			
			//std::vector<mongo::BSONObj> insert(std::vector<mongo::BSONObj> dataList, std::string idNS = "", int startId = 1, bool dryrun = false) throw (UpdateError, DataError);
			
		//public:

			//BatchInsert();

			//BatchInsert(Database * databaseHandlePt);
			
			//template <class myType>
			//std::vector<mongo::BSONObj> insert(std::vector<myType> dataList, std::string idNS = "", unsigned int startId = 0, std::string idPrefix = "", 
				//unsigned int version = 0, bool withVer = true, bool dryrun = false) throw (UpdateError, DataError);
			
	//};


}
#endif

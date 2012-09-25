/* 
   UniSysDB library
   Copyright (C) 2011 

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/

/** \file DBClass.h
    \brief It contain Miriam, IdRef, Tracking and LiteralBSON class using 
    for formating data to database structure 
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <time.h>
#include <vector>
#include <set>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/algorithm/string/split.hpp>
#include "client/dbclient.h"
#include "database/database.h"



#ifndef _UNISYSDB_DATA_CLASS_H_
#define _UNISYSDB_DATA_CLASS_H_

namespace unisys {
	
	template <class type>
	mongo::BSONArray toBSONArray(type const& input)
	{
		mongo::BSONArrayBuilder tmpBSONArray;
		typename type::const_iterator cit;
		for (cit = input.begin(); cit != input.end(); cit++)
		{
			tmpBSONArray.append((*cit).toBSONObj());
		}
		return tmpBSONArray.arr();
	}
	
	
	template <class type>
	std::set<type> BSONToSet(mongo::BSONObj const& bsonObj)
	{
		typename std::set<type> tmp;
		for (int i = 0; i < bsonObj.nFields(); i++) {
			type tmpType(bsonObj[i].Obj());
			tmp.insert(tmpType);
		}
		return tmp;
	}
	
	template <class type>
	std::vector<type> BSONToVector(mongo::BSONObj const& bsonObj)
	{
		typename std::vector<type> tmp;
		for (int i = 0; i < bsonObj.nFields(); i++) {
			type tmpType(bsonObj[i].Obj());
			tmp.push_back(tmpType);
		}
		return tmp;
	}
	
	class DataObj {
	
		protected:
			
			virtual void initField() = 0;
			
			mongo::BSONObj data;
			
			std::vector<std::string> fieldSet;
			
			std::set<std::string> requireField;
			
			// Append
			
			inline void addFieldSet(std::string const& fieldSet, bool isRequire = false)
			{
				DataObj::fieldSet.push_back(fieldSet);
				if (isRequire) DataObj::requireField.insert(fieldSet);
			}
			
			void appendElements(mongo::BSONObj x);
			
			void appendElementsUnique(mongo::BSONObj x);
			
			void appendAs(mongo::BSONElement const& e, std::string const& fieldName, bool substitute = false);
			
			void appendArray(std::string const& fieldName, mongo::BSONObj const& subObj);
			
			void appendArray(std::string const& fieldName, int start, int stop);
			
			template<class type >
			void appendArray(std::string const& fieldName, type const& subObj)
			{
				mongo::BSONObjBuilder tmp;
				mongo::BSONObjIterator i(DataObj::data);
		
				bool isInsert = false;
		
				while ( i.more() ) {
					mongo::BSONElement e = i.next();
					const char *fname = e.fieldName();
					if(strcmp(fieldName.c_str(), fname)) { // if fname != fieldName
						tmp.append(e);
					} else {
						std::vector<mongo::BSONElement>::const_iterator cit;
						std::vector<mongo::BSONElement> es = e.Array();
				
						mongo::BSONArrayBuilder arrayB;
				
						for (cit = es.begin(); cit != es.end(); cit++) {
							type value;
							(*cit).Val(value);
							arrayB.append(value);
						}
						arrayB.append(subObj);
						tmp.append(fieldName, arrayB.arr());
				
						isInsert = true;
					}
				}
		
				if (!isInsert) {
					mongo::BSONArrayBuilder arrayB;
					arrayB.append(subObj);
					tmp.append(fieldName, arrayB.arr());
				}
				DataObj::data = tmp.obj();
			}
			
			void append(std::string const& fieldName, const char *str, int sz, bool substitute = false);
			
			template <class myType>
			void append(std::string const& fieldName, myType value, bool substitute = false)
			{
					if (substitute) DataObj::removeField(fieldName);
					mongo::BSONObjBuilder tmp;
					tmp.appendElements(DataObj::data);
					tmp.append(fieldName, value);
					DataObj::data = tmp.obj();
			}
			
			void set(std::string const& fieldName, std::string const& value);
			
			template <class myType>
			void set(std::string const& fieldName, myType value)
			{
				if ( value.isValid() ) {
					DataObj::append(fieldName, value, true);
				}
			}
			
			void set(std::string const& fieldName, int value);
			
			void set(std::string const& fieldName, double value);
			
			void set(std::string const& fieldName, const char * value);
			
			void set(std::string const& fieldName, bool value);
			
			void set(std::string const& fieldName, int start, int stop);
			
			void appendTimeT(std::string const& fieldName, time_t dt, bool substitute = false);
			
			void appendRegex(std::string const& fieldName, std::string const& regex, std::string const& options = "", bool substitute = false);
			
			void appendTimeStamp(std::string const& fieldName, bool substitute = false);
			
			void appendAsNumber(std::string const& fieldName, std::string const& data, bool substitute = false);
			
			void appendNull(std::string const& fieldName, bool substitute = false);
			
			void appendCode(std::string const& fieldName, std::string const& code, bool substitute = false);
			
			void appendDBRef(std::string const& fieldName, std::string const& ns, mongo::OID const& oid, bool substitute = false);
			
			void genOID();
			
			void sort();
			
		public:
			DataObj();
			
			DataObj(mongo::BSONObj const& bsonObj);
			
			void addWithCheck(mongo::BSONObj const& bsonObj);
			
			void addWithOutCheck(mongo::BSONObj const& bsonObj);
			
			bool operator< (DataObj const& other) const;
			
			bool operator<= (DataObj const& other) const;
			
			bool operator> (DataObj const& other) const;
			
			bool operator>= (DataObj const& other) const;
			
			bool operator== (DataObj const& other) const;
			
			bool valid () const;
			
			std::string md5 ();
			
			mongo::BSONObj toBSONObj();
			
			std::string toString (bool isArray=false, bool full=false);
			
			mongo::BSONElement getField(std::string const& fieldName) const;
			
			bool hasField(std::string const& fieldName) const;
			
			void removeField(std::string const& fieldName);
			
			bool isOwned () const;
			
//			DataObj getOwned () const;
			
			bool isValid() const;
	};
	
	
	/** 
		\brief This class is for miriam cross reference annotation

		This Mirium object is a part of standard guidelines	in the controlled annotation of model components, based on Uniform Resource Identifiers (URI).
		The URI format comprise of two parts URN:identifier.
		URN or Uniform Resource Name is in format "urn:miriam:domain[.sub-domain]"; such as urn:miriam:kegg.compound. 
		In this class structure, only domain and sub-domain are stored in class data member.
		Identifier is the id of object reference to its own URN.
		
		
	*/
	class Miriam {

		private:
			
			std::string ns; ///< domain.sub-domain namespace
			
			std::string id; ///< Identifier
			
			unsigned int version; ///< Version
			
			void setUri(std::string const& uri);
			
		public:
	
			Miriam(); ///< Default constructor
		
			Miriam(std::string const& id, std::string const& ns = "", unsigned int version = 0); ///< Overloaded constructor
			
			bool operator<(Miriam const& other) const; ///< Less than operator overload
			
			bool operator==(Miriam const& other) const; ///< Equal operator overload
			
			void set(std::string const& id, std::string const& ns = "", unsigned int version = 0);
			
			std::string toURI() const; ///< return URI string
			
			std::string toId() const; ///< return Id string
			
			std::string toDBId() const; ///< return Database system ID string (domain.sub-domain namespace:Identifier)
			
			bool isValid() const; ///< Check validity of data
			
			// Miriam annotation with version code
			void operator++(int number = 1); ///< Increase the number of version with 1
			
			std::string toURIWithVer() const; ///< return URI string appended with version number(super-domain:domain.sub-domain namespace:Identifier.Version)
			
			std::string toDBIdWithVer() const; ///< return Database system ID string appended with version number(domain.sub-domain namespace:Identifier.Version)
			
			void increaseVer(int number = 1); ///< Increase the number of version with 1
	};
	/** 
		\brief Identifier reference class

		This class is used for storing database reference (DBRef) under MongoDb DBRef format, which is {"$ref": "collectionNS", "$id": "id"},
		but it support only reference between objects in the same database. This class provides the member functions to manage, converse to 
		another class and to dereference the data from specific database handler.
		
		BSON structure:
		{	
			$ref: \<collname\>,
			$id: \<idvalue\>,
		}
	*/
	class IdRef: public DataObj {
	
		protected:
			void initField(); ///< set the field names
		public:
			IdRef(); ///< Default constructor
			
			IdRef(mongo::BSONObj const& bsonObj); ///< Overloaded constructor get a BSONObj as parameters.
			
			IdRef(std::string const& DBId, std::string const& collectionNS); ///< Overloaded constructor get a id string and collectionNS as parameters.
			
			void initMember(std::string const& DBId, std::string const& collectionNS); ///< 
			
			std::string getId() const; ///< Return Id string
			
			std::string getNS() const;
			
			bool isValid() const; ///< Check validity of class
			
//			mongo::BSONObj fetch(Database & db) const; ///< Derefernce this DBRef and return a boson object.
	};
	/** 
		\brief Identifier reference class specific to physicalentity collection namespace

		This class is the same as IdRef, but has specific collection namespace to physicalentity collection namespace.
	*/
	class PEIdRef: public IdRef {
	
		private:
			void initMember() {}
		public:
			
			PEIdRef() : IdRef("", "physicalentity") {} ///< Default constructor
			
			PEIdRef(mongo::BSONObj const& bsonObj) : IdRef(bsonObj) {}
			
			PEIdRef(std::string const& DBId) : IdRef(DBId, "physicalentity") {} ///< Overloaded constructor get a object id string as parameter.
			
			inline void setId(std::string const& DBId) { IdRef::initMember(DBId, "physicalentity"); }
	};
	/** 
		\brief Identifier reference class specific to Iinteraction collection namespace

		This class is the same as IdRef, but has specific collection namespace to interaction collection namespace.
	*/
	class IntIdRef: public IdRef {
	
		private:
			void initMember() {}
		public:
	
			IntIdRef() : IdRef("", "interaction") {} ///< Default constructor
			
			IntIdRef(mongo::BSONObj const& bsonObj) : IdRef(bsonObj) {}
		
			IntIdRef(std::string const& DBId) : IdRef(DBId, "interaction") {} ///< Overloaded constructor get a object id string as parameter.
			
			inline void setId(std::string const& DBId) { IdRef::initMember(DBId, "interaction"); }

	};
	/** 
		\brief Identifier reference class specific to obo collection namespace

		This class is the same as IdRef, but has specific collection namespace to obo collection namespace.
	*/
	class OntoIdRef: public IdRef {
	
		private:
			void initMember() {}
		public:
	
			OntoIdRef() : IdRef("", "ontology") {} ///< Default constructor
			
			OntoIdRef(mongo::BSONObj const& bsonObj) : IdRef(bsonObj) {}
		
			OntoIdRef(std::string const& DBId) : IdRef(DBId, "ontology") {} ///< Overloaded constructor get a object id string as parameter.
			
			inline void setId(std::string const& DBId) { IdRef::initMember(DBId, "ontology"); }

	};
	/** 
		\brief Data updating history class

		This class makes a editing time stamp of each data documents. Structure of Tracking class in boson document is 
		{oid: "Updated object id", activity: "activity of the update; such as, new object or change detail in abc field", timeStamp: "time stamp"}.
		
		BSON structure:
		{	
			oid: \<idvalue\>,
			activity: "xxx",
			timeStamp: \<dateTimeValue\>,
		}
	*/
	class Tracking: public DataObj {

		private:
			void initField();
		public:
			
			Tracking(mongo::BSONObj const& bsonObj);
			
			Tracking(std::string const& objectID, std::string const& activity); ///< Overloaded constructor to build class instance.
			
			std::string toString() const; ///< Return the string
	};
	/** 
		\brief Specific BSON object to manage general Literal data object

	*/
	class LiteralBSON: public mongo::BSONObj {
	
		private:
			
		public:
	
			LiteralBSON(); ///< Default constructor

	};
	

}

#endif

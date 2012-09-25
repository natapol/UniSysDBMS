/* 
	UniSysDB library
	Copyright (C) 2011 

	class Tracking

	

	Author: Natapol Pornputtapong <natapol@chalmers.se>
*/
#include "DBClass.h"
namespace unisys {
	DataObj::DataObj() { }
	
	DataObj::DataObj(mongo::BSONObj const& bsonObj)
	{
		DataObj::data = bsonObj;
	}
	
	bool DataObj::operator< (DataObj const& other) const
	{
		return DataObj::data < other.data;
	}
	
	bool DataObj::operator<= (DataObj const& other) const
	{
		return DataObj::data <= other.data;
	}
	
	bool DataObj::operator> (DataObj const& other) const
	{
		return DataObj::data > other.data;
	}
	
	bool DataObj::operator>= (DataObj const& other) const
	{
		return DataObj::data >= other.data;
	}
	
	bool DataObj::operator== (DataObj const& other) const
	{
		return DataObj::data == other.data;
	}
	
	bool DataObj::valid() const
	{
		return DataObj::data.valid();
	}
	
	std::string DataObj::md5()
	{
		DataObj::sort();
		return DataObj::data.md5();
	}
	
	mongo::BSONObj DataObj::toBSONObj()
	{
		DataObj::sort();
		return DataObj::data;
	}
	
	std::string DataObj::toString(bool isArray, bool full)
	{
		DataObj::sort();
		return DataObj::data.toString(isArray, full);
	}
	
	mongo::BSONElement DataObj::getField(std::string const& fieldName) const
	{
		return DataObj::data.getField(fieldName);
	}
	
	bool DataObj::hasField(std::string const& fieldName) const
	{
		return DataObj::data.hasField(fieldName.c_str());
	}
	
	bool DataObj::isOwned() const
	{
		return DataObj::data.isOwned();
	}
	
//	DataObj DataObj::getOwned() const
//	{
//		return DataObj(DataObj::data.getOwned());
//	}
	
	// Append
	
	void DataObj::appendElements(mongo::BSONObj x)
	{
		mongo::BSONObjBuilder tmp;
		tmp.appendElements(DataObj::data);
		tmp.appendElements(x);
		DataObj::data = tmp.obj();
	}
	
	void DataObj::appendElementsUnique(mongo::BSONObj x)
	{
		mongo::BSONObjBuilder tmp;
		tmp.appendElements(DataObj::data);
		tmp.appendElementsUnique(x);
		DataObj::data = tmp.obj();
	}
	
	void DataObj::appendAs(mongo::BSONElement const& e, std::string const& fieldName, bool substitute)
	{
		if (substitute) DataObj::removeField(fieldName);
		mongo::BSONObjBuilder tmp;
		tmp.appendElements(DataObj::data);
		tmp.appendAs(e, fieldName);
		DataObj::data = tmp.obj();
	}
	
	void DataObj::appendArray(std::string const& fieldName, int start, int stop)
	{
		if (start > stop)
			DataObj::appendArray(fieldName, BSON("start" << stop << "stop" << start));
		else
			DataObj::appendArray(fieldName, BSON("start" << start << "stop" << stop));
	}
	
	void DataObj::appendArray(std::string const& fieldName, mongo::BSONObj const& subObj)
	{
		mongo::BSONObjBuilder tmp;
		mongo::BSONObjIterator i(DataObj::data);
		
		bool isInsert = false;
		
		while ( i.more() ) {
			mongo::BSONElement e = i.next();
			const char *fname = e.fieldName();
			if(strcmp(fieldName.c_str(), fname)) {
				tmp.append(e);
			} else {
				std::vector<mongo::BSONElement>::const_iterator cit;
				std::vector<mongo::BSONElement> es = e.Array();
				
				mongo::BSONArrayBuilder arrayB;
				
				for (cit = es.begin(); cit != es.end(); cit++) {
					arrayB.append(*cit);
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
	
	void DataObj::append(std::string const& fieldName, const char *str, int sz, bool substitute)
	{
		if (substitute) DataObj::removeField(fieldName);
		mongo::BSONObjBuilder tmp;
		tmp.appendElements(DataObj::data);
		tmp.append(fieldName, str, sz);
		DataObj::data = tmp.obj();
	}
	
	void DataObj::set(std::string const& fieldName, std::string const& value)
	{
		DataObj::removeField(fieldName);
		if ( !value.empty() ) {
			DataObj::append(fieldName, value, false);
		}
	}
	
	void DataObj::set(std::string const& fieldName, int value)
	{
		DataObj::append(fieldName, value, true);
	}
	
	void DataObj::set(std::string const& fieldName, double value)
	{
		DataObj::append(fieldName, value, true);
	}
	
	void DataObj::set(std::string const& fieldName, const char * value)
	{
		DataObj::append(fieldName, value, true);
	}
	
	void DataObj::set(std::string const& fieldName, bool value)
	{
		DataObj::append(fieldName, value, true);
	}
	
	void DataObj::set(std::string const& fieldName, int start, int stop)
	{
		if (start > stop)
			DataObj::append(fieldName, BSON("start" << stop << "stop" << start));
		else
			DataObj::append(fieldName, BSON("start" << start << "stop" << stop));
	}
	
	void DataObj::appendTimeT(std::string const& fieldName, time_t dt, bool substitute)
	{
		if (substitute) DataObj::removeField(fieldName);
		mongo::BSONObjBuilder tmp;
		tmp.appendElements(DataObj::data);
		tmp.appendTimeT(fieldName, dt);
		DataObj::data = tmp.obj();
	}
	
	void DataObj::appendRegex(std::string const& fieldName, std::string const& regex, std::string const& options, bool substitute)
	{
		if (substitute) DataObj::removeField(fieldName);
		mongo::BSONObjBuilder tmp;
		tmp.appendElements(DataObj::data);
		tmp.appendRegex(fieldName, regex, options);
		DataObj::data = tmp.obj();
	}
	
	void DataObj::appendTimeStamp(std::string const& fieldName, bool substitute)
	{
		DataObj::appendTimeT(fieldName, time(NULL), substitute);
	}
	
	void DataObj::appendAsNumber(std::string const& fieldName, std::string const& data, bool substitute)
	{
		if (substitute) DataObj::removeField(fieldName);
		mongo::BSONObjBuilder tmp;
		tmp.appendElements(DataObj::data);
		tmp.appendAsNumber(fieldName, data);
		DataObj::data = tmp.obj();
	}
	
	void DataObj::appendNull(std::string const& fieldName, bool substitute)
	{
		if (substitute) DataObj::removeField(fieldName);
		mongo::BSONObjBuilder tmp;
		tmp.appendElements(DataObj::data);
		tmp.appendNull(fieldName);
		DataObj::data = tmp.obj();
	}
	
	void DataObj::appendCode(std::string const& fieldName, std::string const& code, bool substitute)
	{
		if (substitute) DataObj::removeField(fieldName);
		mongo::BSONObjBuilder tmp;
		tmp.appendElements(DataObj::data);
		tmp.appendCode(fieldName, code);
		DataObj::data = tmp.obj();
	}
	
	void DataObj::appendDBRef(std::string const& fieldName, std::string const& ns, mongo::OID const& oid, bool substitute)
	{
		if (substitute) DataObj::removeField(fieldName);
		mongo::BSONObjBuilder tmp;
		tmp.appendElements(DataObj::data);
		tmp.appendDBRef(fieldName, ns, oid);
		DataObj::data = tmp.obj();
	}
	
	void DataObj::genOID()
	{
		DataObj::removeField("_id");
		mongo::BSONObjBuilder tmp;
		tmp.appendElements(DataObj::data);
		tmp.genOID();
		DataObj::data = tmp.obj();
	}
	
	void DataObj::removeField(std::string const& fieldName)
	{
		mongo::BSONObjBuilder tmp;
		mongo::BSONObjIterator i(DataObj::data);
		while ( i.more() ) {
			mongo::BSONElement e = i.next();
			const char *fname = e.fieldName();
			if(strcmp(fieldName.c_str(), fname) )
				tmp.append(e);
		}
		DataObj::data = tmp.obj();
	}
	
	void DataObj::addWithCheck(mongo::BSONObj const& bsonObj)
	{
		mongo::BSONObjBuilder tmp;
		std::vector<std::string>::const_iterator cit;
		
		for (cit = DataObj::fieldSet.begin(); cit != DataObj::fieldSet.end() ; cit++) {
			if ( bsonObj.hasField((*cit).c_str()) ) {
				//if ( strcmp("relation", (*cit).c_str()) == 0 ) {
					//mongo::BSONArrayBuilder tmpJ;
					//mongo::BSONObjIteratorSorted j(bsonObj.getObjectField((*cit).c_str()));
					//while (j.more()) {
						//tmpJ.append(j.next());
					//}
					//tmp.append("relation", tmpJ.obj());
				//} else {
					//tmp.append( bsonObj.getField(*cit) );
				//}
				tmp.append( bsonObj.getField(*cit) );
			}
		}
		DataObj::data = tmp.obj();
	}
	
	void DataObj::addWithOutCheck(mongo::BSONObj const& bsonObj)
	{
		DataObj::data = bsonObj;
	}
	
	void DataObj::sort()
	{
		DataObj::addWithCheck(DataObj::data);
	}
	
	bool DataObj::isValid() const
	{
		std::set<std::string>::const_iterator cit;
		bool val = true;
		for ( cit = DataObj::requireField.begin(); cit != DataObj::requireField.end(); cit++ ) {
			if ( !DataObj::data.hasField((*cit).c_str()) )
				val = false;
		}
		return val;
	}
	
}
////g++ dataobject.cpp -lmongoclient -lboost_thread -lboost_system -lboost_filesystem -lboost_program_options -I/usr/include/mongo -I/data/Projects/UniSysDBLib/trunk -o test
//int main () {
//	unisys::DataObj test1(BSON("abc" << "123"));
//	unisys::DataObj test2(BSON("def" << "123"));
//	unisys::DataObj test3(BSON("def" << "456"));
//	std::cout << test1.toString() << std::endl;
//	std::cout << test1.isOwned() << std::endl;
//	std::cout << (test1 < test2) << std::endl;
//	std::cout << (test1 <= test2) << std::endl;
//	std::cout << (test1 > test2) << std::endl;
//	std::cout << (test1 >= test2) << std::endl;
//	std::cout << (test1 == test2) << std::endl;
//	std::cout << (test3 == test2) << std::endl;
//	std::cout << test1.md5() << std::endl;
//	std::cout << test1.toString() << std::endl;
//}

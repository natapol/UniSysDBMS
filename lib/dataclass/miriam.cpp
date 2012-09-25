/* 
   UniSysDB library
   Copyright (C) 2011 

   class Miriam

   Author: Natapol Pornputtapong <natapol@chalmers.se>
*/
#include "DBClass.h"


std::string cleanURLString(std::string const& str)
{
	std::string tmpStr;
	
	for (size_t i = 0; i < str.length(); i++) {
		switch (str.at(i))
		{
			case '\t': tmpStr.append("%09"); break;
			case '\n': tmpStr.append("%0A"); break;
			case ' ': tmpStr.append("%20"); break;
			case '!': tmpStr.append("%21"); break;
			case '"': tmpStr.append("%22"); break;
			case '$': tmpStr.append("%24"); break;
			case '%': tmpStr.append("%25"); break;
			case '&': tmpStr.append("%26"); break;
			case '*': tmpStr.append("%2A"); break;
			case '+': tmpStr.append("%2B"); break;
			case ',': tmpStr.append("%2C"); break;
//				case '-': tmpStr.append("%2D"); break;
			case '/': tmpStr.append("%2F"); break;
			case ':': tmpStr.append("%3A"); break;
			case ';': tmpStr.append("%3B"); break;
			case '<': tmpStr.append("%3C"); break;
			case '=': tmpStr.append("%3D"); break;
			case '>': tmpStr.append("%3E"); break;
			case '?': tmpStr.append("%3F"); break;
			case '@': tmpStr.append("%40"); break;
			default: tmpStr.append(1, str.at(i));
		}
	}
	return tmpStr;
	
}

namespace unisys {

	Miriam::Miriam()
	{
		
	}

	Miriam::Miriam(std::string const& id, std::string const& ns, unsigned int version)
	{
		Miriam::set(id, ns, version);
	
	}

	bool Miriam::operator<(const Miriam &other) const
	{
		return Miriam::toURI() < other.toURI();
	}
	
	bool Miriam::operator==(const Miriam &other) const
	{
		return Miriam::toURI().compare(other.toURI()) == 0;
	}
	
	void Miriam::setUri(std::string const& uri)
	{
		size_t colon1 = uri.find(":");
		size_t colon2 = uri.find(":", colon1 + 1);
		size_t colon3 = uri.find(":", colon2 + 1);
		size_t colon4 = uri.find(":", colon3 + 1);
		
		std::string tmpId;
		
		if (colon2 == std::string::npos) {
			Miriam::ns = uri.substr(0, colon1);
			tmpId = uri.substr(colon1 + 1, uri.length() - colon1 - 1);
		} else if (colon3 == std::string::npos) {
			Miriam::ns = uri.substr(0, colon1);
			tmpId = uri.substr(colon1 + 1, uri.length() - colon1 - 1);
		} else if (colon4 == std::string::npos) {
			Miriam::ns = uri.substr(colon2 + 1, colon3 - colon2 - 1);
			tmpId = uri.substr(colon3 + 1, uri.length() - colon3 - 1);
		} else {
			Miriam::ns = uri.substr(colon2 + 1, colon3 - colon2 - 1);
			tmpId = uri.substr(colon3 + 1, uri.length() - colon3 - 1);
		}
		
		size_t punkt = tmpId.find('.');
		
		if (punkt == std::string::npos) {
			Miriam::version = 0;
			Miriam::id = tmpId;
		} else {
			Miriam::version = atoi(tmpId.substr(punkt + 1, tmpId.size() - punkt - 1).c_str());
			Miriam::id = tmpId.substr(0, punkt);
		}
		
		size_t percentPos = Miriam::id.find('%');
		
		if (percentPos != std::string::npos) {
			if (Miriam::id.substr(percentPos, 3).compare("%3A") == 0)
				Miriam::id.replace(percentPos, 3, ":");
			else if (Miriam::id.substr(percentPos, 3).compare("%3a") == 0)
				Miriam::id.replace(percentPos, 3, ":");
		}
	}

	void Miriam::set(std::string const& id, std::string const& ns, unsigned int version)
	{
		if (ns.compare("") == 0) {
			if (boost::algorithm::starts_with(id, "urn:miriam:")) {
				Miriam::setUri(id);
				
				if (version > 0) {
					Miriam::version = version;
				}
				
			} else {
				Miriam::id = id;
				Miriam::ns = "unknown";
				Miriam::version = version;
			}
		} else {
			Miriam::id = id;
			Miriam::version = version;
			if (boost::algorithm::starts_with(ns, "urn:miriam:")) {
				Miriam::ns = ns;
				Miriam::ns.replace(0, 11, "");
			} else {
				Miriam::ns = ns;
			}
		}
		
		size_t percentPos = Miriam::id.find('%');
		
		if (percentPos != std::string::npos) {
			if (Miriam::id.substr(percentPos, 3).compare("%3A") == 0)
				Miriam::id.replace(percentPos, 3, ":");
			else if (Miriam::id.substr(percentPos, 3).compare("%3a") == 0)
				Miriam::id.replace(percentPos, 3, ":");
		}
	}
	
	std::string Miriam::toURI() const
	{
		
		if (Miriam::id.compare("") == 0) {
			return "";
		} else {
			size_t colonPos = Miriam::id.find(":");
			std::string tmpid = cleanURLString(Miriam::id);
			
			return "urn:miriam:" + Miriam::ns + ":" + tmpid;
		}
		
	}
	
	std::string Miriam::toId() const
	{
		return Miriam::id;
	}

	std::string Miriam::toDBId() const
	{
		return Miriam::ns + ":" + Miriam::id;
	}
	
	
	bool Miriam::isValid() const
	{
		if(Miriam::id.compare("") != 0 && Miriam::ns.compare("") != 0) {
			return true;
		} else {
			return false;
		}
	}
	
	
	// Miriam annotation with version code
	void Miriam::operator++(int number)
	{
		Miriam::version += number;
	}
	
	std::string Miriam::toURIWithVer() const
	{
		if (Miriam::id.compare("") == 0) {
			return "";
		} else {
			char buffer [10];
			sprintf(buffer, "%03d", Miriam::version);
			return "urn:miriam:" + Miriam::ns + ":" + Miriam::id + "." + buffer;
		}
	}
	
	std::string Miriam::toDBIdWithVer() const
	{
		char buffer [10];
		sprintf(buffer, "%03d", Miriam::version);
		return Miriam::ns + ":" + Miriam::id + "." + buffer;
	}
	
	void Miriam::increaseVer(int number)
	{
		Miriam::version += 1;
	}
	
}
////////////g++ miriam.cpp ../uni/uniString.cpp -lmongoclient -lboost_thread -lboost_system -lboost_filesystem -lboost_program_options -I/usr/include/mongo -I/data/Projects/UniSysDBLib/trunk -o test
//int main () 
//{
//	unisys::Miriam abc1 ("urn:miriam:obo.go:GO%3A0006915");
//	unisys::Miriam abc2 ("GO:0048869", "urn:miriam:obo.go");
//	std::set<unisys::Miriam> test;
//	test.insert(abc2);
//	test.insert(abc1);
//	std::set<unisys::Miriam>::iterator it;
//	for(it = test.begin(); it != test.end(); it++) {
//		std::cout << (*it).toURI() << std::endl;
//		std::cout << (*it).toId() << std::endl;
//		std::cout << (*it).toDBId() << std::endl;
//		std::cout << (*it).toDBIdWithVer() << std::endl;
//	}
//	abc1++;
//	std::cout << abc1.toDBIdWithVer() << std::endl;
//}

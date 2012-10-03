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

	Miriam::Miriam(std::string const& uri)
	{
		Miriam::set(uri);
	
	}

	bool Miriam::operator<(const Miriam &other) const
	{
		return Miriam::toURI() < other.toURI();
	}
	
	bool Miriam::operator==(const Miriam &other) const
	{
		return Miriam::toURI().compare(other.toURI()) == 0;
	}
	
	void Miriam::set(std::string const& uri)
	{
		using namespace boost::xpressive;
		using namespace regex_constants;
		
		//pattern = urn:miriam:domain.subdomain:id
		
		boost::xpressive::sregex ns_regex, domain_regex, subdomain_regex, id_regex, dn_regex, urn_regex;
		{
			domain_regex = +boost::xpressive::lower;
			subdomain_regex = +boost::xpressive::lower;
			ns_regex = domain_regex | ( domain_regex >> '.' >> subdomain_regex );
			id_regex = ( +boost::xpressive::set[ _w | '%' ] | 
				( +boost::xpressive::upper >> ':' >> +boost::xpressive::set[ _w ]) ) 
				>> boost::xpressive::repeat<0,1>( '.' >> +boost::xpressive::range('0','9'));
			urn_regex = (
							boost::xpressive::bos >> "urn:miriam:" 
							>> (s1= ns_regex)
							>> ':' >> (s2= id_regex) >> boost::xpressive::eos
						)
						|
						(
							boost::xpressive::bos >> (s1= ns_regex)
							>> ':' >> (s2= id_regex) >> boost::xpressive::eos
						);
		}

		smatch what;

		if(regex_search(uri, what, urn_regex))
		{
			 Miriam::ns = what[s1];
			 Miriam::id = what[s2];
			 
		}else{
			throw (ParsingError("MIRIAM parsing error!"));
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

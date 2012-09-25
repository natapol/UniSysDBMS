/* TEST Whole PSIMI */
#include "client/dbclient.h"
#include "database/database.h"
#include "database/query.h"
#include "database/updater.h"
#include "dataclass/LitClass.h"
#include "dataclass/ObjClass.h"
#include "dataclass/DBClass.h"
#include "parser/psimi.h"
#include "parser/xmlParser.h"
#include "exception/exception.h"
//#include "services/bioportal/restBioPortal.h"
#include "uni/uniString.h"
#include "boost/algorithm/string/join.hpp"

int main () {
    /////g++ -o psimiTest psimiTest.cpp parser/psimi.cpp parser/xmlParser.cpp -I/drives/c/MobaXterm/trunk/
    /////./psimiTest
    //test PSIMI class
    std::cout << "TEST PSIMI class functions" << std::endl;
    unisys::PSIMI psimiObj("parser/00016_psimi.xml"); //class object
    unisys::PSIMI::mapOfXMLNode mapContainer; //map container
    unisys::PSIMI::mapOfXMLNode::iterator it; //iterator index

    //test getNodeSource()
    printf("*--- <%s> ---*\n",psimiObj.getNodeSource().getName());
    std::cout << psimiObj.getNodeSource().getChildNode("names").getChildNode("shortLabel").getName() << ": " << psimiObj.getNodeSource().getChildNode("names").getChildNode("shortLabel").getText() << std::endl;
    printf("%s: %s\n", psimiObj.getNodeSource().getAttributeName(0),psimiObj.getNodeSource().getAttribute("release"));

    //test getNodeAvailabilityList()
    mapContainer = psimiObj.getNodeAvailabilityList(); //'availabilityList' container
    std::cout << "*--- <availabilityList> ---*" << std::endl;
    printf("No. of availability element = %i\n",(int)mapContainer.size()); //get number of 'availability' element and print
    for (it = mapContainer.begin(); it != mapContainer.end(); it++){
        std::cout << "- availability (id: "<< (*it).first << ") : Data = " << (*it).second.getText() << std::endl; //print map
    }

    //test getNodeExperimentList()
    mapContainer = psimiObj.getNodeExperimentList(); //'experimentList' container
    std::cout << "*--- <experimentList> ---*" << std::endl;
    printf("No. of experimentDescription element = %i\n",(int)mapContainer.size()); //get number of 'experimentDescription' element and print
    for (it = mapContainer.begin(); it != mapContainer.end(); it++){
        std::cout << "- experimentDescription (id: "<< (*it).first << ") : Data = " << (*it).second.getChildNode("interactionDetectionMethod").getChildNode("names").getChildNode("fullName").getText() << std::endl; //print map
    }

    //test getNodeInteractorList()
    mapContainer = psimiObj.getNodeInteractorList(); //'interactorList' container
    std::cout << "*--- <interactorList> ---*" << std::endl;
    printf("No. of interactor element = %i\n",(int)mapContainer.size()); //get number of 'interactor' element and print
    for (it = mapContainer.begin(); it != mapContainer.end(); it++){
        std::cout << "- interactor (id: "<< (*it).first << ") : Data = " << (*it).second.getChildNode("names").getChildNode("shortLabel").getText() << std::endl; //print map
    }

    //test getNodeInteractionList()
    mapContainer = psimiObj.getNodeInteractionList(); //'interactionList' container
    std::cout << "*--- <interactionList> ---*" << std::endl;
    printf("No. of interaction element = %i\n",(int)mapContainer.size()); //get number of 'interaction' element and print
    for (it = mapContainer.begin(); it != mapContainer.end(); it++){
        std::cout << "- interaction (id: "<< (*it).first << ") : Data = " << (*it).second.getChildNode("participantList").nChildNode() << std::endl; //print map
    }

    //test getNodeAttributeList()
    mapContainer = psimiObj.getNodeAttributeList(); //'attributeList' container
    std::cout << "*--- <attributeList> ---*" << std::endl;
    printf("No. of attribute element = %i\n",(int)mapContainer.size()); //get number of 'attribute' element and print
    for (it = mapContainer.begin(); it != mapContainer.end(); it++){
        std::cout << "- attribute (id: "<< (*it).first << ") : Data = " << (*it).second.getAttribute("name") << std::endl; //print map
    }
    std::cout << "END TEST functions\n" << std::endl;

    /////g++ -o psimiTest psimiTest.cpp database/psimiBatchInsert.cpp database/batchInsert.cpp database/database.cpp database/updater*.cpp database/query.cpp dataclass/*.cpp uni/*.cpp parser/psimi.cpp parser/xmlParser.cpp -lmongoclient -lboost_thread -lboost_filesystem -lboost_date_time -lboost_system -lboost_program_options -I/usr/include/mongo -I/home/natapol/Projects/UniSysDBLib/trunk
    /////./psimiTest
    //test BatchInsert Class
	std::cout << "TEST psimiBatchInsert class functions" << std::endl;
    unisys::Database c;
	c.connect("129.16.106.203");
	unisys::BatchInsert bi(&c);
    bi.insert(psimiObj,"unisys.interaction", 1,true);
	std::cout << "END TEST functions\n" << std::endl;
}

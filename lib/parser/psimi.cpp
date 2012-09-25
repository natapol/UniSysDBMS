/*
   UniSysDB library
   Copyright (C) 2011

   Class PSIMI

   Author: Kwanjeera Wanichthanarak <kwawan@chalmers.se>
*/


#include "psimi.h"

namespace unisys{
    /*  Class constructor for non-parameter passing.   */
    PSIMI::PSIMI(){
    }

    /*  Class constructor overloaded with PSI-MI XML2.5 file as an input.
     *  @param fileName is the path to the PSI-MI XML2.5 file.
    */
    PSIMI::PSIMI(std::string const& filename){
        PSIMI::parse(filename);
    }

    /*  Parse a PSI-MI XML2.5 input file.
     *  @param fileName is the path to the PSI-MI XML2.5 file.
    */
    void PSIMI::parse(std::string const& filename) throw (ParsingError){
        try{
            std::cout << "****--- START ELEMENT SUMMARIES ---****\n" << std::endl; //start

            //entrySet node
            XMLNode entrySet = XMLNode::parseFile(filename.c_str(),"entrySet"); //open and parse the XML file, at 'entrySet' node
            printf("***--- <%s> ---***\n",entrySet.getName()); //print node name
            int entSAttNo = entrySet.nAttribute(); //get number of attributes
            printf("No. of attributes = %i\n",entSAttNo); //print number of attributes
            int entSNo = entrySet.nChildNode(); //get number of child nodes
            printf("No. of child nodes = %d\n",entSNo);
            if (entSNo > 1){
                std::string er = "PSIMI parsing error: Only one entry element is allowed in the entrySet.\n"; //allow only one entry
                throw er;
            }

            //entry node
            XMLNode entry = entrySet.getChildNode("entry"); //at 'entry' node
            printf("**--- <%s> ---**\n",entry.getName()); //print node name
            int entNo = entry.nChildNode(); //get number of child nodes
            printf("No. of child nodes = %d\n",entNo);

            //source node
            source = entry.getChildNode("source"); //at 'source' node
            if(!source.isEmpty()){
                printf("*--- <%s> ---*\n",source.getName()); //print node name
                int souAttNo = source.nAttribute(); //get number of attributes
                printf("No. of attributes = %i\n",souAttNo); //print number of attributes
                int souNo = source.nChildNode(); //get number of child nodes
                printf("No. of child nodes = %d\n",souNo);
            }

            //availabilityList node and availability
            XMLNode availabilityListNode = entry.getChildNode("availabilityList"); //at 'availabilityList' node
            if(!availabilityListNode.isEmpty()){
                int avaListNo = availabilityListNode.nChildNode(); //get number of child nodes
                printf("*--- <%s> ---*\n",availabilityListNode.getName()); //print node name
                for (int i=0; i<avaListNo; i++){
                    availabilityList.insert(std::pair<std::string, XMLNode>(availabilityListNode.getChildNode("availability",i).getAttribute("id"), availabilityListNode.getChildNode("availability",i))); //create map container of 'availabilityList', containing 'availability' node(s)
                }
                printf("No. of availability element = %lu\n",availabilityList.size()); //get number of 'availability' element and print
                printf("\n");
            }

            //experimentList node and experimentDescription
            XMLNode experimentListNode = entry.getChildNode("experimentList"); //at 'experimentList' node
            if(!experimentListNode.isEmpty()){
                int expListNo = experimentListNode.nChildNode(); //get number of child nodes
                printf("*--- <%s> ---*\n",experimentListNode.getName()); //print node name
                for (int i=0; i<expListNo; i++){
                    experimentList.insert(std::pair<std::string, XMLNode>(experimentListNode.getChildNode("experimentDescription",i).getAttribute("id"), experimentListNode.getChildNode("experimentDescription",i))); //create map container of 'experimentList', containing 'experimentDescription' node(s)
                }
                printf("No. of experimentDescription element = %lu\n",experimentList.size()); //get number of 'experimentDescription' element and print
                printf("\n");
            }

            //interactorList node and interactor
            XMLNode interactorListNode = entry.getChildNode("interactorList"); //at 'interactorList' node
            if(!interactorListNode.isEmpty()){
                int intorListNo = interactorListNode.nChildNode(); //get number of child nodes
                printf("*--- <%s> ---*\n",interactorListNode.getName()); //print node name
                for (int i=0; i<intorListNo; i++){
                    interactorList.insert(std::pair<std::string, XMLNode>(interactorListNode.getChildNode("interactor",i).getAttribute("id"), interactorListNode.getChildNode("interactor",i))); //create map container of 'interactorList', containing 'interactor' node(s)
                }
                printf("No. of interactor element = %lu\n",interactorList.size()); //get number of 'interactor' element and print
                printf("\n");
            }

            //interactionList node and interaction
            XMLNode interactionListNode = entry.getChildNode("interactionList"); //at 'interactionList' node
            int intionListNo = interactionListNode.nChildNode(); //get number of child nodes
            if(interactionListNode.isEmpty()||intionListNo < 1){
                std::string er = "PSIMI parsing error: At least one interaction element is required."; //one interaction element is required
                throw er;
            }
            printf("*--- <%s> ---*\n",interactionListNode.getName()); //print node name
            for (int i=0; i<intionListNo; i++){
                interactionList.insert(std::pair<std::string, XMLNode>(interactionListNode.getChildNode("interaction",i).getAttribute("id"), interactionListNode.getChildNode("interaction",i))); //create container map of 'interactionList', containing 'interaction' node(s)
            }
            printf("No. of interaction element = %lu\n",interactionList.size()); //get number of 'interaction' element and print
            printf("\n");

            //attributeList node and attribute
            XMLNode attributeListNode = entry.getChildNode("attributeList"); //at 'attributeList' node
            if(!attributeListNode.isEmpty()){
                int attListNo = attributeListNode.nChildNode(); //get number of child nodes
                printf("*--- <%s> ---*\n",attributeListNode.getName()); //print node name
                for (int i=0; i<attListNo; i++){
                    attributeList.insert(std::pair<std::string, XMLNode>(attributeListNode.getChildNode("attribute",i).getAttribute("name"), attributeListNode.getChildNode("attribute",i))); //create map container of 'attributeList', containing 'attribute' node(s)
                }
                printf("No. of attribute element = %lu\n",attributeList.size()); //get number of 'attribute' element and print
                printf("\n");
            }
            std::cout << "****--- END ELEMENT SUMMARIES ---****\n" << std::endl; //end
        }
        catch (std::string str) {
			throw ParsingError(str);
		}
    }

    /*  Get 'source' node.  */
    XMLNode PSIMI::getNodeSource() const{
        return  PSIMI::source;
    }

    /*  Get 'availabilityList' container.  */
    PSIMI::mapOfXMLNode PSIMI::getNodeAvailabilityList() const{
        return PSIMI::availabilityList;
    }

    /* Get 'experimentList' container. */
    PSIMI::mapOfXMLNode PSIMI::getNodeExperimentList() const{
        return PSIMI::experimentList;
    }

    /* Get 'interactorList' container. */
    PSIMI::mapOfXMLNode PSIMI::getNodeInteractorList() const{
        return PSIMI::interactorList;
    }

    /* Get 'interactionList' container. */
    PSIMI::mapOfXMLNode PSIMI::getNodeInteractionList() const{
        return PSIMI::interactionList;
    }

    /* Get 'attributeList' container. */
    PSIMI::mapOfXMLNode PSIMI::getNodeAttributeList() const{
        return PSIMI::attributeList;
    }
}

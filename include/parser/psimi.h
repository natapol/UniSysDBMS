/*
   UniSysDB library
   Copyright (C) 2011

	Class PSIMI

   Author: Kwanjeera Wanichthanarak <kwawan@chalmers.se>
*/

/** \file psimi.h
    \brief It contains PSIMI class for parsing PSI-MI XML2.5 file.

    Molecular interaction data in Proteomics Standards Initiative Molecular Interaction XML (PSI-MI XML) format will be parsed as a PSIMI object.
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <set>
#include <map>
#include "parser/xmlParser.h"
#include "exception/exception.h"

#ifndef _UNISYSDB_PSIMI_H_
#define _UNISYSDB_PSIMI_H_

namespace unisys{

    /**
        \brief A PSIMI class is used for a data in PSI-MI XML2.5 file format.

        A PSIMI object contains an 'entry' element of the root element 'entrySet' of PSI-MI XML2.5 file. Functions are implemented for parsing data in PSI-MI XML format to UniSysDB.
    */
    class PSIMI{
        public:
            /** \var typedef std::map<std::string, XMLNode> mapOfXMLNode
                \brief A map container contains list of XML data.

                XMLNode [name]List contains list of sub-nodes [name]
                These nodes [name]List are parsed to following structure:
                map<key, XMLNode>
                where @param key      = value of attribute 'id' (of node 'availability', 'experimentDescription', 'interactor', 'interaction')
                                        or value of attribute 'name' (of node 'attribute')
                and   @param XMLNode  = sub-node [name]
            */
            typedef std::map<std::string, XMLNode> mapOfXMLNode;

            /** \var typedef std::map<std::string, std::string> mapOfStringString
                \brief A map container contains data in std::string.

                Data is kept in following structure:
                map<key,value>
                where @param key   = a key value
                and   @param value = a mapped value
            */
            typedef std::map<std::string, std::string> mapOfStringString;

            /** \brief Class constructor for non-parameter passing.

                Instantiate a PSIMI object.
            */
            PSIMI();

            /** \brief Class constructor overloaded with PSI-MI XML2.5 file as an input.

                Instantiate a PSIMI object using the given PSI-MI XML2.5 file.
                @param fileName is the path to the PSI-MI XML2.5 file.
            */
            PSIMI(std::string const& filename);

            /** \brief Parse a PSI-MI XML2.5 input file.

                @param fileName is the path to the PSI-MI XML2.5 file.
            */
            void parse(std::string const& filename) throw (ParsingError);

            /** \brief Get 'source' node.

                Return 'source' node.
            */
            XMLNode getNodeSource() const;

            /** \brief Get 'availabilityList' node.

                Return a map container of 'availability' elements.
            */
            mapOfXMLNode getNodeAvailabilityList() const;

            /** \brief Get 'experimentList' node.

                Return a map container of 'experimentDescription' elements.
            */
            mapOfXMLNode getNodeExperimentList() const;

            /** \brief Get 'interactorList' node.

                Return a map container of 'interactor' elements.
            */
            mapOfXMLNode getNodeInteractorList() const;

            /** \brief Get 'interactionList' node.

                Return a map container of 'interaction' elements.
            */
            mapOfXMLNode getNodeInteractionList() const;

            /** \brief Get 'attributeList' node.

                Return a map container of 'attribute' elements.
            */
            mapOfXMLNode getNodeAttributeList() const;

        private:
            XMLNode source; ///< an XMLNode object 'source'.
            mapOfXMLNode availabilityList; ///< A map container 'availabilityList', containing 0-multiple 'availability' elements.
            mapOfXMLNode experimentList; ///< A map container 'experimentList', containing 0-multiple 'experimentDescription' elements.
            mapOfXMLNode interactorList; ///< A map container 'interactorList', containing 0-multiple 'interactor' elements.
            mapOfXMLNode interactionList; ///< A map container 'interactionList', containing 1-multiple 'interaction' elements.
            mapOfXMLNode attributeList; ///< A map container 'attributeList', containing 0-multiple 'attribute' elements.
    };
}

#endif

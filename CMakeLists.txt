## cmake file for building UniSysDB library
## UniSysDB library
## Copyright (C) 2011 
## Author: Natapol Pornputtapong <natapol@chalmers.se>

## CMake compatibility issues:
CMAKE_MINIMUM_REQUIRED( VERSION 2.4.6 )
MARK_AS_ADVANCED(CMAKE_BACKWARDS_COMPATIBILITY)

## allow more human readable "if then else" constructs
SET( CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE )

## User section
PROJECT( UniSysDB )

# project version
SET( ${PROJECT_NAME}_MAJOR_VERSION 1 )
SET( ${PROJECT_NAME}_MINOR_VERSION 1 )
SET( ${PROJECT_NAME}_PATCH_LEVEL 0 )

SET( PROJECT_NUMBER ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_PATCH_LEVEL} )

SET( CMAKE_INSTALL_PREFIX test )

SET( CMAKE_MODULE_PATH ${CMAKE_HOME_DIRECTORY} )


##User changeable variable
SET( INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries" )
SET( INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files" )
OPTION( BUILD_DOCUMENTATION "Use Doxygen to create the HTML based API documentation" OFF )
OPTION( BUILD_LATEX_DOCUMENTATION "Use Doxygen to create the HTML based API documentation" OFF )

##CMAKE_C_FLAGS
##CMAKE_CXX_FLAGS

SET( usisys_header_dir
	include/database
	include/dataclass
	include/exception
	include/parser
	include/services )

SET( usisys_service_header_dir
	include/services/biomart
	include/services/bioportal
	include/services/miriam
	include/services/rest )

SET( unisys_header
	include/database/database.h
	include/database/updater.h
	include/database/query.h
	include/dataclass/DBClass.h
#	include/dataclass/objElement.h
	include/dataclass/LitClass.h
	include/dataclass/ObjClass.h
	include/exception/exception.h
	include/parser/biopax.h
	include/parser/oboXML.h
	include/parser/chebiowl.h
	include/parser/parser.h
	include/parser/xmlParser.h
	include/parser/psimi.h
	include/services/biomart/restBioMart.h
	include/services/bioportal/restBioPortal.h
	include/services/miriam/restMiriam.h
	include/services/rest/rest.h )


SET( unisys_source
	${unisys_header}
#	lib/database/batchInsert.cpp
	#lib/database/updaterRemove.cpp
#	lib/database/batchUpdater.cpp
	#lib/database/updaterUpdate.cpp
	#lib/database/database.cpp
	#lib/database/query.cpp
	#lib/database/updater.cpp
	lib/database/updaterInsert.cpp
	lib/dataclass/literalbson.cpp
	lib/dataclass/tracking.cpp
	lib/dataclass/miriam.cpp
	lib/dataclass/dataobject.cpp
	lib/dataclass/object.cpp
#	lib/dataclass/idref.cpp
#	lib/dataclass/objElement.cpp
	lib/dataclass/interaction.cpp
	#lib/dataclass/ontology.cpp
	lib/dataclass/LitClass.cpp
	lib/dataclass/physicalEntity.cpp
	lib/parser/oboXML.cpp
	lib/parser/biopax.cpp
	lib/parser/psimi.cpp
	lib/parser/biopaxobj.cpp
	lib/parser/chebiowlclass.cpp
	lib/parser/chebiowl.cpp
	lib/parser/stanza.cpp
	lib/parser/xmlParser.cpp
	lib/services/biomart/restBioMart.cpp
	lib/services/biomart/restBioMartResult.cpp
	lib/services/bioportal/restBioPortalSearchResult.cpp
	lib/services/bioportal/restBioPortalResult.cpp
	lib/services/bioportal/restBioPortalTermResult.cpp
	lib/services/bioportal/classbean.cpp
	lib/services/bioportal/restBioPortal.cpp
	lib/services/miriam/restMiriam.cpp
	lib/services/rest/rest.cpp )


FIND_PACKAGE(Boost)
FIND_PACKAGE(CURL)
FIND_PACKAGE(MongoDB)

##For gSOAP build
#FIND_PATH( GSOAP_INCLUDE_DIRS stdsoap2.h)
#FIND_PATH( GSOAP_IMPORT_DIRS stlvector.h
#	PATHS /usr/share/gsoap/import )
#FIND_LIBRARY( GSOAP_LIBRARIES gsoap++)
#FIND_PROGRAM( GSOAP_WSDL2H_EXECUTE wsdl2h )
#FIND_PROGRAM( GSOAP_SOAPCPP2_EXECUTE soapcpp2 )
#MESSAGE( STATUS "${GSOAP_INCLUDE_DIRS} ${GSOAP_IMPORT_DIRS} ${GSOAP_LIBRARIES} ${GSOAP_WSDL2H_EXECUTE} ${GSOAP_SOAPCPP2_EXECUTE} ")


if(BUILD_DOCUMENTATION OR BUILD_LATEX_DOCUMENTATION)
	FIND_PACKAGE(Doxygen)
	if (NOT DOXYGEN_FOUND)
		MESSAGE(FATAL_ERROR 
			"Doxygen is needed to build the documentation. Please install it correctly")
	endif()
	
	if (BUILD_DOCUMENTATION)
		SET(DOXYGEN_GENERATE_HTML "YES")
	else ()
		SET(DOXYGEN_GENERATE_HTML "NO")
	endif()
	
	if (BUILD_LATEX_DOCUMENTATION)
		SET(DOXYGEN_GENERATE_LATEX "YES")
	else ()
		SET(DOXYGEN_GENERATE_LATEX "NO")
	endif()
	
	#-- Configure the Template Doxyfile for our specific project
	CONFIGURE_FILE(docs/Doxyfile.in 
		docs/Doxyfile @ONLY )
	#-- Add a custom target to run Doxygen when ever the project is built
	ADD_CUSTOM_TARGET (docs ALL 
		COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
		WORKING_DIRECTORY docs
		SOURCES docs/Doxyfile )
		
	if (BUILD_LATEX_DOCUMENTATION)
		ADD_CUSTOM_COMMAND( TARGET docs
			POST_BUILD
			COMMAND make
			COMMAND cp refman.pdf ..
			COMMAND rm -rf ../latex
			WORKING_DIRECTORY docs/latex )
	endif()
	
	# IF you do NOT want the documentation to be generated EVERY time you build the project
	# then leave out the 'ALL' keyword from the above command.
endif()

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIRS}
	${CURL_INCLUDE_DIRS}
	${MongoDB_INCLUDE_DIR}
	${usisys_header_dir}
	${usisys_service_header_dir}
	include )

#LINK_DIRECTORIES( ${Boost_LIBRARY_DIRS} ) ##Global link directory for every library


SET( target_main_name unisysdb )

ADD_LIBRARY( ${target_main_name}_static STATIC ${unisys_source} )
SET_TARGET_PROPERTIES( ${target_main_name}_static PROPERTIES OUTPUT_NAME ${target_main_name} )
TARGET_LINK_LIBRARIES( ${target_main_name}_static ${Boost_LIBRARIES} ${CURL_LIBRARIES} ${MongoDB_LIBRARIES} )


ADD_LIBRARY( ${target_main_name}_shared SHARED ${unisys_source} )
SET_TARGET_PROPERTIES( ${target_main_name}_shared PROPERTIES PREFIX ${CMAKE_SHARED_LIBRARY_PREFIX} )
SET_TARGET_PROPERTIES( ${target_main_name}_shared PROPERTIES SUFFIX 
	${CMAKE_SHARED_LIBRARY_SUFFIX}.${PROJECT_NUMBER} )
SET_TARGET_PROPERTIES( ${target_main_name}_shared PROPERTIES OUTPUT_NAME ${target_main_name} )
TARGET_LINK_LIBRARIES( ${target_main_name}_shared ${Boost_LIBRARIES} ${CURL_LIBRARIES} ${MongoDB_LIBRARIES} )

INSTALL( TARGETS unisysdb_static DESTINATION ${INSTALL_LIB_DIR} )
INSTALL( TARGETS unisysdb_shared DESTINATION ${INSTALL_LIB_DIR} )
INSTALL( DIRECTORY ${unisys_header_dir} DESTINATION include/unisysdb)



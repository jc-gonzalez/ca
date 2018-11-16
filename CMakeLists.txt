#======================================================================
# CMakeLists.txt
# QPF - Prototype of QLA Processing Framework
# qpfgui - QPF HMI Application
#======================================================================
# Author: J C Gonzalez - 2015-2018
# Copyright (C) 2015-2018  Euclid SOC Team at ESAC
#======================================================================

cmake_minimum_required(VERSION 2.8.2)
cmake_policy (SET CMP0015 NEW)

set (MACOSX_CC clang)
set (MACOSX_CXX clang++)
set (MACOSX_CXX_FLAGS "-std=c++11 -stdlib=libc++")

set (MACOSX_DEBUG "-g -gmodules -glldb")

set (CMAKE_CC_COMPILER ${MACOSX_CXX})
set (CMAKE_CC_FLAGS "${CMAKE_CC_FLAGS} ${MACOSX_DEBUG}")

set (CMAKE_CXX_COMPILER ${MACOSX_CXX})
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MACOSX_DEBUG} ${MACOSX_CXX_FLAGS}")


project (ca)

set (caLib_src
  ca_types.cpp
  cell.cpp
  cellautom.cpp
  gameoflife.cpp
  plane.cpp
  rule.cpp
)

set (caLib_hdr
  ca_types.h
  cell.h
  cellautom.h
  gameoflife.h
  plane.h
  rule.h
)

set (caBin_src cellular_automata.cpp fits.cpp)

add_definitions(-DCMAKE_BUILD_TYPE=Debug)

include_directories (. ..
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_BINARY_DIR})

set (CA_LIB_DIR ${PWD})
link_directories (${CA_LIB_DIR})

#----------------------------------------------------------------------

add_library (ca SHARED ${caLib_src})
target_link_libraries (ca gd)
target_include_directories (ca PUBLIC . /usr/local/include)

#----------------------------------------------------------------------

add_executable(cellular_automata ${caBin_src})
add_dependencies (cellular_automata ca)
target_include_directories (cellular_automata PUBLIC . /usr/local/include)
target_link_libraries (cellular_automata ca gd cfitsio)
set_target_properties (cellular_automata PROPERTIES LINKER_LANGUAGE CXX)

install (TARGETS ca cellular_automata
         RUNTIME DESTINATION bin
         ARCHIVE DESTINATION lib
         LIBRARY DESTINATION lib)

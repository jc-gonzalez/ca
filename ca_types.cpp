/******************************************************************************
 * File:    ca_types.cpp
 *          This file is part of the Cellular Automata library
 *
 * Domain:  CellularAutomata.libca.ca_types
 *
 * Version: 0.3
 *
 * Date:    2018/11/13
 *
 * Author:  J C Gonzalez
 *
 * Copyright (C) 2015-2018 by J C Gonzalez
 *_____________________________________________________________________________
 *
 * Topic: General Information
 *
 * Purpose:
 *   Implement ServiceMng class
 *
 * Created by:
 *   J C Gonzalez
 *
 * Status:
 *   Prototype
 *
 * Dependencies:
 *   none
 *
 * Files read / modified:
 *   none
 *
 * History:
 *   See <Changelog>
 *
 * About: License Conditions
 *   See <License>
 *
 ******************************************************************************/

#include "ca_types.h"

////////////////////////////////////////////////////////////////////////////
// Namespace: QPF
// -----------------------
//
// Library namespace
////////////////////////////////////////////////////////////////////////////
//namespace QPF {

#ifdef T
#    undef T
#endif

#define T(x) std::string( #x )

const std::string NeighborhoodNames[] = { T_NEIGHBORHOOD_LIST };
const std::string BoundaryTypeNames[] = { T_BOUNDARYTYPE_LIST };

#undef T

//}

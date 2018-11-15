/******************************************************************************
 * File:    rule.h
 *          This file is part of the Cellular Automata library
 *
 * Domain:  CellularAutomata.libca.DockerMng
 *
 * Last update:  2.0
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
 *   Declare DockerMng class
 *
 * Created by:
 *   J C Gonzalez
 *
 * Status:
 *   Prototype
 *
 * Dependencies:
 *   Component
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

#ifndef RULE_H
#define RULE_H

//============================================================
// Group: External Dependencies
//============================================================

//------------------------------------------------------------
// Topic: System headers
//   none
//------------------------------------------------------------

//------------------------------------------------------------
// Topic: External packages
//   none
//------------------------------------------------------------

//------------------------------------------------------------
// Topic: Project headers
//   none
//------------------------------------------------------------
#include "plane.h"

////////////////////////////////////////////////////////////////////////////
// Namespace: QPF
// -----------------------
//
// Library namespace
////////////////////////////////////////////////////////////////////////////
//namespace QPF {

//======================================================================
// Class: Rule
//======================================================================
class Rule {
public:
    Rule(Neighborhood n = Moore, BoundaryType b = OpenBoundary)
        : neighborhood(n), boundary(b) {}
public:
    virtual void evaluate(Cell & c, Plane & plane) {}
public:
    Neighborhood neighborhood;
    BoundaryType boundary;
};

//}

#endif  /* RULE_H */

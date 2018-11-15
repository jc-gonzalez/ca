/******************************************************************************
 * File:    plane.h
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

#ifndef PLANE_H
#define PLANE_H

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
#include "cell.h"
#include "rule.h"

////////////////////////////////////////////////////////////////////////////
// Namespace: QPF
// -----------------------
//
// Library namespace
////////////////////////////////////////////////////////////////////////////
//namespace QPF {

//======================================================================
// Class: Plane
//======================================================================
class Plane {
public:
    Plane() {}
    Plane(int r, int c, Neighborhood n = Moore, BoundaryType b = OpenBoundary);
    Cell & operator()(int i, int j);
    int count(int i, int j);
    int sum(int i, int j);
    bool evaluate(RuleHdl rule, Plane & lastGenPlane);
public:
    int rows, cols;
    Neighborhood neighborhood;
    BoundaryType boundary;
private:
    CellMatrix cells;
};


//}

#endif  /* PLANE_H */

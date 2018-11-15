/******************************************************************************
 * File:    cell.h
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

#ifndef CELL_H
#define CELL_H

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
#include "ca_types.h"

////////////////////////////////////////////////////////////////////////////
// Namespace: QPF
// -----------------------
//
// Library namespace
////////////////////////////////////////////////////////////////////////////
//namespace QPF {

//======================================================================
// Class: Cell
//======================================================================
class Cell {
public:
    Cell() {}
    Cell(int xi, int xj, Neighborhood n = Moore, BoundaryType b = OpenBoundary)
        : i(xi), j(xj), neighborhood(n), boundary(b), state(0) {}
public:
    int i, j;
    Neighborhood neighborhood;
    BoundaryType boundary;
    int state;

};

//}

#endif  /* CELL_H */

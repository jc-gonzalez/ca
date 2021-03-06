/******************************************************************************
 * File:    gameoflife.h
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

#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

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
#include "rule.h"

////////////////////////////////////////////////////////////////////////////
// Namespace: QPF
// -----------------------
//
// Library namespace
////////////////////////////////////////////////////////////////////////////
//namespace QPF {

//======================================================================
// Class: GameOfLife
//======================================================================
class GameOfLife : public Rule {
public:
    GameOfLife(BoundaryType b = OpenBoundary)
        : Rule(Moore, b) {}
public:
    virtual void evaluate(Cell & c, Plane & plane);
};

//}

#endif  /* GAMEOFLIFE_H */

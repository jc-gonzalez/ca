/******************************************************************************
 * File:    gameoflife.cpp
 *          This file is part of the Cellular Automata library
 *
 * Domain:  CellularAutomata.libca.gameoflife
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

#include "gameoflife.h"

////////////////////////////////////////////////////////////////////////////
// Namespace: QPF
// -----------------------
//
// Library namespace
////////////////////////////////////////////////////////////////////////////
//namespace QPF {

//----------------------------------------------------------------------
// Method: evaluate
//----------------------------------------------------------------------
void GameOfLife::evaluate(Cell & c, Plane & plane)
{
    // The Rules
    // - For a space that is populated:
    //   . Each cell with one or no neighbors dies, as if by solitude.
    //   . Each cell with four or more neighbors dies, as if by overpopulation.
    //   . Each cell with two or three neighbors survives.
    // For a space that is empty or unpopulated
    //   . Each cell with three neighbors becomes populated.

    int count = plane.count(c.i, c.j);
    if (c.state > 0) {
        if (count < 2)      { c.state = 0; }
        else if (count > 3) { c.state = 0; }
        else                { c.state = 1; }
    } else {
        if (count == 3) { c.state = 1; }
    }
}

//}

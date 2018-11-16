/******************************************************************************
 * File:    cellautom.h
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

#ifndef CELLAUTOM_H
#define CELLAUTOM_H

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
// Class: CellularAutomaton
//======================================================================
class CellularAutomaton {
public:
    CellularAutomaton(int r, int c, RuleHdl rle,
                      Neighborhood n = Moore, BoundaryType b = OpenBoundary);
    void evolve(int ngen = 1, bool show = false);
    void place(int i, int j, std::vector<std::vector<int>> m);
    void fillWith(byte * m);
    void dumpToFile(std::string outFileName);
    void dumpToAnimFile(std::string outFileName, int scale = 1);
    void dumpToImageFile(std::string outFileName, int scale = 1);
    void clearHistory();
    void reset();
    void getStats(double & mean, double & stdev, 
                  double & max, double & min);
protected:
    void dumpPlaneToStream(Plane & plane, int ng, std::ostream & o);
private:
    int numOfRows;
    int numOfColumns;
    Neighborhood neighborhood;
    BoundaryType boundary;
    Generations generations;
    std::vector<int> generationIdx;
    int numOfGenerations;
    Plane plane;
    RuleHdl rule;
};

//}

#endif  /* CELLAUTOM_H */

/******************************************************************************
 * File:    cellautom.cpp
 *          This file is part of the Cellular Automata library
 *
 * Domain:  CellularAutomata.libca.cellautom
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

#include "cellautom.h"

////////////////////////////////////////////////////////////////////////////
// Namespace: QPF
// -----------------------
//
// Library namespace
////////////////////////////////////////////////////////////////////////////
//namespace QPF {

//----------------------------------------------------------------------
// Method: evolve
//----------------------------------------------------------------------
void CellularAutomaton::evolve(int ngen, bool show)
{
    for (int ng = 0; ng < ngen; ++ng) {
        // Store plane in generations vector
        generations.push_back(plane);
        numOfGenerations++;
        generationIdx.push_back(numOfGenerations);

        // Get latest plane
        Plane & lastPlane = generations[ng];

        // Evaluate rule for all the cells in a plane
        plane.evaluate(rule, lastPlane);

        // Show, if requested
        if (show) { dumpPlaneToStream(plane, generationIdx.at(ng), std::cout); }
    }
}

//----------------------------------------------------------------------
// Method: place
//----------------------------------------------------------------------
void CellularAutomaton::place(int i, int j, std::vector<std::vector<int>> m)
{
    for(int r = 0; r < m.size(); ++r) {
        for(int c = 0; c < m[r].size(); ++c) {
            plane(r + i, c + j).state = m[r][c];
        }
    }
}

//----------------------------------------------------------------------
// Method: dumpToFile
//----------------------------------------------------------------------
void CellularAutomaton::dumpToFile(std::string outFileName)
{
    std::ofstream ofs;
    ofs.open(outFileName, std::ofstream::out | std::ofstream::app);

    // Show, if requested
    for (int ng = 0; ng < generations.size(); ++ng) {
        dumpPlaneToStream(generations[ng], generationIdx.at(ng), ofs);
    }

   ofs.close();
}

//----------------------------------------------------------------------
// Method: dumpPlaneToStream
//----------------------------------------------------------------------
void CellularAutomaton::dumpPlaneToStream(Plane & plane, int ng, std::ostream & o)
{
    o << "\nGeneration #" << ng << '\n';
    for (int i = 0; i < numOfRows; ++i) {
        o << "\t\t";
        for (int j = 0; j < numOfColumns; ++j) {
            o << plane(i, j).state << ' ';
        }
        o << '\n';
    }
}

//----------------------------------------------------------------------
// Method: dumpToAnimFile
//----------------------------------------------------------------------
void CellularAutomaton::dumpToAnimFile(std::string outFileName, int scale)
{
    FILE * out = fopen(outFileName.c_str(), "wb");
    if (!out) {
        std::cerr << "ERROR: Can't create file " << outFileName << '\n';
        exit(1);
    }

    int theColor;
    gdImagePtr prev = NULL;
    gdImagePtr im = gdImageCreate(numOfRows * scale, numOfColumns * scale);
    if (!im) {
        std::cerr << "ERROR: Can't create image" << '\n';
        exit(1);
    }

    gdImageGifAnimBegin(im, out, 1, -1);

    for (int ng = 0; ng < generations.size(); ++ng) {

        gdImageColorAllocate(im, 255, 255, 255); /* allocate white as side effect */
        theColor = gdImageColorAllocate(im, ng % 255, ng % 255, ng % 255);

        Plane & plane = generations[ng];
        for (int i = 0; i < numOfRows; ++i) {
            for (int j = 0; j < numOfColumns; ++j) {
                int state = ng * plane(i, j).state;
                //theColor = gdImageColorAllocate(im, state, state, state);
                gdImageFilledRectangle(im,
                                       i * scale, j * scale,
                                       i * scale + (scale - 1), j * scale + (scale - 1),
                                       state);
            }
        }

        gdImageGifAnimAdd(im, out, 1, 0, 0, 10, 1, prev);

        if (prev) { gdImageDestroy(prev); }
        prev = im;
        im = gdImageCreate(numOfRows * scale, numOfColumns * scale);
    }

    gdImageGifAnimEnd(out);
    fclose(out);
}

//----------------------------------------------------------------------
// Method: clearHistory
//----------------------------------------------------------------------
void CellularAutomaton::clearHistory()
{
    // Clear the generations stored in memory
    generations.clear();
    generationIdx.clear();
}

//----------------------------------------------------------------------
// Method: reset
//----------------------------------------------------------------------
void CellularAutomaton::reset()
{
    clearHistory();
    numOfGenerations = 0;
}

//}

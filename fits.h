/******************************************************************************
 * File:    fits.h
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

#ifndef FITS_H
#define FITS_H

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
#include "fitsio.h"

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
// Class: Fits
//======================================================================
class Fits {
public:
    Fits();
    Fits(std::string name);

    void open(std::string name, int mode);
    void open(int mode);

    void readHeader();
    void dumpHeader();
    void close();

private:
    std::string fitsFileName;
    fitsfile * fptr;
    int status;
    int numOfKeys;
};

//}

#endif  /* FITS_H */

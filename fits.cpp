/******************************************************************************
 * File:    fits.cpp
 *          This file is part of the Cellular Automata library
 *
 * Domain:  CellularAutomata.libca.fits
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

#include "fits.h"

#include <cstdio>

////////////////////////////////////////////////////////////////////////////
// Namespace: QPF
// -----------------------
//
// Library namespace
////////////////////////////////////////////////////////////////////////////
//namespace QPF {

Fits::Fits()
{
}

Fits::Fits(std::string name) : fitsFileName(name)
{
}

void Fits::open(std::string name, int mode)
{
    fitsFileName = name;
    this->open(mode);
}

void Fits::open(int mode)
{
    fits_open_file(&fptr, fitsFileName.c_str(), mode, &status);
}

void Fits::readHeader()
{
    fits_get_hdrspace(fptr, &numOfKeys, NULL, &status);
}

void Fits::dumpHeader()
{
    char card[FLEN_CARD];

    for (int k = 1; k < numOfKeys; k++)  {
        fits_read_record(fptr, k, card, &status); /* read keyword */
        printf("%s\n", card);
    }
    printf("END\n\n");  /* terminate listing with END */
}

void Fits::close()
{
    fits_close_file(fptr, &status);

    if (status) {
        fits_report_error(stderr, status);
        exit(status);
    }
}


//}

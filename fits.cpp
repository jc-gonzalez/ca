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

    int n = getNumOfHDUs();
    for (int hdu = 1; hdu <= n; ++hdu) {
        moveToHDU(hdu);
        printf("HDU #%d - %d of %d - %d\n", hdu, currHDU, numOfHDUs, currHDUType);
        readHeader();

        for (int k = 1; k < numOfKeys; k++)  {
            fits_read_record(fptr, k, card, &status); /* read keyword */
            printf("%s\n", card);
        }
        printf("END\n\n");  /* terminate listing with END */
    }
}

void Fits::close()
{
    fits_close_file(fptr, &status);

    if (status) {
        fits_report_error(stderr, status);
        exit(status);
    }
}

int Fits::getNumOfHDUs()
{
    fits_get_num_hdus(fptr, &numOfHDUs, &status);
    return numOfHDUs;
}

bool Fits::moveToHDU(int n)
{
    if (n > numOfHDUs) { n = numOfHDUs; }
    if (n < 1) { n = 1; }
    fits_movabs_hdu(fptr, n, &currHDUType, &status);
    currHDU = n;
    return true;
}

bool Fits::moveToNextHDU()
{
    if (currHDU < numOfHDUs) { return moveToHDU(currHDU + 1); }
    else { return false; }
}

bool Fits::moveToPrevHDU()
{
    if (currHDU > 1) { return moveToHDU(currHDU - 1); }
    else { return false; }
}

int Fits::getHDUType()
{
    return currHDUType;
}

void Fits::getImageSize(int & dataType, std::vector<int> & axes)
{
    int bitpix;
    fits_get_img_type(fptr, &bitpix, &status);

    int naxis;
    fits_get_img_dim(fptr, &naxis, &status);

    long * naxes = new long [naxis];
    fits_get_img_size(fptr, naxis, naxes, &status);

    dataType = bitpix;
    for (int i = 0; i < naxis; ++i) { axes.push_back(naxes[i]); }

    delete [] naxes;
}

void Fits::getImage(unsigned short * img)
{
    int bitpix;
    fits_get_img_type(fptr, &bitpix, &status);

    int naxis;
    fits_get_img_dim(fptr, &naxis, &status);

    long * naxes = new long [naxis];
    fits_get_img_size(fptr, naxis, naxes, &status);

    long null_value = 0;
    int any_null;
    long fpixel[2] = {1, 1};
    long lpixel[2];
    long inc[2] = {1, 1};
    lpixel[0] = naxes[0];
    lpixel[1] = naxes[1];

    fits_read_subset(fptr, TUSHORT, fpixel, lpixel, inc, 
                     &null_value, img, &any_null, &status);

    delete [] naxes;
}

//}

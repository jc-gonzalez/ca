/******************************************************************************
 * File:    plane.cpp
 *          This file is part of the Cellular Automata library
 *
 * Domain:  CellularAutomata.libca.plane
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

#include "plane.h"

////////////////////////////////////////////////////////////////////////////
// Namespace: QPF
// -----------------------
//
// Library namespace
////////////////////////////////////////////////////////////////////////////
//namespace QPF {

//----------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------
Plane::Plane(int r, int c, Neighborhood n, BoundaryType b)
    : rows(r), cols(c), neighborhood(n), boundary(b)
{
    /*
    cells = new CellRow [rows];
    for (int i = 0; i < rows; ++i) {
        cells[i] = new Cell [cols];
        for (int j = 0; j < cols; ++j) {
            Cell & c = cells[i][j];
            c.i = i;
            c.j = j;
            c.neighborhood = n;
            c.boundary = b;
        }
    }
    */
    cells = std::vector< CellRow >(rows);
    for (int i = 0; i < rows; ++i) {
        cells[i] = std::vector< Cell >(cols);
        for (int j = 0; j < cols; ++j) {
            Cell & c = cells[i][j];
            c.i = i;
            c.j = j;
            c.neighborhood = n;
            c.boundary = b;
        }
    }
}

//----------------------------------------------------------------------
// Method: count
// Counts number of cells in the neighborhood with state > 0
//----------------------------------------------------------------------
int Plane::count(int i, int j)
{
    int cnt = 0;
    switch (neighborhood) {
    case Moore:
        for (int ni = i - 1; ni <= i + 1; ++ni) {
            for (int nj = j - 1; nj <= j + 1; ++nj) {
                cnt += (((ni == i) && (nj == j)) ? 0 :
                        (cells[ni][nj].state > 0 ? 1 : 0));
            }
        }
        break;
    default:
        break;
    }

    return cnt;
}

//----------------------------------------------------------------------
// Method: operator()
// Sum state values of cells in the neighborhood
//----------------------------------------------------------------------
int Plane::sum(int i, int j)
{
    int sm = 0;
    switch (neighborhood) {
    case Moore:
        for (int ni = i - 1; ni <= i + 1; ++ni) {
            for (int nj = j - 1; nj <= j + 1; ++nj) {
                sm += (((ni == i) && (nj == j)) ? 0 :
                       (cells[ni][nj].state > 0 ? cells[ni][nj].state : 0));
            }
        }
        break;
    default:
        break;
    }

    return sm;
}

//----------------------------------------------------------------------
// Method: sumProduct
// Sum state values of cells in the neighborhood mult. by vector weights
//----------------------------------------------------------------------
int Plane::sumProduct(int i, int j, std::vector<std::vector<double>> v)
{
    int sm = 0;
    switch (neighborhood) {
    case Moore:
        sm = ((cells[i-1][j-1].state * v[0][0]) +
              (cells[i-1][j].state * v[0][1]) +
              (cells[i-1][j+1].state * v[0][2]) +
              (cells[i][j-1].state * v[1][0]) +
              (cells[i][j].state * v[1][1]) +
              (cells[i][j+1].state * v[1][2]) +
              (cells[i+1][j-1].state * v[2][0]) +
              (cells[i+1][j].state * v[2][1]) +
              (cells[i+1][j+1].state * v[2][2]));
        break;
    default:
        break;
    }

    return sm;
}


//----------------------------------------------------------------------
// Method: operator()
//----------------------------------------------------------------------
Cell & Plane::operator()(int i, int j)
{
    return cells[i][j];
}

//----------------------------------------------------------------------
// Method: evaluate
//----------------------------------------------------------------------
bool Plane::evaluate(RuleHdl rule, Plane & lastGenPlane)
{
    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < cols - 1; ++j) {
            rule->evaluate(cells[i][j], lastGenPlane);
        }
    }
    return true;
}

//----------------------------------------------------------------------
// Method: getStats
//----------------------------------------------------------------------
void Plane::getStats(double & mean, double & stdev, 
                     double & max, double & min)
{
    double sum = 0.;
    double sum2 = 0.;
    double n = (double)(rows * cols);
    double mn = (double)(cells[0][0].state);
    double mx = mn;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            double c = (double)(cells[i][j].state);
            sum += c;
            sum2 += c * c;
            if (c < mn) { mn = c; }
            if (c > mx) { mx = c; }
        }
    }

    mean = sum / n;
    stdev = sqrt((sum2 / n) - (mean * mean));
    max = mx;
    min = mn;
}

//}

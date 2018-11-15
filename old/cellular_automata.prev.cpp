// -*- C++ -*-

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>

#include <gd.h>

// Declare lists of items

#ifdef T
#    undef T
#endif

#define T_NEIGHBORHOOD_LIST                     \
    T(Moore),                                   \
        T(ExtendedMoore),                       \
        T(VonNeumann),                          \
        T(ExtendedVonNeuman),                   \
        T(Manhattan2),                          \
        T(Manhattan3),                          \
        T(Manhattan4)

#define T_BOUNDARYTYPE_LIST                     \
    T(OpenBoundary),                            \
        T(PeriodicBoundary),                    \
        T(ReflectiveBoundary)

// Declare enumerated types and corresponding name strings

#define T(x) std::string( #x )

const std::string NeighborhoodNames[] = { T_NEIGHBORHOOD_LIST };
const std::string BoundaryTypeNames[] = { T_BOUNDARYTYPE_LIST };

#undef T
#define T(x) x

enum Neighborhood { T_NEIGHBORHOOD_LIST };
enum BoundaryType { T_BOUNDARYTYPE_LIST };

#undef T

// Forward declarations

class Cell;
class Plane;
class Rule;

//typedef Cell * CellRow;
//typedef CellRow * CellMatrix;
typedef std::vector<Cell> CellRow;
typedef std::vector<CellRow> CellMatrix;
typedef std::vector<Plane> Generations;
typedef Rule * RuleHdl;

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

//======================================================================
// Class: Rule
//======================================================================
class Rule {
public:
    Rule(Neighborhood n = Moore, BoundaryType b = OpenBoundary)
        : neighborhood(n), boundary(b) {}
public:
    virtual void evaluate(Cell & c, Plane & plane) {}
public:
    Neighborhood neighborhood;
    BoundaryType boundary;
};

//======================================================================
// Class: GameOfLife
//======================================================================
class GameOfLife : public Rule {
public:
    GameOfLife(BoundaryType b = OpenBoundary)
        : Rule(Moore, b) {}
public:
    virtual void evaluate(Cell & c, Plane & plane);
public:
    Neighborhood neighborhood;
    BoundaryType boundary;
};

//======================================================================
// Class: CellularAutomaton
//======================================================================
class CellularAutomaton {
public:
    CellularAutomaton(int r, int c, RuleHdl rle,
                      Neighborhood n = Moore, BoundaryType b = OpenBoundary)
        : numOfRows(r), numOfColumns(c), rule(rle),
          neighborhood(n), boundary(b), numOfGenerations(0)
    {
        plane = Plane(numOfRows, numOfColumns, neighborhood, boundary);
        numOfGenerations = 0;
    }
    void evolve(int ngen = 1, bool show = false);
    void place(int i, int j, std::vector<std::vector<int>> m);
    void dumpToFile(std::string outFileName);
    void dumpToAnimFile(std::string outFileName, int scale = 1);
    void clearHistory();
    void reset();
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
// Method: operator()
//----------------------------------------------------------------------
Cell & Plane::operator()(int i, int j)
{
    return cells[i][j];
}

//----------------------------------------------------------------------
// Method: operator()
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

//======================================================================
// Main function
//======================================================================
int main(int argc, char * argv[])
{
    int nrows = 30, ncols = 30;
    /*
    Plane plane(nrows, ncols);

    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            std::cout << i << ',' << j << ": " << plane(i, i).state << '\n';
        }
    }
    */

    RuleHdl gameOfLife = new GameOfLife();
    CellularAutomaton ca(nrows, ncols, gameOfLife, Moore, OpenBoundary);
    ca.place(14, 13, {{0,1,1,1,0},
                      {1,0,0,0,1},
                      {0,1,1,1,0}});
    ca.place(20, 20, {{0,1,1,1,0},
                      {1,0,0,0,1},
                      {0,1,1,1,0}});
    ca.place(8, 6, {{0,1,1,1,0},
                      {1,0,0,0,1},
                      {0,1,1,1,0}});

    ca.evolve(100);
    ca.dumpToFile("file.txt");

    ca.dumpToAnimFile("file.gif", 2);

    ca.clearHistory();

    ca.evolve(100);
    ca.dumpToFile("file.txt");
}

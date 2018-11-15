// -*- C++ -*-

#include "cellautom.h"
#include "gameoflife.h"

#include "fits.h"

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

    Fits fits;

    fits.open(std::string(argv[1]), READONLY);
    fits.readHeader();
    fits.dumpHeader();
    fits.close();

    return 0;
}

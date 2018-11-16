// -*- C++ -*-

#include "cellautom.h"
#include "gameoflife.h"

#include "fits.h"

#include <random>

class Random {
public: 
    Random(int m) { 
        rng.seed(std::random_device()()); 
        dist = new std::uniform_int_distribution<std::mt19937::result_type>(0,m);
    }
    int operator()() {
        return (*dist)(rng);
    }
private:
    std::mt19937 rng;
    std::uniform_int_distribution<std::mt19937::result_type> * dist;
};

//======================================================================
// Class: TestRule
//======================================================================
class TestRule : public Rule {
public:
    TestRule(BoundaryType b = OpenBoundary)
        : Rule(Moore, b) {
        Random r(10000);
        v = std::vector<std::vector<double>> {{r() * 0.0001, r() * 0.0001, r() * 0.0001},
                                              {r() * 0.0001, r() * 0.0001, r() * 0.0001},
                                              {r() * 0.0001, r() * 0.0001, r() * 0.0001}};
    }
public:
    virtual void evaluate(Cell & c, Plane & plane) {
        // The Rules
        // - For a space that is populated:
        //   . Each cell with one or no neighbors dies, as if by solitude.
        //   . Each cell with four or more neighbors dies, as if by overpopulation.
        //   . Each cell with two or three neighbors survives.
        // For a space that is empty or unpopulated
        //   . Each cell with three neighbors becomes populated.

        int count = plane.sumProduct(c.i, c.j, v);
        c.state = count;
    }
private:
    std::vector<std::vector<double>> v;
};

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
    {
    /*
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

    ca.reset();
    */
    }
    //===================================================

    Fits fits;

    fits.open(std::string(argv[1]), READONLY);
    fits.dumpHeader();
    
    fits.moveToHDU(atoi(argv[2]));

    int dataType;
    std::vector<int> axes;
    fits.getImageSize(dataType, axes);
    ncols = axes.at(0);
    nrows = axes.at(1);

    // In this example I assume the type is SHORT_IMG
    //
    // #define BYTE_IMG 8 /* 8-bit unsigned integers */
    // #define SHORT_IMG 16 /* 16-bit signed integers */
    // #define LONG_IMG 32 /* 32-bit signed integers */
    // #define LONGLONG_IMG 64 /* 64-bit signed integers */
    // #define FLOAT_IMG -32 /* 32-bit single precision floating point */
    // #define DOUBLE_IMG -64 /* 64-bit double precision floating p
    //

    unsigned short * img = nullptr;
    if (dataType == SHORT_IMG) { 
        img = new unsigned short [nrows * ncols];
    }

    fits.getImage(img);
    /*
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            std::cout << i << ',' << j << ": " << img[i * ncols + j] << '\n';    
        }    
    }
    */
    
    byte * scaledImg = new byte [nrows * ncols]; 

    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            int idx = i * ncols + j;
            unsigned short k = (img[idx] % 256);
            scaledImg[idx] = k; //(k < 10) ? 0 : 1;
            //std::cout << std::setw(4) << k << ' ' 
            //          << scaledImg[idx] << ' ';    
        }    
        //std::cout << '\n';    
    }
    

    fits.close();

    for (int k = 1; k < atoi(argv[4]); ++k) {
        RuleHdl rule = new TestRule();
        CellularAutomaton ca(nrows, ncols, rule, Moore, OpenBoundary);
        ca.fillWith(scaledImg);

        double mean, stdev, max, min;
        ca.getStats(mean, stdev, max, min);

        std::cout << k << ":  " 
                  << "Mean: " << mean << ", StDev: " << stdev << ", "
                  << "Min.: " << min << ", Max.: " << max << '\n';

        if (k == 1) { ca.dumpToImageFile("p0.png"); }

        ca.evolve(atoi(argv[3]));

        ca.dumpToFile("c.txt");
        //ca.dumpToAnimFile("c.gif");
        char name[20];
        sprintf(name, "p%d.png", k);
        ca.dumpToImageFile(std::string(name));
    }

    return 0;
}

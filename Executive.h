

#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "LinkedList.h"

class Executive
{
    public:
        void run();

    private:
        int menu();
        void listReversal();
        void compute();
        int computePermutations(int input);
        int computeCombinations(int input);
        void quadtree();
        void reportSimpleCellsIn(int** Q, int firstRow, int lastRow,
            int firstCol, int lastCol);

};

#endif

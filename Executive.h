

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
        void computeC();
        void quadtree();

};

#endif

/*
*   Author:     Andrew Monroe
*   Date:       10/14/16
*   File Name:  Executive.h
*   File Description: Header file for executive class.
*/

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
        /** @pre None.
		*   @post None.
		*/
        void run();

    private:
        /** @pre None.
		*   @post None.
		*   @return user's menu choice
		*/
        int menu();

        /** @pre None.
		*   @post None.
		*/
        void listReversal();

        /** @pre None.
		*   @post None.
		*/
        void compute();

        /** @pre input >= 0
		*   @post None.
		*   @return number of additive permutations of input
		*/
        int computePermutations(int input);

        /** #########################
		*/
        int computeCombinations(int input, int temp);

        /** @pre None.
		*   @post None.
		*/
        void quadtree();

        /** @pre None.
		*   @post None.
		*/
        void reportSimpleCellsIn(int** Q, int firstRow, int lastRow,
            int firstCol, int lastCol);

};

#endif

/*
*   Author:     Andrew Monroe
*   Date:       10/14/16
*   File Name:  Executive.cpp
*   File Description: Implementation for Executive class. Creates method
        definitions for each of Executive's methods.
*/

#include "Executive.h"

void Executive::run()
{
    int choice = menu();

    if (choice == 1)
    {
        listReversal();
    }
    else if (choice == 2)
    {
        compute();
    }
    else if (choice == 3)
    {
        quadtree();
    }
    else if (choice == 4)
    {

    }
    else
    {
        //this won't be possible in the final program
        std::cout << "ERROR. CRASHING NOW." << std::endl;
    }
}

int Executive::menu()
{
    int choice = 0;

    std::cout << "Select an option:" << std::endl;
    std::cout << "1. List Reversal" << std::endl;
    std::cout << "2. Compute c(n)" << std::endl;
    std::cout << "3. Quadtree" << std::endl;
    std::cout << "4. Quit" << std::endl;
    std::cout << std::endl;

    std::cout << "Choice: ";
    std::cin >> choice;

    return(choice);
}

void Executive::listReversal()
{
    std::string fileName = "";
    LinkedList<std::string> myList;
    std::string input;

    std::cout << "Enter a filename: ";
    std::cin.ignore(1, '\n');
    std::getline(std::cin, fileName);

    std::ifstream inFile;
    inFile.open(fileName);

    if (inFile.is_open())
    {
        while (!inFile.eof())
        {
            std::getline(inFile, input);

            if (input != "")
                myList.addBack(input);
        }
    }

    inFile.close();

    std::cout << std::endl;

    std::cout << "Original List:" << std::endl;
    for (int x = 1; x <= myList.getLength(); x++)
    {
        std::cout << "Entry " << x << ": " << myList.getEntry(x) << std::endl;
    }
    std::cout << std::endl;

    myList.reverseList();

    std::cout << "Reversed List: " << std::endl;

    for (int x = 1; x <= myList.getLength(); x++)
    {
        std::cout << "Entry " << x << ": " << myList.getEntry(x) << std::endl;
    }
}

void Executive::compute()
{
    int target = 0;
    char permutations = 'n';

    std::cout << "Let c(n) be the number of different groups of integers " <<
        "that can be chosen from the integers 1 through n-1 so that the " <<
        "integers in each group add up to n." << std::endl;
    std::cout << "Enter a value of n for c(n) to be evaluated at: ";
    std::cin >> target;

    std::cout << std::endl;

    std::cout << "Would you like to count permutations? (y/n)" << std::endl;
    std::cin >> permutations;

    if (permutations == 'y' || permutations == 'Y')
    {
        std::cout << "C(" << target << ") = " <<
            computePermutations(target)-1 << std::endl;
    }
    else if (permutations == 'n' || permutations == 'N')
    {
        std::cout << "C(" << target << ") = " <<
            computeCombinations(target)-1 << std::endl;
    }
}

int Executive::computePermutations(int input)
{
    int numPermutations = 0;

    if (input == 0)
    {
        return(1);
    }
    else if (input > 0)
    {
        for(int x = input; x > 0; x--)
        {
            numPermutations += computePermutations(input - x);
        }
    }
    else
    {
        throw(std::runtime_error("Unexpected value in computePermutations."));
    }

    return(numPermutations);
}

int Executive::computeCombinations(int input)
{
    int numCombinations = 0;

    if (input == 0)
    {
        return(0);
    }
    else if (input == 1)
    {
        return(1);
    }
    else if (input > 1)
    {
        numCombinations = computeCombinations(input - 1) +
            computeCombinations(input - 2);
    }
    else
    {
        throw(std::runtime_error("Unexpected value in computeCombinations."));
    }

    return(numCombinations);
}

void Executive::quadtree()
{
    std::string fileName;
    int** arr;

    arr = new int*[64];
    for (int x = 0; x < 64; x++)
        arr[x] = new int[64];

    std::cout << "Enter file name: ";
    std::cin >> fileName;
    std::cout << std::endl;

    std::ifstream inFile;
    inFile.open(fileName);

    if (inFile.is_open())
    {
        for (int x = 0; x < 64; x++)
        {
            for (int y = 0; y < 64; y++)
            {
                inFile >> arr[x][y];
            }
        }

        inFile.close();
    }
    else
    {
        throw(std::runtime_error("Invalid file name."));
    }

    reportSimpleCellsIn(arr, 0, 64, 0, 64);

    for (int x = 0; x < 64; x++)
        delete[] arr[x];
    delete[] arr;
}

void Executive::reportSimpleCellsIn(int** Q, int firstRow, int lastRow,
    int firstCol, int lastCol)
{
    int count = 0;

    for(int x = firstCol; x < lastCol; x++)
    {
        for (int y = firstRow; y < lastRow; y++)
        {
            count += Q[x][y];
        }
    }

    if (count == 0)
    {
        if (firstRow == lastRow-1)
        {
            std::cout << "Row\t" << firstRow;
        }
        else
        {
            std::cout << "Rows\t" << firstRow << "-" << lastRow-1;
        }
        if (firstCol == lastCol-1)
        {
            std::cout << "\tand column\t" << firstCol << ":\tEMPTY" << std::endl;
        }
        else
        {
            std::cout << "\tand columns\t" << firstCol << "-" <<
            lastCol-1 << ":\tEMPTY" << std::endl;
        }
    }
    else if (count == 1)
    {
        if (firstRow == lastRow-1)
        {
            std::cout << "Row\t" << firstRow;
        }
        else
        {
            std::cout << "Rows\t" << firstRow << "-" << lastRow-1;
        }
        if (firstCol == lastCol-1)
        {
            std::cout << "\tand column\t" << firstCol << ":\tONE" << std::endl;
        }
        else
        {
            std::cout << "\tand columns\t" << firstCol << "-" <<
            lastCol-1 << ":\tONE" << std::endl;
        }
    }
    else
    {
        reportSimpleCellsIn(Q, firstRow, (lastRow+firstRow)/2,
            firstCol, (lastCol+firstCol)/2);
        reportSimpleCellsIn(Q, (lastRow+firstRow)/2, lastRow,
            firstCol, (lastCol+firstCol)/2);
        reportSimpleCellsIn(Q, firstRow, (lastRow+firstRow)/2,
            (lastCol+firstCol)/2, lastCol);
        reportSimpleCellsIn(Q, (lastRow+firstRow)/2, lastRow,
            (lastCol+firstCol)/2, lastCol);
    }
}

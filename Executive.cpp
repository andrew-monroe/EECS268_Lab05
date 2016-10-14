/*
*   Author:     Andrew Monroe
*   Date:       10/14/16
*   File Name:  Executive.cpp
*   File Description: Implementation for Executive class. Creates method
*        definitions for each of Executive's methods.
*/

#include "Executive.h"

/*
*   implementation for the run method, loops, calling the menu method to get
*   user-input on what the program should do next
*/
void Executive::run()
{
    int choice = 0;

    try
    {
        while (choice != 4)
        {
            //get user's choice
            choice = menu();

            if (choice == 1)
            {
                try{
                    //reverse a list
                    listReversal();
                }
                catch(std::runtime_error &e)
                {
                    std::cout << "ERROR: " << e.what() << std::endl;
                    std::cout << std::endl;
                }
            }
            else if (choice == 2)
            {
                //compute C(n) as defined in prompt
                compute();
            }
            else if (choice == 3)
            {
                try{
                    //find "simple" regions of a 64x64 integer array of 0s and 1s
                    quadtree();
                }
                catch(std::runtime_error &e)
                {
                    std::cout << "ERROR: " << e.what() << std::endl;
                    std::cout << std::endl;
                }
            }
            else
            {
                //quit the program
                std::cout << "Goodbye!" << std::endl;
            }
        }
    }
    catch(std::exception &e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
        std::cout << std::endl;
    }
}

/*
*    implementation for the menu class, prints out the selection of options
*    to the user, then takes the user's input for their choice, then returns
*    that choice
*/
int Executive::menu()
{
    int choice = 0;

    //loop until user selects a valid choice
    do
    {
        //output menu
        std::cout << "Select an option:" << std::endl;
        std::cout << "1. List Reversal" << std::endl;
        std::cout << "2. Compute c(n)" << std::endl;
        std::cout << "3. Quadtree" << std::endl;
        std::cout << "4. Quit" << std::endl;
        std::cout << std::endl;

        //receive user input
        std::cout << "Choice: ";
        std::cin >> choice;

        //ensures user entered a valid choice
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Try again. "<< std::endl;
            std::cout << std::endl;
            choice = 0;
        }
        else if (choice < 1 || choice > 4)
        {
            std::cout << "Invalid choice. Try again." << std::endl;
            std::cout << std::endl;
        }
    } while (choice < 1 || choice > 4);

    return(choice);
}

/*
*   implementation for the listReversal method, user names a file with a list
*   strings in it, the method reads that file into a LinkedList variable, the
*   method then prints the list, reverses it, then prints the new list
*/
void Executive::listReversal()
{
    //variables
    std::string fileName = "";
    LinkedList<std::string> myList;
    std::string input;

    //get user input for a file name
    std::cout << "Enter a filename: ";
    std::cin.ignore(1, '\n');
    std::getline(std::cin, fileName);

    //create an in file object and open the user-specified file
    std::ifstream inFile;
    inFile.open(fileName);

    //if the file could be opened, loop through the file's list entries and
    //  add them to myList
    if (inFile.is_open())
    {
        while (!inFile.eof())
        {
            std::getline(inFile, input);

            if (input != "")
                myList.addBack(input);
        }
    }
    else
    {
        throw(std::runtime_error("File named " + fileName +
            " could not be found."));
    }

    //no more use for in file, close it
    inFile.close();

    std::cout << std::endl;

    //print the original list
    std::cout << "Original List:" << std::endl;
    for (int x = 1; x <= myList.getLength(); x++)
    {
        std::cout << "Entry " << x << ": " << myList.getEntry(x) << std::endl;
    }
    std::cout << std::endl;

    //call reverseList method to reverse myList
    myList.reverseList();

    //print the reversed list
    std::cout << "Reversed List: " << std::endl;
    for (int x = 1; x <= myList.getLength(); x++)
    {
        std::cout << "Entry " << x << ": " << myList.getEntry(x) << std::endl;
    }

    std::cout << std::endl;
}

/*
*   Calculate c(n) as it has been specified below, either with or without
*   permutations included in the answer
*/
void Executive::compute()
{
    //variables
    int target = 0;
    char permutations = 'n';

    //describe c(n) and get user input for n
    std::cout << "Let c(n) be the number of different groups of integers " <<
        "that can be chosen from the integers 1 through n-1 so that the " <<
        "integers in each group add up to n." << std::endl;

    std::cout << std::endl;

    do
    {
        std::cout << "Enter a value of n for c(n) to be evaluated at: ";
        std::cin >> target;
        if (std::cin.fail() || target < 1)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Try again. "<< std::endl;
            std::cout << std::endl;
        }
    } while (target < 1);

    std::cout << std::endl;

    //find out if the user wants to count permutations or not
    std::cout << "Would you like to count permutations? (y/n)" << std::endl;

    do
    {
        std::cin >> permutations;

        std::cout << std::endl;

        //run with or without permutations depending on user's choice
        if (permutations == 'y' || permutations == 'Y')
        {
            std::cout << "C(" << target << ") = " <<
                computePermutations(target)-1 << std::endl;
        }
        else if (permutations == 'n' || permutations == 'N')
        {
            std::cout << "C(" << target << ") = " <<
                computeCombinations(target,1)-1 << std::endl;
        }
        else
        {
            std::cout << "Please answer with either y or n." << std::endl;
        }
    } while(permutations != 'y' && permutations != 'Y' &&
                permutations != 'n' && permutations != 'N');

    std::cout << std::endl;
}

/*
*   returns the number of permutations an integer has
*/
int Executive::computePermutations(int input)
{
    int numPermutations = 1;

    //sum up total of all of the numbers of permutations for numbers n-1 to input
    for(int x = 1; x < input; x++)
    {
        numPermutations += computePermutations(input - x);
    }

    //return the number of permutations found
    return(numPermutations);
}

/*
*   returns the number of combinations an integer has
*/
int Executive::computeCombinations(int input, int temp)
{
    int numCombinations = 0;

    for(int x = temp; x <= (input/2); x++)
    {
        numCombinations += computeCombinations(input - x, x) + 1;
    }

    return(numCombinations);
}

/*
*   implementation for quadtree method, takes in 64x64 array of integers from
*       an input file, puts them in an array, then finds biggest "simple"
*       regions and displays their location
*/
void Executive::quadtree()
{
    //variables
    std::string fileName;
    int** arr;

    //create the heap allocations necessary for the 64x64 array of integers
    arr = new int*[64];
    for (int x = 0; x < 64; x++)
        arr[x] = new int[64];

    //get the name of the input file from the user
    std::cout << "Enter file name: ";
    std::cin >> fileName;
    std::cout << std::endl;

    //open the user-specified input file
    std::ifstream inFile;
    inFile.open(fileName);

    //if the file exists, record each data value in its appropriate location in
    //  the array
    if (inFile.is_open())
    {
        for (int x = 0; x < 64; x++)
        {
            for (int y = 0; y < 64; y++)
            {
                inFile >> arr[x][y];
            }
        }

        //inFile is finished being used, close it
        inFile.close();
    }
    else //file did not open/did not exist
    {
        throw(std::runtime_error("Invalid file name."));
    }

    //call method to report all of the simple cells in the array
    reportSimpleCellsIn(arr, 0, 64, 0, 64);

    std::cout << std::endl;

    //deallocate the memory for the array
    for (int x = 0; x < 64; x++)
        delete[] arr[x];
    delete[] arr;
}

/*
*   reports the simple cells in a given array of integers, splits array into
*   four quadrents if one cell is not simple, and calls itself recursively on
*   each of the four quadrents
*/
void Executive::reportSimpleCellsIn(int** Q, int firstRow, int lastRow,
    int firstCol, int lastCol)
{
    int count = 0;

    //get sum of all values in the array
    for(int x = firstCol; x < lastCol; x++)
    {
        for (int y = firstRow; y < lastRow; y++)
        {
            count += Q[x][y];
        }
    }

    //if all values were zero, output that it was an empty cell
    if (count == 0)
    {
        //simple formatting organization and output
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
    //if the sum was 1, output that the value in the quadrent is one
    else if (count == 1)
    {
        //simple formatting organization and output
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
    //recursively call reportSimpleCellsIn on each quadrent
    else
    {
        //NW
        reportSimpleCellsIn(Q, firstRow, (lastRow+firstRow)/2,
            firstCol, (lastCol+firstCol)/2);
        //NE
        reportSimpleCellsIn(Q, (lastRow+firstRow)/2, lastRow,
            firstCol, (lastCol+firstCol)/2);
        //SW
        reportSimpleCellsIn(Q, firstRow, (lastRow+firstRow)/2,
            (lastCol+firstCol)/2, lastCol);
        //SE
        reportSimpleCellsIn(Q, (lastRow+firstRow)/2, lastRow,
            (lastCol+firstCol)/2, lastCol);
    }
}

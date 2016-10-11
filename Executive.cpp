

#include "Executive.h"

void Executive::run()
{
    int choice = menu();

    if (choice == 1)
    {

    }
    else if (choice == 2)
    {

    }
    else if (choice == 3)
    {

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

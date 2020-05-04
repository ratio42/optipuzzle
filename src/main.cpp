#include "includes/version.h"
#include "may2020/includes/may.h"

#include <iostream>

int main(int argc, char **argv)
{
    std::cout << "OptiPuzzle version: " << PROGRAM_VERSION__MAJOR << "." <<
        PROGRAM_VERSION__MINOR << "." << PROGRAM_VERSION__PATCH << std::endl << std::endl;
        
    std::cout << "Starting with May 2020: " << std::endl;
    May may;
    may.SearchSolution();
        
    return 0;
}

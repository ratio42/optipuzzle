#include "includes/may.h"
#include <iostream>

May::May() : m_PuzzleGrid()
{
}

void May::SearchSolution()
{
    std::cout << "The current grid is:" << std::endl << std:: endl;
    
    if (m_PuzzleGrid.IsValid()) {
        m_PuzzleGrid.PrintConfigurationWithPoints();    
    }
}


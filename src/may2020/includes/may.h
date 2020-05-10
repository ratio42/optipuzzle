#pragma once

#include "grid.h"

#include <map>

class May {
public:
    May();
    
    void SearchSolution();
    
private:
    Grid m_PuzzleGrid;

    /**
     * @brief Set numbers in the solution to find better solutions.
     */
    void SetNumbers();
    
    typedef std::map<int, int> NumbersToPlace_t;
    
    void FillNumbersRecursively(Grid currentGrid_p, NumbersToPlace_t numbersToPlace_p, int& pointsToBeat);
};
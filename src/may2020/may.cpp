#include "includes/may.h"
#include <iostream>
#include <thread>
#include <chrono>

#define FILL_WITH_TEST_SOLUTION

// stuff for threading 
static bool keyHit(false);

void KeyHitWaitTask()
{
    std::getchar();
    keyHit = true;
}


May::May() : m_PuzzleGrid()
{
#if defined(FILL_WITH_TEST_SOLUTION)
    m_PuzzleGrid.SetFieldAtPosition(1,0, GridTypes::W);
    m_PuzzleGrid.SetFieldAtPosition(2,0, GridTypes::W);
    m_PuzzleGrid.SetFieldAtPosition(0,1, GridTypes::W);
    m_PuzzleGrid.SetFieldAtPosition(1,1, GridTypes::W);
    m_PuzzleGrid.SetFieldAtPosition(0,2, GridTypes::W);
    
    m_PuzzleGrid.SetFieldAtPosition(4,0, GridTypes::P);
    m_PuzzleGrid.SetFieldAtPosition(5,0, GridTypes::P);
    m_PuzzleGrid.SetFieldAtPosition(6,0, GridTypes::P);
    m_PuzzleGrid.SetFieldAtPosition(4,1, GridTypes::P);
    m_PuzzleGrid.SetFieldAtPosition(5,1, GridTypes::P);
    
    m_PuzzleGrid.SetFieldAtPosition(9,0, GridTypes::V);
    m_PuzzleGrid.SetFieldAtPosition(10,0, GridTypes::V);
    m_PuzzleGrid.SetFieldAtPosition(11,0, GridTypes::V);
    m_PuzzleGrid.SetFieldAtPosition(11,1, GridTypes::V);
    m_PuzzleGrid.SetFieldAtPosition(11,2, GridTypes::V);
    
    m_PuzzleGrid.SetFieldAtPosition(0,4, GridTypes::I);
    m_PuzzleGrid.SetFieldAtPosition(1,4, GridTypes::I);
    m_PuzzleGrid.SetFieldAtPosition(2,4, GridTypes::I);
    m_PuzzleGrid.SetFieldAtPosition(3,4, GridTypes::I);
    m_PuzzleGrid.SetFieldAtPosition(4,4, GridTypes::I);
    
    m_PuzzleGrid.SetFieldAtPosition(7,2, GridTypes::X);
    m_PuzzleGrid.SetFieldAtPosition(6,3, GridTypes::X);
    m_PuzzleGrid.SetFieldAtPosition(7,3, GridTypes::X);
    m_PuzzleGrid.SetFieldAtPosition(8,3, GridTypes::X);
    m_PuzzleGrid.SetFieldAtPosition(7,4, GridTypes::X);
    
    m_PuzzleGrid.SetFieldAtPosition(11,4, GridTypes::T);
    m_PuzzleGrid.SetFieldAtPosition(9,5, GridTypes::T);
    m_PuzzleGrid.SetFieldAtPosition(10,5, GridTypes::T);
    m_PuzzleGrid.SetFieldAtPosition(11,5, GridTypes::T);
    m_PuzzleGrid.SetFieldAtPosition(11,6, GridTypes::T);
    
    m_PuzzleGrid.SetFieldAtPosition(3,6, GridTypes::N);
    m_PuzzleGrid.SetFieldAtPosition(4,6, GridTypes::N);
    m_PuzzleGrid.SetFieldAtPosition(5,6, GridTypes::N);
    m_PuzzleGrid.SetFieldAtPosition(5,7, GridTypes::N);
    m_PuzzleGrid.SetFieldAtPosition(6,7, GridTypes::N);
    
    m_PuzzleGrid.SetFieldAtPosition(1,7, GridTypes::F);
    m_PuzzleGrid.SetFieldAtPosition(0,8, GridTypes::F);
    m_PuzzleGrid.SetFieldAtPosition(1,8, GridTypes::F);
    m_PuzzleGrid.SetFieldAtPosition(2,8, GridTypes::F);
    m_PuzzleGrid.SetFieldAtPosition(0,9, GridTypes::F);
    
    m_PuzzleGrid.SetFieldAtPosition(2,10, GridTypes::Y);
    m_PuzzleGrid.SetFieldAtPosition(0,11, GridTypes::Y);
    m_PuzzleGrid.SetFieldAtPosition(1,11, GridTypes::Y);
    m_PuzzleGrid.SetFieldAtPosition(2,11, GridTypes::Y);
    m_PuzzleGrid.SetFieldAtPosition(3,11, GridTypes::Y);
    
    m_PuzzleGrid.SetFieldAtPosition(4,9, GridTypes::Z);
    m_PuzzleGrid.SetFieldAtPosition(5,9, GridTypes::Z);
    m_PuzzleGrid.SetFieldAtPosition(5,10, GridTypes::Z);
    m_PuzzleGrid.SetFieldAtPosition(5,11, GridTypes::Z);
    m_PuzzleGrid.SetFieldAtPosition(6,11, GridTypes::Z);
    
    m_PuzzleGrid.SetFieldAtPosition(8,7, GridTypes::U);
    m_PuzzleGrid.SetFieldAtPosition(9,7, GridTypes::U);
    m_PuzzleGrid.SetFieldAtPosition(8,8, GridTypes::U);
    m_PuzzleGrid.SetFieldAtPosition(8,9, GridTypes::U);
    m_PuzzleGrid.SetFieldAtPosition(9,9, GridTypes::U);
    
    m_PuzzleGrid.SetFieldAtPosition(11,8, GridTypes::L);
    m_PuzzleGrid.SetFieldAtPosition(11,9, GridTypes::L);
    m_PuzzleGrid.SetFieldAtPosition(11,10, GridTypes::L);
    m_PuzzleGrid.SetFieldAtPosition(10,11, GridTypes::L);
    m_PuzzleGrid.SetFieldAtPosition(11,11, GridTypes::L);
#endif
}

void May::FillNumbersRecursively(Grid currentGrid_p, NumbersToPlace_t numbersToPlace_p, int& pointsToBeat) {
    if (!keyHit) {
        int nextFreeX(0), nextFreeY(0);
        if (!currentGrid_p.GetNextFreeFieldPosition(nextFreeX, nextFreeY)) {
            //std::cout << "Solution found!" << std::endl;
            
            int currentPoints = currentGrid_p.Points_Get();
            if (currentPoints > pointsToBeat) {
                pointsToBeat = currentPoints;
                currentGrid_p.PrintConfigurationWithPoints();
            }
        } else  {        
            // fill with 1,2,3,4 or 5 and call recursively
            for (int numberToPlace = 1; numberToPlace <= 5; numberToPlace++) {
                if (numbersToPlace_p.at(numberToPlace) > 0) {
                    // c cast to Field_t is applicable here, as long as numbers in enum are defined correctly
                    currentGrid_p.SetFieldAtPosition(nextFreeX, nextFreeY, (GridTypes::Field_t)numberToPlace);                
                    numbersToPlace_p.at(numberToPlace)--;
                    FillNumbersRecursively(currentGrid_p, numbersToPlace_p, pointsToBeat);
                    
                    // restore condition from before
                    currentGrid_p.SetFieldAtPosition(nextFreeX, nextFreeY, GridTypes::empty);
                    numbersToPlace_p.at(numberToPlace)++;
                }
            }
        }
    }
}

void May::SetNumbers() {
    // numbers from 1 to 5 have to be placed 12 times each
    
    std::map<int, int> stillFreeNumbersToUse = {{1, 12}, {2, 12}, {3, 12}, {4, 12}, {5, 12}};
    int currentMaxPoints(-10000);
    
    FillNumbersRecursively(m_PuzzleGrid, stillFreeNumbersToUse, currentMaxPoints);
}

void May::SearchSolution()
{
    std::cout << "The current grid is:" << std::endl << std:: endl;
    
    if (m_PuzzleGrid.IsValid()) {
        m_PuzzleGrid.PrintConfigurationWithPoints();    
    }
    
    // start key press wait thread
    std::thread t1(KeyHitWaitTask);    
    
    SetNumbers();
    
    while (!keyHit) {
        // wait for keyHit, if not yet done
    }
    
    t1.join();    
}


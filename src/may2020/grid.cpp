#include "includes/grid.h"
#include <iostream>
#include <map>

#define FILL_WITH_TEST_SOLUTION

Grid::Grid() : m_SolutionGrid()
{
    // fill the blocked fields
    SetFieldAtPosition(7,0, GridTypes::blocked);
    SetFieldAtPosition(2,1, GridTypes::blocked); SetFieldAtPosition(7,1, GridTypes::blocked);
    SetFieldAtPosition(5,2, GridTypes::blocked);
    SetFieldAtPosition(4,3, GridTypes::blocked); SetFieldAtPosition(5,3, GridTypes::blocked); SetFieldAtPosition(10,3, GridTypes::blocked); SetFieldAtPosition(11,3, GridTypes::blocked);
    SetFieldAtPosition(8,4, GridTypes::blocked);
    SetFieldAtPosition(0,5, GridTypes::blocked); SetFieldAtPosition(1,5, GridTypes::blocked); SetFieldAtPosition(7,5, GridTypes::blocked); SetFieldAtPosition(8,5, GridTypes::blocked);
    SetFieldAtPosition(3,7, GridTypes::blocked); SetFieldAtPosition(4,7, GridTypes::blocked); SetFieldAtPosition(11,7, GridTypes::blocked);
    SetFieldAtPosition(9,8, GridTypes::blocked);
    SetFieldAtPosition(1,9, GridTypes::blocked); SetFieldAtPosition(2,9, GridTypes::blocked); SetFieldAtPosition(6,9, GridTypes::blocked); SetFieldAtPosition(10,9, GridTypes::blocked);
    SetFieldAtPosition(6,10, GridTypes::blocked);
    SetFieldAtPosition(4,11, GridTypes::blocked); SetFieldAtPosition(8,11, GridTypes::blocked);
    
#if defined(FILL_WITH_TEST_SOLUTION)
    SetFieldAtPosition(0,0, GridTypes::P);
    SetFieldAtPosition(0,1, GridTypes::P);
    SetFieldAtPosition(1,1, GridTypes::P);
    SetFieldAtPosition(0,2, GridTypes::P);
    SetFieldAtPosition(1,2, GridTypes::P);
    
    SetFieldAtPosition(3,0, GridTypes::L);
    SetFieldAtPosition(4,0, GridTypes::L);
    SetFieldAtPosition(3,1, GridTypes::L);
    SetFieldAtPosition(3,2, GridTypes::L);
    SetFieldAtPosition(3,3, GridTypes::L);
#endif
}

void Grid::SetFieldAtPosition(int x_p, int y_p, GridTypes::Field_t value_p) {  
    m_SolutionGrid.SetFieldAtPosition(x_p, y_p, value_p);
}

const GridTypes::Field_t& Grid::GetFieldAtPosition(int x_p, int y_p) const {
    return m_SolutionGrid.GetFieldAtPosition(x_p, y_p);
}

bool Grid::IsValid() const
{
    // The following things have to be checked:

    // each pentomino used
    // no pentomino used twice
    // no pentominos touch each other (not even diagonally)
    // each number is used as often as allowed
    
    // this method relies on the correct use of pentomino letters:
    // - no two different pentominos use same letters
    // - if if a letter is used, it describes that pentomino correctly
    
    ReasonForInvalidity_t reasonForInvalidity(NoReasonForInvalidity);

    // iterate till last row and column and check right, bottom and bottom right, bottom left
    for (int x = 0; x < MAX_COORDINATE_X - 1; x++) {
        for (int y = 0; y < MAX_COORDINATE_Y - 1; y++) {
            const GridTypes::Field_t& currentField = GetFieldAtPosition(x,y);
            
            if (IsPentomino(currentField)) {                
                // right
                const GridTypes::Field_t& rightNeighbor = GetFieldAtPosition(x+1, y);
                if (IsPentomino(rightNeighbor) && currentField != rightNeighbor) {
                    reasonForInvalidity = TwoPentominosTouches;
                    return false;
                }
                
                // bottom
                const GridTypes::Field_t& bottomNeighbor = GetFieldAtPosition(x, y+1);
                if (IsPentomino(bottomNeighbor) && currentField != bottomNeighbor) {
                    reasonForInvalidity = TwoPentominosTouches;
                    return false;
                }
                
                // bottom right
                const GridTypes::Field_t& bottomRightNeighbor = GetFieldAtPosition(x+1, y+1);
                if (IsPentomino(bottomRightNeighbor) && currentField != bottomRightNeighbor) {
                    reasonForInvalidity = TwoPentominosTouches;
                    return false;
                }
                
                // bottom left
                const GridTypes::Field_t& bottomLeftNeighbor = GetFieldAtPosition(x-1, y+1);
                if (IsPentomino(bottomLeftNeighbor) && currentField != bottomLeftNeighbor) {
                    reasonForInvalidity = TwoPentominosTouches;
                    return false;
                }
            }
        }    
    }
    
    return true;
}

void Grid::FillPentominosWithNumbers(InternalGrid& calculationGrid_p) const {
    std::map<GridTypes::Field_t, int> lastPentominoPlacedNumber;
    
    // iterate over solution grid in western world reading order
    // inner loop should be over x coordinate
    for (int y = 0; y < MAX_COORDINATE_Y; y++) {
        for (int x = 0; x < MAX_COORDINATE_X; x++) {
            GridTypes::Field_t currentField = GetFieldAtPosition(x,y);
            
            if (IsPentomino(currentField)) {
                std::map<GridTypes::Field_t, int>::iterator mapIterator =
                    lastPentominoPlacedNumber.find(currentField);
                    
                if (mapIterator == lastPentominoPlacedNumber.end()) {
                    calculationGrid_p.SetFieldAtPosition(x, y, GridTypes::number_1);
                    lastPentominoPlacedNumber.insert(std::make_pair(currentField, 1));
                } else {
                    calculationGrid_p.SetFieldAtPosition(x, y, (GridTypes::Field_t) ++(mapIterator->second));
                    // c cast is applicable here, as long as numbers in enum are defined correctly
                }
            } else {
                // copy content to calculation grid
                calculationGrid_p.SetFieldAtPosition(x, y, currentField);
            }
        }
    }
}

int Grid::Points_Get() const
{
    // two step process:
    // 1. enter numbers from placed pentominos    
    // 2. do point calculations
    
    int points(0);
    InternalGrid calculationGrid;

    FillPentominosWithNumbers(calculationGrid);
    
    for (int y = 0; y < MAX_COORDINATE_Y; y++) {
        for (int x = 0; x < MAX_COORDINATE_X; x++) {
            GridTypes::Field_t currentField = calculationGrid.GetFieldAtPosition(x,y);
            if (IsNumber(currentField)) {
                if (calculationGrid.SameNumberIsNeighboring(x, y, currentField)) {
                    // negative points
                    points -= (int) currentField * calculationGrid.SumOfAdjacentNumbers(x, y);
                } else {
                    // good case, be happy: positive points
                    points += (int) currentField + calculationGrid.SumOfAdjacentNumbers(x, y);
                }
            }
        }
    }
    
    return points;
}

static char GetLetterRepresentation(GridTypes::Field_t field_p) {
    switch (field_p) {
        case GridTypes::empty:
            return '.';
        case GridTypes::blocked:
            return 'x';        
        case GridTypes::F:
            return 'F';
        case GridTypes::I:
            return 'I';
        case GridTypes::L:
            return 'L';
        case GridTypes::N:
            return 'N';
        case GridTypes::P:
            return 'P';
        case GridTypes::T:
            return 'T';
        case GridTypes::U:
            return 'U';
        case GridTypes::V:
            return 'V';
        case GridTypes::W:
            return 'W';
        case GridTypes::X:
            return 'X';
        case GridTypes::Y:
            return 'Y';
        case GridTypes::Z:
            return 'Z';
            
        case GridTypes::number_1:
            return '1';
        case GridTypes::number_2:
            return '2';
        case GridTypes::number_3:
            return '3';
        case GridTypes::number_4:
            return '4';
        case GridTypes::number_5:
            return '5';
    }

    throw std::out_of_range("Field value out of range.");
}

void Grid::PrintConfigurationWithPoints() const
{
    // inner loop should be over x coordinate
    for (int y = 0; y < MAX_COORDINATE_Y; y++) {
        for (int x = 0; x < MAX_COORDINATE_X; x++) {
            std::cout << GetLetterRepresentation(GetFieldAtPosition(x,y));
        }
        std::cout << std::endl;
    }
    
    std::cout << std::endl << "Points: " << Points_Get() << std::endl;
}

// implementation of internal grid

InternalGrid::InternalGrid() : m_Grid({GridTypes::empty}) 
{
}

static void CheckPositionAccess(int x_p, int y_p) {
    if ((x_p > MAX_COORDINATE_X - 1) || (y_p > MAX_COORDINATE_Y - 1) ||
    (x_p < 0) || (y_p < 0))
    {
        throw std::out_of_range("Field position out of range.");    
    }
}


void InternalGrid::SetFieldAtPosition(int x_p, int y_p, GridTypes::Field_t value_p) {
    CheckPositionAccess(x_p, y_p);
    
    // get real positions in internal grid
    int x(x_p + 1);
    int y(y_p + 1);   
    
    m_Grid[x][y] = value_p;
}

const GridTypes::Field_t& InternalGrid::GetFieldAtPosition(int x_p, int y_p) const {
    //CheckPositionAccess(x_p, y_p);
    
    // get real positions in internal grid
    int x(x_p + 1);
    int y(y_p + 1);   
    
    return m_Grid[x][y];
}

bool InternalGrid::SameNumberIsNeighboring(int x_p, int y_p, GridTypes::Field_t value_p) const
{
    GridTypes::Field_t currentField = GetFieldAtPosition(x_p, y_p);
    if (!Grid::IsNumber(currentField)) {
        throw std::invalid_argument("Field value is not a number.");
    }
    
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            if (y == 0 && x == 0) { continue; }
            if (GetFieldAtPosition(x_p + x, y_p + y) == currentField) {
                return true;
            }
        }
    }
        
    return false;
}

int InternalGrid::SumOfAdjacentNumbers(int x_p, int y_p) const
{
    int sum(0);
    
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            if (y == 0 && x == 0) { continue; }
            GridTypes::Field_t currentField = GetFieldAtPosition(x_p + x, y_p + y);
            if (Grid::IsNumber(currentField)) {
                sum += (int) currentField;
                // c cast is applicable here, as long as numbers in enum are defined correctly
            }
        }
    }
    
    return sum;
}

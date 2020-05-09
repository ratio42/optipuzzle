#include "includes/grid.h"
#include <iostream>
#include <map>

Grid::Grid() : m_SolutionGrid({empty})
{
    // fill the blocked fields
    SetFieldAtPosition(7,0, blocked);
    SetFieldAtPosition(2,1, blocked); SetFieldAtPosition(7,1, blocked);
    SetFieldAtPosition(5,2, blocked);
    SetFieldAtPosition(4,3, blocked); SetFieldAtPosition(5,3, blocked); SetFieldAtPosition(10,3, blocked); SetFieldAtPosition(11,3, blocked);
    SetFieldAtPosition(8,4, blocked);
    SetFieldAtPosition(0,5, blocked); SetFieldAtPosition(1,5, blocked); SetFieldAtPosition(7,5, blocked); SetFieldAtPosition(8,5, blocked);
    SetFieldAtPosition(3,7, blocked); SetFieldAtPosition(4,7, blocked); SetFieldAtPosition(11,7, blocked);
    SetFieldAtPosition(9,8, blocked);
    SetFieldAtPosition(1,9, blocked); SetFieldAtPosition(2,9, blocked); SetFieldAtPosition(6,9, blocked); SetFieldAtPosition(10,9, blocked);
    SetFieldAtPosition(6,10, blocked);
    SetFieldAtPosition(4,11, blocked); SetFieldAtPosition(8,11, blocked);
}

static void CheckPositionAccess(int x_p, int y_p) {
    if ((x_p > MAX_COORDINATE_X - 1) || (y_p > MAX_COORDINATE_Y - 1) ||
    (x_p < 0) || (y_p < 0))
    {
        throw std::out_of_range("Field position out of range.");    
    }
}

void Grid::SetFieldAtPosition(int x_p, int y_p, Field_t value_p) {
    CheckPositionAccess(x_p, y_p);
    
    // get real positions in internal grid
    int x(x_p + 1);
    int y(y_p + 1);   
    
    m_SolutionGrid[x][y] = value_p;
}

const Grid::Field_t& Grid::GetFieldAtPosition(int x_p, int y_p) const {
    CheckPositionAccess(x_p, y_p);
    
    // get real positions in internal grid
    int x(x_p + 1);
    int y(y_p + 1);   
    
    return m_SolutionGrid[x][y];
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
    for (int x = 1; x < MAX_COORDINATE_X; x++) {
        for (int y = 1; y < MAX_COORDINATE_Y; y++) {
            const Field_t& currentField = GetFieldAtPosition(x,y);
            
            if (IsPentomino(currentField)) {                
                // right
                const Field_t& rightNeighbor = GetFieldAtPosition(x+1, y);
                if (IsPentomino(rightNeighbor) && currentField != rightNeighbor) {
                    reasonForInvalidity = TwoPentominosTouches;
                    return false;
                }
                
                // bottom
                const Field_t& bottomNeighbor = GetFieldAtPosition(x, y+1);
                if (IsPentomino(bottomNeighbor) && currentField != bottomNeighbor) {
                    reasonForInvalidity = TwoPentominosTouches;
                    return false;
                }
                
                // bottom right
                const Field_t& bottomRightNeighbor = GetFieldAtPosition(x+1, y+1);
                if (IsPentomino(bottomRightNeighbor) && currentField != bottomRightNeighbor) {
                    reasonForInvalidity = TwoPentominosTouches;
                    return false;
                }
                
                // bottom left
                const Field_t& bottomLeftNeighbor = GetFieldAtPosition(x-1, y+1);
                if (IsPentomino(bottomLeftNeighbor) && currentField != bottomLeftNeighbor) {
                    reasonForInvalidity = TwoPentominosTouches;
                    return false;
                }
            }
        }    
    }
    
    return true;
}

void Grid::FillPentominosWithNumbers(Grid_t& calculationGrid_p) const {
    std::map<Field_t, int> lastPentominoPlacedNumber;
    
    // iterate over solution grid in western world reading order
    // inner loop should be over x coordinate
    for (int y = 0; y < MAX_COORDINATE_Y; y++) {
        for (int x = 0; x < MAX_COORDINATE_X; x++) {
            Field_t currentField = GetFieldAtPosition(x,y);
            
            if (IsPentomino(currentField)) {
                std::map<Field_t, int>::iterator mapIterator =
                    lastPentominoPlacedNumber.find(currentField);
                    
                if (mapIterator == lastPentominoPlacedNumber.end()) {
                    calculationGrid_p[x+1][y+1] = number_1;
                    lastPentominoPlacedNumber.insert(std::make_pair(currentField, 1));
                } else {
                    calculationGrid_p[x+1][y+1] = (Field_t) ++(mapIterator->second);
                    // c cast is applicable here, as long as numbers in enum are defined correctly
                }
            } else {
                // copy content to calculation grid
                calculationGrid_p[x+1][y+1] = currentField;
            }
            
            // PH open issue: access to calculationGrid should also be performed via getter/setter
            // than we could get rid of that dangerous direct access with x+1 and y+1
        }
    }
}

int Grid::Points_Get() const
{
    // two step process:
    // 1. enter numbers from placed pentominos    
    // 2. do point calculations
    
    int points(0);
    Grid_t calculationGrid;

    FillPentominosWithNumbers(calculationGrid);
    
    for (int y = 0; y < MAX_COORDINATE_Y; y++) {
        for (int x = 0; x < MAX_COORDINATE_X; x++) {
            Field_t currentField = GetFieldAtPosition(x,y);
            if (IsNumber(currentField)) {
                if (SameNumberIsNeighboring(x, y, currentField)) {
                    // negative points
                    points -= (int) currentField * SumOfAdjacentNumbers(x, y);
                } else {
                    // good case, be happy: positive points
                    points += (int) currentField + SumOfAdjacentNumbers(x, y);
                }
            }
        }
    }
    
    return 0;
}

static char GetLetterRepresentation(Grid::Field_t field_p) {
    switch (field_p) {
        case Grid::empty:
            return '.';
        case Grid::blocked:
            return 'x';        
        case Grid::F:
            return 'F';
        case Grid::I:
            return 'I';
        case Grid::L:
            return 'L';
        case Grid::N:
            return 'N';
        case Grid::P:
            return 'P';
        case Grid::T:
            return 'T';
        case Grid::U:
            return 'U';
        case Grid::V:
            return 'V';
        case Grid::W:
            return 'W';
        case Grid::X:
            return 'X';
        case Grid::Y:
            return 'Y';
        case Grid::Z:
            return 'Z';
            
        case Grid::number_1:
            return '1';
        case Grid::number_2:
            return '2';
        case Grid::number_3:
            return '3';
        case Grid::number_4:
            return '4';
        case Grid::number_5:
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

bool Grid::SameNumberIsNeighboring(int x_p, int y_p, Field_t value_p) const
{
    Field_t currentField = GetFieldAtPosition(x_p, y_p);
    if (!IsNumber(currentField)) {
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

int Grid::SumOfAdjacentNumbers(int x_p, int y_p) const
{
    int sum(0);
    
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            if (y == 0 && x == 0) { continue; }
            Field_t currentField = GetFieldAtPosition(x_p + x, y_p + y);
            if (IsNumber(currentField)) {
                sum += (int) currentField;
                // c cast is applicable here, as long as numbers in enum are defined correctly
            }
        }
    }
}

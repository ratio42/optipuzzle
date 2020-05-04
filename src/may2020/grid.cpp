#include "includes/grid.h"
#include <iostream>

Grid::Grid()
{
    m_Fields = {MayGrid::empty};
}

bool Grid::IsValid() const
{
    /*// iterate over inner and check for neighbors
    for (int x = 1; x < MAX_COORDINATE_X - 1; x++) {
        for (int y = 1; y < MAX_COORDINATE_Y - 1; y++) {
            MarchBoard::letters_t currentLetter = GetLetterAtPosition(x,y);
            
            if (currentLetter != MarchBoard::X) {
                // check all 8 neighbors
                if (GetLetterAtPosition(x-1,y-1) == currentLetter) {
                    return false;            
                } 
                if (GetLetterAtPosition(x-1,y) == currentLetter) {
                    return false;            
                } 
                if (GetLetterAtPosition(x-1,y+1) == currentLetter) {
                    return false;            
                } 
                if (GetLetterAtPosition(x,y-1) == currentLetter) {
                    return false;            
                } 
                if (GetLetterAtPosition(x,y+1) == currentLetter) {
                    return false;            
                } 
                if (GetLetterAtPosition(x+1,y-1) == currentLetter) {
                    return false;            
                } 
                if (GetLetterAtPosition(x+1,y) == currentLetter) {
                    return false;            
                } 
                if (GetLetterAtPosition(x+1,y+1) == currentLetter) {
                    return false;            
                } 
            }
        }    
    }*/
    
    return true;
}

int Grid::Points_Get() const
{
    return 0;
}

static char GetLetterRepresentation(MayGrid::Field_t field_p) {
    switch (field_p) {
        case MayGrid::empty:
            return '.';
        case MayGrid::blocked:
            return 'x';        
        case MayGrid::F:
            return 'F';
        case MayGrid::I:
            return 'I';
        case MayGrid::L:
            return 'L';
        case MayGrid::N:
            return 'N';
        case MayGrid::P:
            return 'P';
        case MayGrid::T:
            return 'T';
        case MayGrid::U:
            return 'U';
        case MayGrid::V:
            return 'V';
        case MayGrid::W:
            return 'W';
        case MayGrid::X:
            return 'X';
        case MayGrid::Y:
            return 'Y';
        case MayGrid::Z:
            return 'Z';
    }

    throw std::out_of_range("Field value out of range.");
}


void Grid::PrintConfigurationWithPoints() const
{
    // inner loop should be over x coordinate
    for (int y = 0; y < MAX_COORDINATE_Y; y++) {
        for (int x = 0; x < MAX_COORDINATE_X; x++) {
            std::cout << GetLetterRepresentation(m_Fields[x][y]);
        }
        std::cout << std::endl;
    }
    
    std::cout << std::endl << "Points: " << Points_Get() << std::endl;
}

#pragma once

#include <array>

// grid is a 12x12 to filled with pentominos and numbers 1-5
// some fields are blocked from the beginning

// rules:
//  # each of the 12 pentominos must occur exactly once, and they are not allowed to touch each other
//  # remaining fields have to be filled with numbers 1-5, each number must occur exactly 12 times
//  # within a pentomino the numbers 1-5 are applied to the fields in western world reading order
//  # points for each field:
//    * if no same number touches: sum of number and adjacent numbers
//    * if at least one same number touches: (-1) * number * sum of adjacent numbers
//  # points for grid: sum of points of fields

// we start with arrays and enum values, there is a lot of room for speed approvement


// defines
#define MAX_COORDINATE_X  12
#define MAX_COORDINATE_Y  12

namespace GridTypes {
    enum Field_t {
        // empty (must be 0, since we access it that way)
        empty = 0,
        
        // numbers (must be 1-5, since we access them that way)        
        number_1 = 1,
        number_2 = 2,
        number_3 = 3,
        number_4 = 4,
        number_5 = 5,
        FirstNumber = number_1,
        LastNumber = number_5,
        
        blocked = 6,
        
        // 12 pentominos
        FirstPentomino = blocked + 1,
        F = FirstPentomino,
        I = FirstPentomino + 1,
        L = FirstPentomino + 2,
        N = FirstPentomino + 3,
        P = FirstPentomino + 4,
        T = FirstPentomino + 5,
        U = FirstPentomino + 6,
        V = FirstPentomino + 7,
        W = FirstPentomino + 8,
        X = FirstPentomino + 9,
        Y = FirstPentomino + 10,
        Z = FirstPentomino + 11,
        LastPentomino = Z
    };
    
    // we build an outer rim of one field to avoid any border checks
    typedef std::array< std::array <Field_t, MAX_COORDINATE_Y + 2>, MAX_COORDINATE_X + 2> Grid_t;    
}

// class InternalGrid holds only the values and implements setter and getter
// has to be separated from Grid we use for solution, since this uses internally
// some copies for operations, that doesn't need the full functionality
class InternalGrid {
public:
    InternalGrid();

    const GridTypes::Field_t& GetFieldAtPosition(int x_p, int y_p) const;
    void SetFieldAtPosition(int x_p, int y_p, GridTypes::Field_t value_p);    

    bool SameNumberIsNeighboring(int x_p, int y_p, GridTypes::Field_t value_p) const;
    int SumOfAdjacentNumbers(int x_p, int y_p) const;    
    
private:
    GridTypes::Grid_t m_Grid;
};

class Grid {
public:    
    enum ReasonForInvalidity_t {
        NoReasonForInvalidity,
        
        NotAllPentominosUsed,
        AtLeastOnePentominoTwice,
        TwoPentominosTouches,
        NotAllNumbersSet
    };

    /**
     * @brief Standard constructor
     */
    Grid();
    
    /**
     * @brief Returns true, if the current configuration is valid. (Applies to rule set.)
     */
    bool IsValid() const;

    /**
     * @brief Returns the number of points, the current configuration complies to, according to the rule set.
     */    
    int Points_Get() const;
    
    /**
     * @brief Outputs configuration and points in a human readable format.
     */
    void PrintConfigurationWithPoints() const;
    
    static bool IsNumber(GridTypes::Field_t field_p) {
        return (field_p >= GridTypes::FirstNumber && field_p <= GridTypes::LastNumber);
    }    
    
private:
    // holds the for solution placed information (pentomino tiles and numbers outside of pentominos)
    InternalGrid m_SolutionGrid;
    
    static bool IsPentomino(GridTypes::Field_t field_p) {
        return (field_p >= GridTypes::FirstPentomino && field_p <= GridTypes::LastPentomino);
    }
    const GridTypes::Field_t& GetFieldAtPosition(int x_p, int y_p) const;
    void SetFieldAtPosition(int x_p, int y_p, GridTypes::Field_t value_p);
    void FillPentominosWithNumbers(InternalGrid& calculationGrid_p) const;    
};
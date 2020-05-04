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

namespace MayGrid {
    enum Field_t {
        empty,
        blocked,
        
        // 12 pentominos
        F,
        I,
        L,
        N,
        P,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z
    };
}

// defines
#define MAX_COORDINATE_X  12
#define MAX_COORDINATE_Y  12

class Grid {
public:    
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

    
private:
    std::array< std::array <MayGrid::Field_t, MAX_COORDINATE_Y>, MAX_COORDINATE_X> m_Fields;

    // PH maybe initialize empty puzzle field already here
};
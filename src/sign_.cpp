// $Source$
//------------------------------------------------------------------------------
// sign_
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file sign_.cpp
*   @brief Source of the sign_ operation. Returns the absolute value of a with the sign of b.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#include <cmath>

// sign: returns absolute value of a with sign of b
double sign_(double a, double b) {
    if (b>=0.0){
        return fabs(a);
    } else {
        return - fabs(a);
    }
}
// $Source$
//------------------------------------------------------------------------------
// AccelPointMass
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file AccelPointMass.cpp
*   @brief Source of the AccelPointMass operation.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#include "..\include\matrix.hpp"
#include <cmath>

Matrix& AccelPointMass(Matrix& r, Matrix& s, double GM) {
    // Relative position vector of satellite w.r.t. point mass 
    Matrix& d = r - s;

    // Acceleration 
    Matrix& a = ( d/(pow(norm(d),3)) + s/(pow(norm(s),3)) ) * (-GM);

    return a;
}
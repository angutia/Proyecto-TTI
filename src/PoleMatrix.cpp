// $Source$
//------------------------------------------------------------------------------
// PoleMatrix
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file PoleMatrix.cpp
*   @brief Source of the PoleMatrix operation. It transforms coordinates from pseudo Earth-fixed to Earth-fixed for a given date.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#include "../include/matrix.hpp"
#include "../include/R_x.hpp"
#include "../include/R_y.hpp"

Matrix& PoleMatrix (double xp, double yp){
    Matrix& PoleMat = R_y(-xp) * R_x(-yp);

    return PoleMat;
}

// $Source$
//------------------------------------------------------------------------------
// GHAMatrix
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file GHAMatrix.cpp
*   @brief Source of the GHAMatrix operation. Transformation from true equator and equinox to Earth equator and Greenwich meridian system.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#include "../include/matrix.hpp"
#include "../include/gast.hpp"
#include "../include/R_z.hpp"

Matrix& GHAMatrix (double Mjd_UT1){
    Matrix& GHAmat = R_z( gast(Mjd_UT1) );

    return GHAmat;
}

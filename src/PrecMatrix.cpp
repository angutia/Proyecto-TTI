// $Source$
//------------------------------------------------------------------------------
// PrecMatrix
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file PrecMatrix.cpp
*   @brief Source of the PrecMatrix operation. Precession transformation of equatorial coordinates.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#include "../include/matrix.hpp"
#include "../include/SAT_Const.hpp"
#include "../include/R_y.hpp"
#include "../include/R_z.hpp"

Matrix& PrecMatrix (double Mjd_1, double Mjd_2){
    double T  = (Mjd_1-SAT_Const::MJD_J2000)/36525;
    double dT = (Mjd_2-Mjd_1)/36525;

    // Precession angles
    double zeta  =  ( (2306.2181+(1.39656-0.000139*T)*T)+((0.30188-0.000344*T)+0.017998*dT)*dT )*dT/SAT_Const::Arcs;
    double z     =  zeta + ( (0.79280+0.000411*T)+0.000205*dT)*dT*dT/SAT_Const::Arcs;
    double theta =  ( (2004.3109-(0.85330+0.000217*T)*T)-((0.42665+0.000217*T)+0.041833*dT)*dT )*dT/SAT_Const::Arcs;

    // Precession matrix
    Matrix& PrecMat = R_z(-z) * R_y(theta) * R_z(-zeta);

    return PrecMat;
}


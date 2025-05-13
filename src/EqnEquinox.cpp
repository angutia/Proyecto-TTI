// $Source$
//------------------------------------------------------------------------------
// EqnEquinox
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file EqnEquinox.cpp
*   @brief Source of the EqnEquinox operation. It computes the equation of the equinoxes.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#include "../include/NutAngles.hpp"
#include "../include/MeanObliquity.hpp"
#include <cmath>

double EqnEquinox (double Mjd_TT){
    // Nutation in longitude and obliquity
    auto [dpsi, deps] = NutAngles (Mjd_TT);

    // Equation of the equinoxes
    double EqE = dpsi * cos ( MeanObliquity(Mjd_TT) );
    
    return EqE;
}
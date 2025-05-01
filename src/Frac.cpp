// $Source$
//------------------------------------------------------------------------------
// Frac
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file Frac.cpp
*   @brief Source of the Frac operation. It computes the fractional part of a number (y=x-[x]).
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#include <cmath>

double Frac(double x){
    double res = x-floor(x);
    return res;
}
// $Source$
//------------------------------------------------------------------------------
// gast
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file gast.cpp
*   @brief Source of the gast operation. Greenwich Apparent Sidereal Time calculation.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#define _USE_MATH_DEFINES
#include <cmath>
#include "../include/gmst.hpp"
#include "../include/EqnEquinox.hpp"

double gast (double Mjd_UT1){
    double gstime = fmod ( gmst(Mjd_UT1) + EqnEquinox(Mjd_UT1), 2*M_PI );
    if(gstime < 0){
        gstime += 2*M_PI;
    }

    return gstime;
}
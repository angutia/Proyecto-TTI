// $Header$
//------------------------------------------------------------------------------
// JPL_Eph_DE430
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file JPL_Eph_DE430.hpp
*   @brief This header contains the JPL_Eph_DE430 operation. It computes the sun, moon, and nine major planets' equatorial position using JPL Ephemerides.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _JPL_EPH_DE430_
#define _JPL_EPH_DE430_

#include "../include/matrix.hpp"
#include <tuple>

using namespace std;

//------------------------------------------------------------------------------
// JPL_Eph_DE430(double Mjd_TDB)
//-------------------------------------------------------------------------------
/**
* @brief Computes the sun, moon, and nine major planets' equatorial position using JPL Ephemerides.
*
* @param [in] Mjd_TDB Modified julian date of TDB.
* @return r_Earth(solar system barycenter (SSB)),r_Mars,r_Mercury,r_Venus,r_Jupiter,r_Saturn,r_Uranus,r_Neptune,r_Pluto,r_Moon,r_Sun(geocentric equatorial position ([m]) referred to the International Celestial Reference Frame (ICRF)).
*/
//------------------------------------------------------------------------------
tuple<Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&> JPL_Eph_DE430(double Mjd_TDB);



#endif
// $Header$
//------------------------------------------------------------------------------
// IERS
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file IERS.hpp
*   @brief This header contains the IERS operation. Management of IERS time and polar motion data.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _IERS_
#define _IERS_

#include <tuple>
#include "../include/Matrix.hpp"

using namespace std;

//------------------------------------------------------------------------------
// IERS(Matrix& eop, double Mjd_UTC, char interp = 'n')
//-------------------------------------------------------------------------------
/**
* @brief Management of IERS time and polar motion data.
*
* @param [in] eop Earth Orientation Parameters (EOP) data.
* @param [in] Mjd_UTC Modified Julian Date in UTC.
* @param [in] interp Interpolation method ('l' for linear, 'n' for nearest).
* @return A tuple containing the x and y coordinates of the pole, UT1-UTC, LOD, dpsi, deps, dx_pole, dy_pole, and TAI-UTC.
*/
//------------------------------------------------------------------------------
tuple<double, double, double, double, double, double, double, double, double> IERS(Matrix& eop, double Mjd_UTC, char interp = 'n');



#endif
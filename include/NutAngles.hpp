// $Header$
//------------------------------------------------------------------------------
// NutAngles
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file NutAngles.hpp
*   @brief This header contains the NutAngles operation. Computes the nutation in longitude and obliquity.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _NUTANGLES_
#define _NUTANGLES_

#include <tuple>

using namespace std;

//------------------------------------------------------------------------------
// NutAngles (double Mjd_TT)
//-------------------------------------------------------------------------------
/**
* @brief Computes the nutation in longitude and obliquity.
*
* @param [in] Mjd_TT Modified Julian Date (Terrestrial Time).
* @return A tuple containing the nutation angles in longitude and obliquity.
*/
//------------------------------------------------------------------------------
tuple<double, double> NutAngles (double Mjd_TT);



#endif
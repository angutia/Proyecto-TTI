// $Header$
//------------------------------------------------------------------------------
// timediff
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file timediff.hpp
*   @brief This header contains the timediff operation. Returns the time differences in seconds.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _TIMEDIFF_
#define _TIMEDIFF_

#include <tuple>

using namespace std;

//------------------------------------------------------------------------------
// timediff(double UT1_UTC, double TAI_UTC)
//-------------------------------------------------------------------------------
/**
* @brief Returns the time differences in seconds.
*
* @param [in] UT1_UTC UT1-UTC time difference [s].
* @param [in] TAI_UTC TAI-UTC time difference [s].
* @return A tuple containing the time differences.
*/
//------------------------------------------------------------------------------
tuple<double, double, double, double, double> timediff(double UT1_UTC, double TAI_UTC);



#endif
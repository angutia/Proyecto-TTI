// $Header$
//------------------------------------------------------------------------------
// MeanObliquity
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file MeanObliquity.hpp
*   @brief This header contains the MeanObliquity operation. It computes the mean obliquity of the ecliptic.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _MEANOBLIQUITY_
#define _MEANOBLIQUITY_

#include <cmath>

//------------------------------------------------------------------------------
// MeanObliquity(double Mjd_TT)
//-------------------------------------------------------------------------------
/**
* @brief Computes the mean obliquity of the ecliptic.
*
* @param [in] Mjd_TT Modified Julian Date (Terrestrial Time).
* @return Mean obliquity of the ecliptic [rad].
*/
//------------------------------------------------------------------------------
double MeanObliquity (double Mjd_TT);



#endif
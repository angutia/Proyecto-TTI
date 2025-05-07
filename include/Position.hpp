// $Header$
//------------------------------------------------------------------------------
// Position
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file Position.hpp
*   @brief This header contains the Position operation. Computes the position vector (r [m]) from geodetic coordinates (Longitude [rad], latitude [rad], altitude [m]).
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _POSITION_
#define _POSITION_

#include "..\include\matrix.hpp"
#include <cmath>

//------------------------------------------------------------------------------
// Position(double lon, double lat, double h)
//-------------------------------------------------------------------------------
/**
* @brief Computes the position vector (r [m]) from geodetic coordinates (Longitude [rad], latitude [rad], altitude [m]).
*
* @param [in] lon Longitude [rad].
* @param [in] lat Latitude [rad].
* @param [in] h Altitude [m].
* @return Position vector (r [m]).
*/
//------------------------------------------------------------------------------
Matrix& Position(double lon, double lat, double h);



#endif
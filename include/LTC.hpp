// $Header$
//------------------------------------------------------------------------------
// LTC
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file LTC.hpp
*   @brief This header contains the LTC operation. It computes the transformation from Greenwich meridian system to local tangent coordinates.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _LTC_
#define _LTC_

#include "../include/matrix.hpp"

//------------------------------------------------------------------------------
// LTC(double lon, double lat)
//-------------------------------------------------------------------------------
/**
* @brief Computes the transformation from Greenwich meridian system to local tangent coordinates.
*
* @param [in] lon Geodetic East longitude [rad].
* @param [in] lat Geodetic latitude [rad].
* @return The rotation matrix from the Earth equator and Greenwich meridian to the local tangent (East-North-Zenith) coordinate system.
*/
//------------------------------------------------------------------------------
Matrix& LTC(double lon, double lat);



#endif
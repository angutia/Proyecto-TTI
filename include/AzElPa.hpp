// $Header$
//------------------------------------------------------------------------------
// AzElPa
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file AzElPa.hpp
*   @brief This header contains the AzElPa operation. Computes azimuth, elevation and partials from local tangent coordinates.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _AZELPA_
#define _AZELPA_

#include <tuple>
#include "../include/Matrix.hpp"

using namespace std;

//------------------------------------------------------------------------------
// AzElPa(Matrix& s)
//-------------------------------------------------------------------------------
/**
* @brief Computes azimuth, elevation and partials from local tangent coordinates.
*
* @param [in] s Topocentric local tangent coordinates (East-North-Zenith frame).
* @return A tuple containing azimuth, elevation, and their partials with respect to s.
*/
//------------------------------------------------------------------------------
tuple<double, double, Matrix&, Matrix&> AzElPa(Matrix& s);



#endif
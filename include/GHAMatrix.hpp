// $Header$
//------------------------------------------------------------------------------
// GHAMatrix
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file GHAMatrix.hpp
*   @brief This header contains the GHAMatrix operation. Transformation from true equator and equinox to Earth equator and Greenwich meridian system.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _GHAMATRIX_
#define _GHAMATRIX_

#include "../include/matrix.hpp"

//------------------------------------------------------------------------------
// GHAMatrix (double Mjd_UT1)
//-------------------------------------------------------------------------------
/**
* @brief Transformation from true equator and equinox to Earth equator and Greenwich meridian system.
*
* @param [in] Mjd_UT1 Modified Julian Date UT1
* @return Greenwich Hour Angle matrix
*/
//------------------------------------------------------------------------------
Matrix& GHAMatrix (double Mjd_UT1);



#endif
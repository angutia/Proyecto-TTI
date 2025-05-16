// $Header$
//------------------------------------------------------------------------------
// PrecMatrix
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file PrecMatrix.hpp
*   @brief This header contains the PrecMatrix operation. Precession transformation of equatorial coordinates.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _PRECMATRIX_
#define _PRECMATRIX_

#include "../include/matrix.hpp"

//------------------------------------------------------------------------------
// PrecMatrix (double Mjd_1, double Mjd_2)
//-------------------------------------------------------------------------------
/**
* @brief Precession transformation of equatorial coordinates
*
* @param [in] Mjd_1 Epoch given (Modified Julian Date TT)
* @param [in] Mjd_2 Epoch to precess to (Modified Julian Date TT)
* @return Precession transformation matrix.
*/
//------------------------------------------------------------------------------
Matrix& PrecMatrix (double Mjd_1, double Mjd_2);



#endif
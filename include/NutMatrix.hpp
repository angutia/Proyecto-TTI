// $Header$
//------------------------------------------------------------------------------
// NutMatrix
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file NutMatrix.hpp
*   @brief This header contains the NutMatrix operation. It computes the transformation from mean to true equator and equinox.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _NUTMATRIX_
#define _NUTMATRIX_

#include "../include/matrix.hpp"

//------------------------------------------------------------------------------
// NutMatrix (double Mjd_TT)
//-------------------------------------------------------------------------------
/**
* @brief Computes the transformation from mean to true equator and equinox.
*
* @param [in] Mjd_TT Modified Julian Date (Terrestrial Time).
* @return The nutation matrix from the mean equator and equinox to the true equator and equinox.
*/
//------------------------------------------------------------------------------
Matrix& NutMatrix (double Mjd_TT);



#endif
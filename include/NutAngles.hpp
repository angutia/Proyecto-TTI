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
*   @brief This header contains the NutAngles operation. 
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _NUTANGLES_
#define _NUTANGLES_

#include <tuple>
#include "../include/Matrix.hpp"

using namespace std;

//------------------------------------------------------------------------------
// Legendre(int n, int m, double fi)
//-------------------------------------------------------------------------------
/**
* @brief Legendre operation. Computes the Legendre polynomials and their derivatives.
*
* @param [in] n Degree of the polynomial.
* @param [in] m Order of the polynomial.
* @param [in] fi Angle in radians.
* @return A tuple containing the Legendre polynomials and their derivatives.
*/
//------------------------------------------------------------------------------
tuple<Matrix&, Matrix&> Legendre(int n, int m, double fi);



#endif
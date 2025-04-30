// $Header$
//------------------------------------------------------------------------------
// Cheb3D
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file Cheb3D.hpp
*   @brief This header contains the Cheb3D operation. Chebyshev approximation of 3-dimensional vectors.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _CHEB3D_
#define _CHEB3D_

#include "..\include\matrix.hpp"
#include <cmath>

//------------------------------------------------------------------------------
// AccelPointMass(Matrix& r, Matrix& s, double GM)
//-------------------------------------------------------------------------------
/**
* @brief Computes the perturbational acceleration due to a point mass
*
* @param [in] N Number of coefficients.
* @param [in] Ta Begin interval.
* @param [in] Tb End interval.
* @param [in] Cx Coefficients of Chebyshev polyomial (x-coordinate).
* @param [in] Cy Coefficients of Chebyshev polyomial (y-coordinate).
* @param [in] Cz Coefficients of Chebyshev polyomial (z-coordinate).
* @return Chebyshev approximation of 3-dimensional vectors
*/
//------------------------------------------------------------------------------
Matrix& Cheb3D(double t, int N, double Ta, double Tb, Matrix& Cx, Matrix& Cy, Matrix& Cz);



#endif
// $Header$
//------------------------------------------------------------------------------
// DEInteg
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file DEInteg.hpp
*   @brief This header contains the DEInteg operation. It contains the numerical integration methods for ordinaray differential equations. This module provides implemenation of the variable order variable stepsize multistep method of Shampine & Gordon.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _DEINTEG_
#define _DEINTEG_

#include "../include/matrix.hpp"

//------------------------------------------------------------------------------
// DEInteg(Matrix& func (double t, Matrix& Y), double t, double tout, double relerr, double abserr, int n_eqn, Matrix& y)
//-------------------------------------------------------------------------------
/**
* @brief Numerical integration methods for ordinaray differential equations. This module provides implemenation of the variable order variable stepsize multistep method of Shampine & Gordon.
*
* @param [in] func Function pointer to the function to be integrated
* @param [in] t Initial time
* @param [in] tout Final time
* @param [in] relerr Relative error tolerance
* @param [in] abserr Absolute error tolerance
* @param [in] n_eqn Number of equations to be integrated
* @param [in] y Initial state vector
* @return The resulting state vector
*/
//------------------------------------------------------------------------------
Matrix& DEInteg(Matrix& func (double t, Matrix& Y), double t, double tout, double relerr, double abserr, int n_eqn, Matrix& y);



#endif
// $Header$
//------------------------------------------------------------------------------
// MeasUpdate
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file MeasUpdate.hpp
*   @brief This header contains the MeasUpdate operation. Kalman filter measurement update.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _MEASUPDATE_
#define _MEASUPDATE_

#include "../include/matrix.hpp"
#include <tuple>

using namespace std;

//------------------------------------------------------------------------------
// MeasUpdate(Matrix& x, Matrix& z, Matrix& g, Matrix& s, Matrix& G, Matrix& P, int n)
//-------------------------------------------------------------------------------
/**
* @brief Kalman filter measurement update.
*
* @param [in] x State vector
* @param [in] z Measurement vector
* @param [in] g Measurement model
* @param [in] s Measurement noise
* @param [in] G Measurement matrix
* @param [in] P State covariance matrix
* @param [in] n State dimension
* @return Tuple containing the Kalman gain, updated state vector, and updated covariance matrix
*/
//------------------------------------------------------------------------------
tuple<Matrix&, Matrix&, Matrix&> MeasUpdate(Matrix& x, Matrix& z, Matrix& g, Matrix& s, Matrix& G, Matrix& P, int n);



#endif
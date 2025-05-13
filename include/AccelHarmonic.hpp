// $Header$
//------------------------------------------------------------------------------
// AccelHarmonic
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file AccelHarmonic.hpp
*   @brief This header contains the AccelHarmonic operation. Computes the acceleration due to the harmonic gravity field of the central body.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _ACCELHARMONIC_
#define _ACCELHARMONIC_

#include "../include/matrix.hpp"

//------------------------------------------------------------------------------
// AccelHarmonic(Matrix& r, Matrix& E, int n_max, int m_max)
//-------------------------------------------------------------------------------
/**
* @brief Computes the acceleration due to the harmonic gravity field of the central body.
*
* @param [in] r Satellite position vector in the inertial system.
* @param [in] E Transformation matrix to body-fixed system.
* @param [in] n_max Maximum degree.
* @param [in] m_max Maximum order (m_max<=n_max; m_max=0 for zonals, only).
* @return The acceleration (a=d^2r/dt^2).
*/
//------------------------------------------------------------------------------
Matrix& AccelHarmonic(Matrix& r, Matrix& E, int n_max, int m_max);



#endif
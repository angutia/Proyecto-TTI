// $Header$
//------------------------------------------------------------------------------
// G_AccelHarmonic
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file G_AccelHarmonic.hpp
*   @brief This header contains the G_AccelHarmonic operation. Computes the gradient of the Earth's harmonic gravity field.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _G_ACCELHARMONIC_
#define _G_ACCELHARMONIC_

#include "../include/matrix.hpp"

//------------------------------------------------------------------------------
// G_AccelHarmonic(Matrix& r, Matrix& U, int n_max, int m_max)
//-------------------------------------------------------------------------------
/**
* @brief Computes the gradient of the Earth's harmonic gravity field.
*
* @param [in] r Satellite position vector in the true-of-date system
* @param [in] U Transformation matrix to body-fixed system
* @param [in] n_max Gravity model degree
* @param [in] m_max Gravity model order
* @return Gradient (G=da/dr) in the true-of-date system
*/
//------------------------------------------------------------------------------
Matrix& G_AccelHarmonic(Matrix& r, Matrix& U, int n_max, int m_max);



#endif
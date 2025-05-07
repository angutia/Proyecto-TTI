// $Header$
//------------------------------------------------------------------------------
// R_x
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file R_x.hpp
*   @brief This header contains the R_x operation. Computes the rotation matrix around the x-axis.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _R_X_
#define _R_X_

#include "..\include\matrix.hpp"
#include <cmath>

//------------------------------------------------------------------------------
// R_x(double angle)
//-------------------------------------------------------------------------------
/**
* @brief Computes the rotation matrix around the x-axis.
*
* @param [in] angle Angle of rotation [rad].
* @return Vector result.
*/
//------------------------------------------------------------------------------
Matrix& R_x(double angle);



#endif
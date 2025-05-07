// $Header$
//------------------------------------------------------------------------------
// R_y
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file R_y.hpp
*   @brief This header contains the R_y operation. Computes the rotation matrix around the y-axis.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _R_Y_
#define _R_Y_

#include "..\include\matrix.hpp"
#include <cmath>

//------------------------------------------------------------------------------
// R_y(double angle)
//-------------------------------------------------------------------------------
/**
* @brief Computes the rotation matrix around the y-axis.
*
* @param [in] angle Angle of rotation [rad].
* @return Vector result.
*/
//------------------------------------------------------------------------------
Matrix& R_y(double angle);



#endif
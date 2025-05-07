// $Header$
//------------------------------------------------------------------------------
// R_z
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file R_z.hpp
*   @brief This header contains the R_z operation. Computes the rotation matrix around the z-axis.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _R_Z_
#define _R_Z_

#include "..\include\matrix.hpp"
#include <cmath>

//------------------------------------------------------------------------------
// R_z(double angle)
//-------------------------------------------------------------------------------
/**
* @brief Computes the rotation matrix around the z-axis.
*
* @param [in] angle Angle of rotation [rad].
* @return Vector result.
*/
//------------------------------------------------------------------------------
Matrix& R_z(double angle);



#endif
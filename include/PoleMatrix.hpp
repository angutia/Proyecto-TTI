// $Header$
//------------------------------------------------------------------------------
// PoleMatrix
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file PoleMatrix.hpp
*   @brief This header contains the PoleMatrix operation. It transforms coordinates from pseudo Earth-fixed to Earth-fixed for a given date.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _POLEMATRIX_
#define _POLEMATRIX_

#include "../include/matrix.hpp"

//------------------------------------------------------------------------------
// PoleMatrix (double xp, double yp)
//-------------------------------------------------------------------------------
/**
* @brief Transforms coordinates from pseudo Earth-fixed to Earth-fixed for a given date.
*
* @param [in] xp X-coordinate in pseudo Earth-fixed frame.
* @param [in] yp Y-coordinate in pseudo Earth-fixed frame.
* @return Pole matrix.
*/
//------------------------------------------------------------------------------
Matrix& PoleMatrix (double xp, double yp);



#endif
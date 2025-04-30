// $Header$
//------------------------------------------------------------------------------
// AccelPointMass
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file AccelPointMass.hpp
*   @brief This header contains the AccelPointMass operation.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _ACCELPOINTMASS_
#define _ACCELPOINTMASS_

#include "..\include\matrix.hpp"
#include <cmath>

//------------------------------------------------------------------------------
// AccelPointMass(Matrix& r, Matrix& s, double GM)
/**
* @brief Computes the perturbational acceleration due to a point mass
*
* @param [in] r Satellite position vector.
* @param [in] s Point mass position vector.
* @param [in] GM Gravitational coefficient of point mass.
* @return Acceleration (a=d^2r/dt^2)
*/
//------------------------------------------------------------------------------
Matrix& AccelPointMass(Matrix& r, Matrix& s, double GM);



#endif
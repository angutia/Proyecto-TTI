// $Header$
//------------------------------------------------------------------------------
// EccAnom
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file EccAnom.hpp
*   @brief This header contains the EccAnom operation. It computes the eccentric anomaly for elliptic orbits.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _ECCANOM_
#define _ECCANOM_

#include "..\include\matrix.hpp"
#include <cmath>

//------------------------------------------------------------------------------
// EccAnom(double M, double e)
//-------------------------------------------------------------------------------
/**
* @brief Computes the perturbational acceleration due to a point mass
*
* @param [in] M Mean anomaly in [rad].
* @param [in] e Eccentricity of the orbit [0,1].
* @return Eccentric anomaly in [rad].
*/
//------------------------------------------------------------------------------
double EccAnom (double M, double e);



#endif
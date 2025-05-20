// $Header$
//------------------------------------------------------------------------------
// Accel
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file Accel.hpp
*   @brief This header contains the Accel operation. It computes the acceleration of an Earth orbiting satellite due to the Earth's harmonic gravity field, the gravitational perturbations of the Sun and Moon, the solar radiation pressure, and the atmospheric drag.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _ACCEL_
#define _ACCEL_

#include "../include/matrix.hpp"

//------------------------------------------------------------------------------
// Accel(double x, Matrix& Y)
//-------------------------------------------------------------------------------
/**
* @brief Computes the acceleration of an Earth orbiting satellite due to the Earth's harmonic gravity field, the gravitational perturbations of the Sun and Moon, the solar radiation pressure, and the atmospheric drag.
*
* @param [in] x Terrestrial Time (Modified Julian Date)
* @param [in] Y Satellite state vector in the ICRF/EME2000 system
* @return Acceleration (a=d^2r/dt^2) in the ICRF/EME2000 system
*/
//------------------------------------------------------------------------------
Matrix& Accel(double x, Matrix& Y);



#endif
// $Header$
//------------------------------------------------------------------------------
// EqnEquinox
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file EqnEquinox.hpp
*   @brief This header contains the EqnEquinox operation. It computes the equation of the equinoxes. The equation of the equinoxes dpsi*cos(eps) is the right ascension of the mean equinox referred to the true equator and equinox and is equal to the difference between apparent and mean sidereal time.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _EQNEQUINOX_
#define _EQNEQUINOX_

//------------------------------------------------------------------------------
// EqnEquinox (double Mjd_TT)
//-------------------------------------------------------------------------------
/**
* @brief Computes the equation of the equinoxes.
*
* @param [in] Mjd_TT Modified Julian Date (Terrestrial Time).
* @return The equation of the equinoxes.
*/
//------------------------------------------------------------------------------
double EqnEquinox (double Mjd_TT);



#endif
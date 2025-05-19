// $Header$
//------------------------------------------------------------------------------
// gast
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file gast.hpp
*   @brief This header contains the gast operation. Greenwich Apparent Sidereal Time calculation.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _GAST_
#define _GAST_

//------------------------------------------------------------------------------
// gast (double Mjd_UT1)
//-------------------------------------------------------------------------------
/**
* @brief Greenwich Apparent Sidereal Time calculation.
*
* @param [in] Mjd_UT1 Modified Julian Date UT1
* @return GAST in [rad]
*/
//------------------------------------------------------------------------------
double gast (double Mjd_UT1);



#endif
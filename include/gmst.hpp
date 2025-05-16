// $Header$
//------------------------------------------------------------------------------
// gmst
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file gmst.hpp
*   @brief This header contains the gmst operation. Greenwich Mean Sidereal Time calculation.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _GMST_
#define _GMST_

//------------------------------------------------------------------------------
// gmst(double Mjd_UT1)
//-------------------------------------------------------------------------------
/**
* @brief Greenwich Mean Sidereal Time calculation
*
* @param [in] Mjd_UT1 Modified Julian Date UT1
* @return GMST in [rad]
*/
//------------------------------------------------------------------------------
double gmst(double Mjd_UT1);



#endif
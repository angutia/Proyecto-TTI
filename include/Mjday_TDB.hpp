// $Header$
//------------------------------------------------------------------------------
// Mjday_TDB
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file Mjday_TDB.hpp
*   @brief This header contains the Mjday_TDB operation. Computes the Modified Julian Date for barycentric dynamical time.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _MJDAY_TDB_
#define _MJDAY_TDB_

#include <cmath>

//------------------------------------------------------------------------------
// Mjday_TDB(double Mjd_TT)
//-------------------------------------------------------------------------------
/**
* @brief Computes the Modified Julian Date for barycentric dynamical time.
*
* @param [in] Mjd_TT Modified Julian Date (TT).
* @return Modified Julian Date (TDB).
*/
//------------------------------------------------------------------------------
double Mjday_TDB(double Mjd_TT);



#endif
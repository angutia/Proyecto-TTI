// $Header$
//------------------------------------------------------------------------------
// Mjday
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file Mjday.hpp
*   @brief This header contains the Mjday operation. It computes the Modified Julian Date (MJD).
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _MJDAY_
#define _MJDAY_

#include <cmath>

//------------------------------------------------------------------------------
// Mjday(double yr, double mon, double day, double hr = 0, double min = 0, double sec = 0)
//-------------------------------------------------------------------------------
/**
* @brief Computes the Modified Julian Date (MJD).
*
* @param [in] yr Year.
* @param [in] mon Month.
* @param [in] day Day.
* @param [in] hr Universal time hour.
* @param [in] min Universal time min.
* @param [in] sec Universal time sec.
* @return Modified Julian Date (MJD).
*/
//------------------------------------------------------------------------------
double Mjday(double yr, double mon, double day, double hr = 0, double min = 0, double sec = 0);



#endif
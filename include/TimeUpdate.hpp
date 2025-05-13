// $Header$
//------------------------------------------------------------------------------
// TimeUpdate
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file TimeUpdate.hpp
*   @brief This header contains the TimeUpdate operation. Computes the time update.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _TIMEUPDATE_
#define _TIMEUPDATE_

#include "../include/matrix.hpp"

//------------------------------------------------------------------------------
// TimeUpdate(Matrix& P, Matrix& Phi, double Qdt = 0.0)
//-------------------------------------------------------------------------------
/**
* @brief Computes the time update.
*
* @param [in] P 
* @param [in] Phi 
* @param [in] Qdt 
* @return The updated matrix P.
*/
//------------------------------------------------------------------------------
Matrix& TimeUpdate(Matrix& P, Matrix& Phi, double Qdt = 0.0);



#endif
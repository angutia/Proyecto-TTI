// $Header$
//------------------------------------------------------------------------------
// VarEqn
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file VarEqn.hpp
*   @brief This header contains the VarEqn operation. It computes the variational equations, i.e. the derivative of the state vector and the state transition matrix.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#ifndef _VAREQN_
#define _VAREQN_

#include "../include/matrix.hpp"

//------------------------------------------------------------------------------
// VarEqn(double x, Matrix& yPhi)
//-------------------------------------------------------------------------------
/**
* @brief Computes the variational equations, i.e. the derivative of the state vector and the state transition matrix.
*
* @param [in] x Time since epoch in [s]
* @param [in] yPhi (6+36)-dim vector comprising the state vector (y) and the state transition matrix (Phi) in column wise storage order
* @return Derivative of yPhi
*/
//------------------------------------------------------------------------------
Matrix& VarEqn(double x, Matrix& yPhi);



#endif
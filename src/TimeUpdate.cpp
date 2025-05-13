// $Source$
//------------------------------------------------------------------------------
// TimeUpdate
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file TimeUpdate.cpp
*   @brief Source of the TimeUpdate operation. It computes the time update.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#include "../include/matrix.hpp"

Matrix& TimeUpdate(Matrix& P, Matrix& Phi, double Qdt = 0.0){
    Matrix& Paux = Phi*P*transpose(Phi) + Qdt;

    return Paux;
}
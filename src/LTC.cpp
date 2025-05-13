// $Source$
//------------------------------------------------------------------------------
// LTC
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file LTC.cpp
*   @brief Source of the LTC operation. It computes the transformation from Greenwich meridian system to local tangent coordinates.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#include "../include/matrix.hpp"
#include "../include/R_y.hpp"
#include "../include/R_z.hpp"

Matrix& LTC(double lon, double lat){
    Matrix& M = R_y(-1.0*lat)*R_z(lon);

    double Aux;
    for (int j = 1; j <= 3; j++){
        Aux=M(1,j); M(1,j)=M(2,j); M(2,j)=M(3,j); M(3,j)= Aux;
    }

    return M;
}

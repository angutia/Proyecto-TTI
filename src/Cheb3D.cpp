// $Source$
//------------------------------------------------------------------------------
// Cheb3D
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file Cheb3D.cpp
*   @brief Source of the Cheb3D operation. Chebyshev approximation of 3-dimensional vectors.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#include "..\include\matrix.hpp"
#include <cmath>

Matrix& Cheb3D(double t, int N, double Ta, double Tb, Matrix& Cx, Matrix& Cy, Matrix& Cz){
    // Check validity
    if ( (t<Ta) || (Tb<t) ){
        cout << "ERROR: Time out of range in Cheb3D::Value\n";
        exit(EXIT_FAILURE);
    }

    // Clenshaw algorithm
    double tau = ((2*t)-Ta-Tb)/(Tb-Ta);

    Matrix& f1 = zeros(3);
    Matrix& f2 = zeros(3);

    Matrix old_f1(3);
    for (int i=N; i>=2; i--) {
        old_f1 = f1;
        Matrix C(3);
        C(1) = Cx(i); C(2) = Cy(i); C(3) = Cz(i);
        f1 = (f1*2*tau)-f2+C;
        f2 = old_f1;
    }
    Matrix C(3);
    C(1) = Cx(1); C(2) = Cy(1); C(3) = Cz(1);
    Matrix& ChebApp = (f1*tau)-f2+C;

    return ChebApp;
}
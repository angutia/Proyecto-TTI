// $Source$
//------------------------------------------------------------------------------
// G_AccelHarmonic
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file G_AccelHarmonic.cpp
*   @brief Source of the G_AccelHarmonic operation. Computes the gradient of the Earth's harmonic gravity field.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#include "../include/matrix.hpp"
#include "../include/AccelHarmonic.hpp"

Matrix& G_AccelHarmonic(Matrix& r, Matrix& U, int n_max, int m_max){
    double d = 1.0;   // Position increment [m]

    Matrix& G = zeros(3,3);
    Matrix& dr = zeros(3,1);

    // Gradient
    for (int i = 1; i <= 3; i++) {
        // Set offset in i-th component of the position vector
        dr = zeros(3,1);
        dr(i) = d;
        // Acceleration difference
        Matrix da = AccelHarmonic ( r+dr/2,U, n_max, m_max ) - AccelHarmonic ( r-dr/2,U, n_max, m_max );
        cout << "da "<<i<<": " << da << endl;
        // Derivative with respect to i-th axis
        G.assign_column(i, transpose(da/d));
    }

    return G;
}


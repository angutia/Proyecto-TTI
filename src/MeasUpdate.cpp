// $Source$
//------------------------------------------------------------------------------
// MeasUpdate
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file MeasUpdate.cpp
*   @brief Source of the MeasUpdate operation. Kalman filter measurement update.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#include "../include/matrix.hpp"
#include <tuple>

using namespace std;

tuple<Matrix&, Matrix&, Matrix&> MeasUpdate(Matrix& x, Matrix& z, Matrix& g, Matrix& s, Matrix& G, Matrix& P, int n){
    int m = z.n_column;
    Matrix Inv_W = zeros(m,m);

    for (int i = 1; i <= m; i++){
        Inv_W(i,i) = s(i)*s(i);    // Inverse weight (measurement covariance)
    }

    // Kalman gain
    Matrix& K = P*transpose(G)*inv(Inv_W+G*P*transpose(G));

    // State update
    x = x + K*(z-g);

    // Covariance update
    P = (eye(n)-K*G)*P;

    return tie(K, x, P);
}
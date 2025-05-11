// $Source$
//------------------------------------------------------------------------------
// AzElPa
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file AzElPa.cpp
*   @brief Source of the AzElPa operation. Computes azimuth, elevation and partials from local tangent coordinates.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#define _USE_MATH_DEFINES
#include <cmath>
#include <tuple>
#include "../include/Matrix.hpp"

using namespace std;

tuple<double, double, Matrix&, Matrix&> AzElPa(Matrix& s){ 
    double pi2 = 2.0*M_PI;

    double rho = sqrt(s(1)*s(1)+s(2)*s(2));

    // Angles
    double Az = atan2(s(1),s(2));

    if (Az<0.0){ 
        Az = Az+pi2;
    }

    double El = atan ( s(3) / rho );

    // Partials
    Matrix& dAds = zeros(3);
    dAds(1) = s(2)/(rho*rho);
    dAds(2) = -s(1)/(rho*rho);
    dAds(3) = 0.0;
    Matrix& dEds = zeros(3);
    dEds(1) = -s(1)*s(3)/rho;
    dEds(2) = -s(2)*s(3)/rho;
    dEds(3) = rho;
    dEds = dEds / dot(s,s);

    return tie(Az, El, dAds, dEds);   
}
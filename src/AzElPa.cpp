//--------------------------------------------------------------------------
//
// Purpose:
//  Computes azimuth, elevation and partials from local tangent coordinates
//
// Input:
//   s      Topocentric local tangent coordinates (East-North-Zenith frame)
// 
// Outputs:
//   A      Azimuth [rad]
//   E      Elevation [rad]
//   dAds   Partials of azimuth w.r.t. s
//   dEds   Partials of elevation w.r.t. s
//
// Last modified:   2015/08/12   M. Mahooti
//
//--------------------------------------------------------------------------

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
    Matrix dAds(3);
    dAds(1) = s(2)/(rho*rho);
    dAds(2) = -s(1)/(rho*rho);
    dAds(3) = 0.0;
    Matrix dEds(3);
    dEds(1) = -s(1)*s(3)/rho;
    dEds(2) = -s(2)*s(3)/rho;
    dEds(3) = rho;
    dEds = dEds / dot(s,s);

    return tie(Az, El, dAds, dEds);   
}
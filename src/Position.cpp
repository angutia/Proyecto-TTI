// $Source$
//------------------------------------------------------------------------------
// Position
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file Position.cpp
*   @brief Source of the Position operation. Computes the position vector (r [m]) from geodetic coordinates (Longitude [rad], latitude [rad], altitude [m]).
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#include "..\include\matrix.hpp"
#include "..\include\SAT_Const.hpp"
#include <cmath>


Matrix& Position(double lon, double lat, double h){
    double R_equ = SAT_Const::R_Earth;
    double f     = SAT_Const::f_Earth;
    
    double e2     = f*(2.0-f);   // Square of eccentricity
    double CosLat = cos(lat);    // (Co)sine of geodetic latitude
    double SinLat = sin(lat);
    
    // Position vector 
    double N = R_equ / sqrt(1.0-e2*SinLat*SinLat);
    
    Matrix& r = zeros(3); // Position vector [m]
    r(1) =  (         N+h)*CosLat*cos(lon);
    r(2) =  (         N+h)*CosLat*sin(lon);
    r(3) =  ((1.0-e2)*N+h)*SinLat;

    return r;
}



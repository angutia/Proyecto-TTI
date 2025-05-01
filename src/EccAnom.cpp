// $Source$
//------------------------------------------------------------------------------
// EccAnom
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file EccAnom.cpp
*   @brief Source of the EccAnom operation. It computes the eccentric anomaly for elliptic orbits.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#define _USE_MATH_DEFINES
#include "..\include\matrix.hpp"
#include "..\include\global.hpp"
#include "..\include\EccAnom.hpp"
#include <cmath>

double EccAnom (double M, double e) {
    int maxit = 15;
    int i = 1;

    // Starting value
    M = fmod(M, 2.0*M_PI);

    double E;
    if (e<0.8) {
        E = M;
    } 
    else {
        E = M_PI;
    }

    double f = E - e*sin(E) - M;
    E = E - f / ( 1.0 - e*cos(E) );

    // Iteration
    while (abs(f) > 1e2*eps){
        f = E - e*sin(E) - M;
        E = E - f / ( 1.0 - e*cos(E) );
        i = i+1;
        if (i==maxit){
            cout << "ERROR: convergence problems in EccAnom\n";
            exit(EXIT_FAILURE);
        }  
    }

    return E;
}

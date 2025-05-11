// $Source$
//------------------------------------------------------------------------------
// IERS
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file IERS.cpp
*   @brief Source of the IERS operation. Management of IERS time and polar motion data.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#include "../include/matrix.hpp"
#include "../include/SAT_Const.hpp"
#include <cmath>
#include <tuple>

tuple<double, double, double, double, double, double, double, double, double> IERS(Matrix& eop, double Mjd_UTC, char interp = 'n'){
    double x_pole, y_pole, UT1_UTC, LOD, dpsi, deps, dx_pole, dy_pole, TAI_UTC;
    if (interp =='l'){
        // linear interpolation
        double mjd = (floor(Mjd_UTC));
        double i = 1;
        Matrix eop4r = eop.extract_row(4);
        while (i<=eop4r.n_column && mjd!=eop4r(i)){
            i++;
        }
        Matrix preeop = eop.extract_column(i);
        Matrix nexteop = eop.extract_column(i+1);
        double mfme = 1440*(Mjd_UTC-floor(Mjd_UTC));
        double fixf = mfme/1440;
        // Setting of IERS Earth rotation parameters
        // (UT1-UTC [s], TAI-UTC [s], x ["], y ["])
        x_pole  = preeop(5)+(nexteop(5)-preeop(5))*fixf;
        y_pole  = preeop(6)+(nexteop(6)-preeop(6))*fixf;
        UT1_UTC = preeop(7)+(nexteop(7)-preeop(7))*fixf;
        LOD     = preeop(8)+(nexteop(8)-preeop(8))*fixf;
        dpsi    = preeop(9)+(nexteop(9)-preeop(9))*fixf;
        deps    = preeop(10)+(nexteop(10)-preeop(10))*fixf;
        dx_pole = preeop(11)+(nexteop(11)-preeop(11))*fixf;
        dy_pole = preeop(12)+(nexteop(12)-preeop(12))*fixf;
        TAI_UTC = preeop(13);
        
        x_pole  = x_pole/SAT_Const::Arcs;  // Pole coordinate [rad]
        y_pole  = y_pole/SAT_Const::Arcs;  // Pole coordinate [rad]
        dpsi    = dpsi/SAT_Const::Arcs;
        deps    = deps/SAT_Const::Arcs;
        dx_pole = dx_pole/SAT_Const::Arcs; // Pole coordinate [rad]
        dy_pole = dy_pole/SAT_Const::Arcs; // Pole coordinate [rad]
    } else if (interp =='n'){    
        double mjd = (floor(Mjd_UTC));
        double i = 1;
        Matrix eop4r = eop.extract_row(4);
        while (i<=eop4r.n_column && mjd!=eop4r(i)){
            i++;
        }
        Matrix eopi = eop.extract_column(i);
        // Setting of IERS Earth rotation parameters
        // (UT1-UTC [s], TAI-UTC [s], x ["], y ["])
        x_pole  = eopi(5)/SAT_Const::Arcs;  // Pole coordinate [rad]
        y_pole  = eopi(6)/SAT_Const::Arcs;  // Pole coordinate [rad]
        UT1_UTC = eopi(7);             // UT1-UTC time difference [s]
        LOD     = eopi(8);             // Length of day [s]
        dpsi    = eopi(9)/SAT_Const::Arcs;
        deps    = eopi(10)/SAT_Const::Arcs;
        dx_pole = eopi(11)/SAT_Const::Arcs; // Pole coordinate [rad]
        dy_pole = eopi(12)/SAT_Const::Arcs; // Pole coordinate [rad]
        TAI_UTC = eopi(13);            // TAI-UTC time difference [s]
    }
    return tie(x_pole, y_pole, UT1_UTC, LOD, dpsi, deps, dx_pole, dy_pole, TAI_UTC);
}
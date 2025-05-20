// $Source$
//------------------------------------------------------------------------------
// Accel
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file Accel.cpp
*   @brief Source of the Accel operation. It computes the acceleration of an Earth orbiting satellite due to the Earth's harmonic gravity field, the gravitational perturbations of the Sun and Moon, the solar radiation pressure, and the atmospheric drag.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#include "../include/matrix.hpp"
#include "../include/global.hpp"
#include "../include/SAT_Const.hpp"
#include "../include/IERS.hpp"
#include "../include/timediff.hpp"
#include "../include/PrecMatrix.hpp"
#include "../include/NutMatrix.hpp"
#include "../include/PoleMatrix.hpp"
#include "../include/GHAMatrix.hpp"
#include "../include/Mjday_TDB.hpp"
#include "../include/JPL_Eph_DE430.hpp"
#include "../include/AccelHarmonic.hpp"
#include "../include/AccelPointMass.hpp"

#include "../include/gast.hpp"
#include "../include/gmst.hpp"
#include "../include/EqnEquinox.hpp"

Matrix& Accel(double x, Matrix& Y){

    auto [x_pole,y_pole,UT1_UTC,LOD,dpsi,deps,dx_pole,dy_pole,TAI_UTC] = IERS(eopdata,AuxParam.Mjd_UTC + x/86400,'l');
    auto [UT1_TAI,UTC_GPS,UT1_GPS,TT_UTC,GPS_UTC] = timediff(UT1_UTC,TAI_UTC);
    double Mjd_UT1 = AuxParam.Mjd_UTC + x/86400 + UT1_UTC/86400;
    double Mjd_TT = AuxParam.Mjd_UTC + x/86400 + TT_UTC/86400;

    Matrix P = PrecMatrix(SAT_Const::MJD_J2000,Mjd_TT);
    Matrix N = NutMatrix(Mjd_TT);
    Matrix T = N * P;
    Matrix E = PoleMatrix(x_pole,y_pole) * GHAMatrix(Mjd_UT1) * T;

    double MJD_TDB = Mjday_TDB(Mjd_TT);
    auto [r_Mercury,r_Venus,r_Earth,r_Mars,r_Jupiter,r_Saturn,r_Uranus,r_Neptune,r_Pluto,r_Moon,r_Sun] = JPL_Eph_DE430(MJD_TDB);

    // Acceleration due to harmonic gravity field 
    Matrix a = AccelHarmonic(Y.extract_vector(1,3), E, AuxParam.n, AuxParam.m);

    // Luni-solar perturbations
    if (AuxParam.sun){
        a = a + AccelPointMass(Y.extract_vector(1,3),r_Sun,SAT_Const::GM_Sun);
    }

    if (AuxParam.moon){
        a = a + AccelPointMass(Y.extract_vector(1,3),r_Moon,SAT_Const::GM_Moon);
    }

    // Planetary perturbations
    if (AuxParam.planets){
        a = a + AccelPointMass(Y.extract_vector(1,3),r_Mercury,SAT_Const::GM_Mercury);
        a = a + AccelPointMass(Y.extract_vector(1,3),r_Venus,SAT_Const::GM_Venus);
        a = a + AccelPointMass(Y.extract_vector(1,3),r_Mars,SAT_Const::GM_Mars);
        a = a + AccelPointMass(Y.extract_vector(1,3),r_Jupiter,SAT_Const::GM_Jupiter);
        a = a + AccelPointMass(Y.extract_vector(1,3),r_Saturn,SAT_Const::GM_Saturn);
        a = a + AccelPointMass(Y.extract_vector(1,3),r_Uranus,SAT_Const::GM_Uranus);
        a = a + AccelPointMass(Y.extract_vector(1,3),r_Neptune,SAT_Const::GM_Neptune);
        a = a + AccelPointMass(Y.extract_vector(1,3),r_Pluto,SAT_Const::GM_Pluto);
    }

    Matrix& dY = zeros(a.n_row+Y.extract_vector(4,6).n_row,1);
    for (int i = 1; i <= Y.extract_vector(4,6).n_row; i++) {
        dY.assign_row(i,Y.extract_vector(4,6).extract_row(i));
    }
    for (int i = 1; i <= a.n_row; i++) {
        dY.assign_row(i+Y.extract_vector(4,6).n_row,a.extract_row(i));
    }

    return dY;
}

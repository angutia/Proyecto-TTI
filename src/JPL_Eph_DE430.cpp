// $Source$
//------------------------------------------------------------------------------
// JPL_Eph_DE430
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file JPL_Eph_DE430.cpp
*   @brief Source of the JPL_Eph_DE430 operation. It computes the sun, moon, and nine major planets' equatorial position using JPL Ephemerides.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------

#include "../include/matrix.hpp"
#include "../include/global.hpp"
#include "../include/Cheb3D.hpp"
#include <tuple>

using namespace std;

tuple<Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&> JPL_Eph_DE430(double Mjd_TDB){
    double JD = Mjd_TDB + 2400000.5;
    Matrix col1 = PC.extract_column(1);
    for(int i = 1; i <= col1.n_column; i++){
        if(col1(i) <= JD){
            col1(i) = 1;
        } else {
            col1(i) = 0;
        }
    }
    Matrix col2 = PC.extract_column(2);
    for(int i = 1; i <= col2.n_column; i++){
        if(JD <= col2(i)){
            col2(i) = 1;
        } else {
            col2(i) = 0;
        }
    }
    int i = 1;
    while (i <= col1.n_column && col1(i) + col2(i) != 2){
        i++;
    }
    Matrix PCtemp = PC.extract_row(i);

    double t1 = PCtemp(1)-2400000.5; // MJD at start of interval

    double dt = Mjd_TDB - t1;

    Matrix temp(4);
    for (int j = 0; j <= 3; j++){
        temp(j+1) = 231 + 13*j;
    }
    Matrix Cx_Earth = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix Cy_Earth = PCtemp.extract_vector(temp(2),temp(3)-1);
    Matrix Cz_Earth = PCtemp.extract_vector(temp(3),temp(4)-1);
    temp = temp+39;
    Matrix Cx = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix Cy = PCtemp.extract_vector(temp(2),temp(3)-1);
    Matrix Cz = PCtemp.extract_vector(temp(3),temp(4)-1);
    Cx_Earth = union_vector(Cx_Earth,Cx);
    Cy_Earth = union_vector(Cy_Earth,Cy);
    Cz_Earth = union_vector(Cz_Earth,Cz);
    int j;
    double Mjd0;
    if (0<=dt && dt<=16){
        j=0;
        Mjd0 = t1;
    } else if(16<dt && dt<=32){
        j=1;
        Mjd0 = t1+16*j;
    }
    Matrix& r_Earth = transpose(Cheb3D(Mjd_TDB, 13, Mjd0, Mjd0+16, Cx_Earth.extract_vector(13*j+1,13*j+13), Cy_Earth.extract_vector(13*j+1,13*j+13), Cz_Earth.extract_vector(13*j+1,13*j+13)))*1e3;
    

    for (int j = 0; j <= 3; j++){
        temp(j+1) = 441 + 13*j;
    }
    Matrix Cx_Moon = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix Cy_Moon = PCtemp.extract_vector(temp(2),temp(3)-1);
    Matrix Cz_Moon = PCtemp.extract_vector(temp(3),temp(4)-1);
    for (int i=1; i<=7; i++){
        temp = temp+39;
        Cx = PCtemp.extract_vector(temp(1),temp(2)-1);
        Cy = PCtemp.extract_vector(temp(2),temp(3)-1);
        Cz = PCtemp.extract_vector(temp(3),temp(4)-1);
        Cx_Moon = union_vector(Cx_Moon,Cx);
        Cy_Moon = union_vector(Cy_Moon,Cy);
        Cz_Moon = union_vector(Cz_Moon,Cz);
    }
    if (0<=dt && dt<=4){
        j=0;
        Mjd0 = t1;
    } else if(4<dt && dt<=8){
        j=1;
        Mjd0 = t1+4*j;
    } else if(8<dt && dt<=12){
        j=2;
        Mjd0 = t1+4*j;
    } else if(12<dt && dt<=16){
        j=3;
        Mjd0 = t1+4*j;
    } else if(16<dt && dt<=20){
        j=4;
        Mjd0 = t1+4*j;
    } else if(20<dt && dt<=24){
        j=5;
        Mjd0 = t1+4*j;
    } else if(24<dt && dt<=28){
        j=6;
        Mjd0 = t1+4*j;
    } else if(28<dt && dt<=32){
        j=7;
        Mjd0 = t1+4*j;
    }
    Matrix& r_Moon = transpose(Cheb3D(Mjd_TDB, 13, Mjd0, Mjd0+4, Cx_Moon.extract_vector(13*j+1,13*j+13), Cy_Moon.extract_vector(13*j+1,13*j+13), Cz_Moon.extract_vector(13*j+1,13*j+13)))*1e3;
    

    for (int j = 0; j <= 3; j++){
        temp(j+1) = 753 + 11*j;
    }
    Matrix Cx_Sun = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix Cy_Sun = PCtemp.extract_vector(temp(2),temp(3)-1);
    Matrix Cz_Sun = PCtemp.extract_vector(temp(3),temp(4)-1);
    temp = temp+33;
    Cx = PCtemp.extract_vector(temp(1),temp(2)-1);
    Cy = PCtemp.extract_vector(temp(2),temp(3)-1);
    Cz = PCtemp.extract_vector(temp(3),temp(4)-1);
    Cx_Sun = union_vector(Cx_Sun,Cx);
    Cy_Sun = union_vector(Cy_Sun,Cy);
    Cz_Sun = union_vector(Cz_Sun,Cz);
    if (0<=dt && dt<=16){
        j=0;
        Mjd0 = t1;
    } else if(16<dt && dt<=32){
        j=1;
        Mjd0 = t1+16*j;
    }
    Matrix& r_Sun = transpose(Cheb3D(Mjd_TDB, 11, Mjd0, Mjd0+16, Cx_Sun.extract_vector(11*j+1,11*j+11), Cy_Sun.extract_vector(11*j+1,11*j+11), Cz_Sun.extract_vector(11*j+1,11*j+11)))*1e3;
    

    for (int j = 0; j <= 3; j++){
        temp(j+1) = 3 + 14*j;
    }
    Matrix Cx_Mercury = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix Cy_Mercury = PCtemp.extract_vector(temp(2),temp(3)-1);
    Matrix Cz_Mercury = PCtemp.extract_vector(temp(3),temp(4)-1);
    for (int i=1; i<=3; i++){
        temp = temp+42;
        Cx = PCtemp.extract_vector(temp(1),temp(2)-1);
        Cy = PCtemp.extract_vector(temp(2),temp(3)-1);
        Cz = PCtemp.extract_vector(temp(3),temp(4)-1);
        Cx_Mercury = union_vector(Cx_Mercury,Cx);
        Cy_Mercury = union_vector(Cy_Mercury,Cy);
        Cz_Mercury = union_vector(Cz_Mercury,Cz);
    }
    if (0<=dt && dt<=8){
        j=0;
        Mjd0 = t1;
    } else if(8<dt && dt<=16){
        j=1;
        Mjd0 = t1+8*j;
    } else if (16<dt && dt<=24){
        j=2;
        Mjd0 = t1+8*j;
    } else if(24<dt && dt<=32){
        j=3;
        Mjd0 = t1+8*j;
    }
    Matrix& r_Mercury = transpose(Cheb3D(Mjd_TDB, 14, Mjd0, Mjd0+8, Cx_Mercury.extract_vector(14*j+1,14*j+14), Cy_Mercury.extract_vector(14*j+1,14*j+14), Cz_Mercury.extract_vector(14*j+1,14*j+14)))*1e3;
    

    for (int j = 0; j <= 3; j++){
        temp(j+1) = 171 + 10*j;
    }
    Matrix Cx_Venus = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix Cy_Venus = PCtemp.extract_vector(temp(2),temp(3)-1);
    Matrix Cz_Venus = PCtemp.extract_vector(temp(3),temp(4)-1);
    temp = temp+30;
    Cx = PCtemp.extract_vector(temp(1),temp(2)-1);
    Cy = PCtemp.extract_vector(temp(2),temp(3)-1);
    Cz = PCtemp.extract_vector(temp(3),temp(4)-1);
    Cx_Venus = union_vector(Cx_Venus,Cx);
    Cy_Venus = union_vector(Cy_Venus,Cy);
    Cz_Venus = union_vector(Cz_Venus,Cz);
    if (0<=dt && dt<=16){
        j=0;
        Mjd0 = t1;
    } else if(16<dt && dt<=32){
        j=1;
        Mjd0 = t1+16*j;
    }
    Matrix& r_Venus = transpose(Cheb3D(Mjd_TDB, 10, Mjd0, Mjd0+16, Cx_Venus.extract_vector(10*j+1,10*j+10), Cy_Venus.extract_vector(10*j+1,10*j+10), Cz_Venus.extract_vector(10*j+1,10*j+10)))*1e3;
    

    for (int j = 0; j <= 3; j++){
        temp(j+1) = 309 + 11*j;
    }
    Matrix Cx_Mars = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix Cy_Mars = PCtemp.extract_vector(temp(2),temp(3)-1);
    Matrix Cz_Mars = PCtemp.extract_vector(temp(3),temp(4)-1);
    j=0;
    Mjd0 = t1;
    Matrix& r_Mars = transpose(Cheb3D(Mjd_TDB, 11, Mjd0, Mjd0+32, Cx_Mars.extract_vector(11*j+1,11*j+11), Cy_Mars.extract_vector(11*j+1,11*j+11), Cz_Mars.extract_vector(11*j+1,11*j+11)))*1e3;
    

    for (int j = 0; j <= 3; j++){
        temp(j+1) = 342 + 8*j;
    }
    Matrix Cx_Jupiter = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix Cy_Jupiter = PCtemp.extract_vector(temp(2),temp(3)-1);
    Matrix Cz_Jupiter = PCtemp.extract_vector(temp(3),temp(4)-1);
    j=0;
    Mjd0 = t1;
    Matrix& r_Jupiter = transpose(Cheb3D(Mjd_TDB, 8, Mjd0, Mjd0+32, Cx_Jupiter.extract_vector(8*j+1,8*j+8), Cy_Jupiter.extract_vector(8*j+1,8*j+8), Cz_Jupiter.extract_vector(8*j+1,8*j+8)))*1e3;
    
    
    for (int j = 0; j <= 3; j++){
        temp(j+1) = 366 + 7*j;
    }
    Matrix Cx_Saturn = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix Cy_Saturn = PCtemp.extract_vector(temp(2),temp(3)-1);
    Matrix Cz_Saturn = PCtemp.extract_vector(temp(3),temp(4)-1);
    j=0;
    Mjd0 = t1;
    Matrix& r_Saturn = transpose(Cheb3D(Mjd_TDB, 7, Mjd0, Mjd0+32, Cx_Saturn.extract_vector(7*j+1,7*j+7), Cy_Saturn.extract_vector(7*j+1,7*j+7), Cz_Saturn.extract_vector(7*j+1,7*j+7)))*1e3;
    

    for (int j = 0; j <= 3; j++){
        temp(j+1) = 387 + 6*j;
    }
    Matrix Cx_Uranus = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix Cy_Uranus = PCtemp.extract_vector(temp(2),temp(3)-1);
    Matrix Cz_Uranus = PCtemp.extract_vector(temp(3),temp(4)-1);
    j=0;
    Mjd0 = t1;
    Matrix& r_Uranus = transpose(Cheb3D(Mjd_TDB, 6, Mjd0, Mjd0+32, Cx_Uranus.extract_vector(6*j+1,6*j+6), Cy_Uranus.extract_vector(6*j+1,6*j+6), Cz_Uranus.extract_vector(6*j+1,6*j+6)))*1e3;
    

    for (int j = 0; j <= 3; j++){
        temp(j+1) = 405 + 6*j;
    }
    Matrix Cx_Neptune = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix Cy_Neptune = PCtemp.extract_vector(temp(2),temp(3)-1);
    Matrix Cz_Neptune = PCtemp.extract_vector(temp(3),temp(4)-1);
    j=0;
    Mjd0 = t1;
    Matrix& r_Neptune = transpose(Cheb3D(Mjd_TDB, 6, Mjd0, Mjd0+32, Cx_Neptune.extract_vector(6*j+1,6*j+6), Cy_Neptune.extract_vector(6*j+1,6*j+6), Cz_Neptune.extract_vector(6*j+1,6*j+6)))*1e3;
    

    for (int j = 0; j <= 3; j++){
        temp(j+1) = 423 + 6*j;
    }
    Matrix Cx_Pluto = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix Cy_Pluto = PCtemp.extract_vector(temp(2),temp(3)-1);
    Matrix Cz_Pluto = PCtemp.extract_vector(temp(3),temp(4)-1);
    j=0;
    Mjd0 = t1;
    Matrix& r_Pluto = transpose(Cheb3D(Mjd_TDB, 6, Mjd0, Mjd0+32, Cx_Pluto.extract_vector(6*j+1,6*j+6), Cy_Pluto.extract_vector(6*j+1,6*j+6), Cz_Pluto.extract_vector(6*j+1,6*j+6)))*1e3;
    

    for (int j = 0; j <= 2; j++){
        temp(j+1) = 819 + 10*j;
    }
    /*
    Matrix Cx_Nutations = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix Cy_Nutations = PCtemp.extract_vector(temp(2),temp(3)-1);
    for (int i=1; i<=3; i++){
        temp = temp+20;
        Cx = PCtemp.extract_vector(temp(1),temp(2)-1);
        Cy = PCtemp.extract_vector(temp(2),temp(3)-1);
        Cx_Nutations = union_vector(Cx_Nutations,Cx);
        Cy_Nutations = union_vector(Cy_Nutations,Cy);
    }
    if (0<=dt && dt<=8) {
        j=0;
        Mjd0 = t1;
    } else if(8<dt && dt<=16) {
        j=1;
        Mjd0 = t1+8*j;
    } else if (16<dt && dt<=24) {
        j=2;
        Mjd0 = t1+8*j;
    } else if(24<dt && dt<=32) {
        j=3;
        Mjd0 = t1+8*j;
    }
    Matrix Nutations = transpose(Cheb3D(Mjd_TDB, 10, Mjd0, Mjd0+8, Cx_Nutations.extract_vector(10*j+1,10*j+10), Cy_Nutations.extract_vector(10*j+1,10*j+10),zeros(10,1)));


    for (int j = 0; j <= 2; j++){
        temp(j+1) = 899 + 10*j;
    }
    Matrix Cx_Librations = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix Cy_Librations = PCtemp.extract_vector(temp(2),temp(3)-1);
    Matrix Cz_Librations = PCtemp.extract_vector(temp(3),temp(4)-1);
    for (int i=1; i<=3; i++){
        temp = temp+30;
        Cx = PCtemp.extract_vector(temp(1),temp(2)-1);
        Cy = PCtemp.extract_vector(temp(2),temp(3)-1);
        Cz = PCtemp.extract_vector(temp(3),temp(4)-1);
        Cx_Librations = union_vector(Cx_Librations,Cx);
        Cy_Librations = union_vector(Cy_Librations,Cy);
        Cz_Librations = union_vector(Cz_Librations,Cz);
    }
    if (0<=dt && dt<=8) {
        j=0;
        Mjd0 = t1;
    } else if(8<dt && dt<=16) {
        j=1;
        Mjd0 = t1+8*j;
    } else if (16<dt && dt<=24) {
        j=2;
        Mjd0 = t1+8*j;
    } else if(24<dt && dt<=32) {
        j=3;
        Mjd0 = t1+8*j;
    }
    Matrix Librations = transpose(Cheb3D(Mjd_TDB, 10, Mjd0, Mjd0+8, Cx_Librations.extract_vector(10*j+1,10*j+10), Cy_Librations.extract_vector(10*j+1,10*j+10), Cz_Librations.extract_vector(10*j+1,10*j+10)));
    */
    double EMRAT = 81.30056907419062; // DE430
    double EMRAT1 = 1/(1+EMRAT);
    r_Earth = r_Earth-r_Moon*EMRAT1;
    r_Mercury = (r_Earth*-1)+r_Mercury;
    r_Venus = (r_Earth*-1)+r_Venus;
    r_Mars = (r_Earth*-1)+r_Mars;
    r_Jupiter = (r_Earth*-1)+r_Jupiter;
    r_Saturn = (r_Earth*-1)+r_Saturn;
    r_Uranus = (r_Earth*-1)+r_Uranus;
    r_Neptune = (r_Earth*-1)+r_Neptune;
    r_Pluto = (r_Earth*-1)+r_Pluto;
    r_Sun = (r_Earth*-1)+r_Sun;

    return tie(r_Mercury, r_Venus, r_Earth, r_Mars, r_Jupiter, r_Saturn, r_Uranus, r_Neptune, r_Pluto, r_Moon, r_Sun);

}
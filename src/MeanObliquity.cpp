// $Source$
//------------------------------------------------------------------------------
// MeanObliquity
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file MeanObliquity.cpp
*   @brief Source of the MeanObliquity operation. It computes the mean obliquity of the ecliptic.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------


#include "..\include\global.hpp"

double MeanObliquity (double Mjd_TT){
    double T = (Mjd_TT-MJD_J2000)/36525;

    double MOblq = Rad *( 84381.448/3600-(46.8150+(0.00059-0.001813*T)*T)*T/3600 );

    return MOblq;
}

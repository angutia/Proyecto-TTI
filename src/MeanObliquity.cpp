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


#include "..\include\SAT_Const.hpp"

double MeanObliquity (double Mjd_TT){
    double T = (Mjd_TT-SAT_Const::MJD_J2000)/36525;

    double MOblq = SAT_Const::Rad *( 84381.448/3600-(46.8150+(0.00059-0.001813*T)*T)*T/3600 );

    return MOblq;
}

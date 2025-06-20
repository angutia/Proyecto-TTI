#ifndef _GLOBAL_
#define _GLOBAL_

#include "..\include\matrix.hpp"
#include <cmath>

typedef struct {
    double Mjd_UTC, Mjd_TT;
    int n, m, sun, moon, planets;
} Param;

extern Param AuxParam;
extern Matrix eopdata;
extern Matrix Cnm;
extern Matrix Snm;
extern Matrix PC;
extern Matrix obs;
extern double eps;

void eop19620101(int c);

void GGM03S();

void DE430Coeff();

void GEOS3(int f);


#endif
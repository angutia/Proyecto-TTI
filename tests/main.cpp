#include "..\include\matrix.hpp"
#include "..\include\R_x.hpp"
#include "..\include\global.hpp"
#include <iostream>

using namespace std;

int main() {
	eop19620101(4); // c = 21413
    GGM03S();
    DE430Coeff();

	AuxParam.Mjd_UTC = 49746.1112847221;
    AuxParam.Mjd_TT = 49746.1108586111;
    AuxParam.n = 20;
    AuxParam.m = 20;
    AuxParam.sun = 1;
    AuxParam.moon = 1;
    AuxParam.planets = 1;
	
    Matrix A(3);
    A(1) = 0; A(2) = 2; A(3) = 8;
    A = transpose(A);
    cout << A << endl;
    cout << A.extract_vector(1,2) << endl;
	

    return 0;
}
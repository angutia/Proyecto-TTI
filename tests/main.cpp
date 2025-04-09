#include "..\include\matrix.h"
#include "..\include\R_x.hpp"
#include <iostream>

using namespace std;

int main() {
	Matrix aux = R_x(3);
	cout << "aux\n" << aux << "\n";
	
	
	
    Matrix M1(3, 2);
	M1(1,1) = 5;
	
    Matrix M2(3, 2);
	M2(1,1) = -3;
	
    Matrix M3 = M1 - M2;
	
    cout << "M1\n" << M1 << "\n";
    cout << "M2\n" << M2 << "\n";
    cout << "M3\n" << M3 << "\n";
	
	
	Matrix m1(3,2);
	m1(1,1) = 1; m1(1,2) = 2;
	m1(2,1) = 2; m1(2,2) = 3;
	m1(3,1) = 1; m1(3,2) = 4;
	
	Matrix m2(2,4);
	m2(1,1) = 1; m2(1,2) = 2; m2(1,3) = 1; m2(1,4) = -2;
	m2(2,1) = 4; m2(2,2) = -1; m2(2,3) = 3; m2(2,4) = 1;
	cout << "m1\n" << m1 << "\n";
	cout << "m2\n" << m2 << "\n";
	Matrix M4 = m1*m2;
	cout << "M4\n" << M4 << "\n";
	
	cout << M1(1,1) << "\n";



    Matrix A(3, 4);
	A(1,1) = 0; A(1,2) = 2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) = 1; A(3,3) = 0; A(3,4) = 5;
	
	Matrix B(4, 3);
	B(1,1) = 2; B(1,2) = 0; B(1,3) = 0;
	B(2,1) = 7; B(2,2) = -2; B(2,3) = 1;
	B(3,1) = 0; B(3,2) = -3; B(3,3) = 0;
    B(4,1) = 1; B(4,2) = 0; B(4,3) = -2;

    cout << "A\n" << A << "\n";
	cout << "B\n" << B << "\n";
	Matrix C = A*B;
	cout << "C\n" << C << "\n";
	
	
	
	Matrix D(4, 4);
	D(1,1) = 2; D(1,2) = 0; D(1,3) = 0; D(1,4) = 1;
	D(2,1) = 7; D(2,2) = -2; D(2,3) = 1; D(2,4) = 0;
	D(3,1) = 0; D(3,2) = -3; D(3,3) = 0; D(3,4) = 2;
    D(4,1) = 1; D(4,2) = 0; D(4,3) = -2; D(4,4) = -2;

	cout << "D\n" << D << "\n";
	cout << "inv(D)\n" << inv(D) << "\n";
	Matrix E = A/D;
	cout << "E=A/D\n" << E << "\n";
	E = D*inv(D);
	cout << "E = D*inv(D)\n" << E << "\n";
	
	cout << "det(m1)\n" << det(m1) << "\n";
	

    return 0;
}
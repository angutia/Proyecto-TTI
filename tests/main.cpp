#include "..\include\matrix.h"
#include <iostream>

using namespace std;

int main() {
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

    return 0;
}
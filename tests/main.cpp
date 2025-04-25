#include "..\include\matrix.hpp"
#include "..\include\R_x.hpp"
#include "..\include\global.hpp"
#include <iostream>

using namespace std;

int main() {
	eop19620101(4); // c = 21413
	cout << eopdata;
	
	Matrix aux = R_x(3);
	cout << "aux\n" << aux << "\n";
	
	
	Matrix m1(3,2);
	m1(1,1) = 1; m1(1,2) = 2;
	m1(2,1) = 2; m1(2,2) = 3;
	m1(3,1) = 1; m1(3,2) = 4;
	
	Matrix m2(2,4);
	m2(1,1) = 1; m2(1,2) = 2; m2(1,3) = 1; m2(1,4) = -2;
	m2(2,1) = 4; m2(2,2) = -1; m2(2,3) = 3; m2(2,4) = 1;
	cout << "m1\n" << m1 << "\n";
	cout << "m2\n" << m2 << "\n";

	cout << "m1 + 5\n" << m1 + 5 << "\n";
	cout << "m1 - 2\n" << m1 - 2 << "\n";
	
	
	Matrix m3 = m1;
	m3(1,1) = 999;
	cout << "m3\n" << m3 << "\n";
	cout << "m1\n" << m1 << "\n";
	

    return 0;
}
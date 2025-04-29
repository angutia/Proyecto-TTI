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
    cout << "m1 * 2\n" << m1 * 2 << "\n";
    cout << "m1 / 2\n" << m1 / 2 << "\n";
	
	
	Matrix m3 = m1;
    cout << "m1\n" << m1 << "\n";
    cout << "m3\n" << m3 << "\n";
	m3(1,1) = 999;
    cout << "m1\n" << m1 << "\n";
	cout << "m3\n" << m3 << "\n";

    Matrix v(4);
    v(1) = 1; v(2) = 2; v(3) = 3; v(4) = 4;
    cout << "v\n" << v << "\n";
    cout << "norm(v)\n" << norm(v) << "\n";

    Matrix m5(2,3);
    m5(1,1) = 1; m5(1,2) = 2; m5(1,3) = 3;
    m5(2,1) = 4; m5(2,2) = 5; m5(2,3) = 6;
    cout << "m5\n" << m5 << "\n";
    cout << "norm(m5)\n" << norm(m5) << "\n";

    Matrix v1(3);
    v1(1) = 1; v1(2) = 2; v1(3) = 3;
    Matrix v2(3);
    v2(1) = 4; v2(2) = 5; v2(3) = 6;
    cout << "v1\n" << v1 << "\n";
    cout << "v2\n" << v2 << "\n";
    cout << "dot(v1, v2)\n" << dot(v1, v2) << "\n";
    cout << "cross(v1, v2)\n" << cross(v1, v2) << "\n";

    Matrix v3 = v1.extract_vector(2, 3);
    cout << "v3\n" << v3 << "\n";
	

    return 0;
}
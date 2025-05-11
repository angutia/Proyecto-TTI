#include "..\include\matrix.hpp"
#include "..\include\global.hpp"
#include "..\include\AccelPointMass.hpp"
#include "..\include\Cheb3D.hpp"
#include "..\include\EccAnom.hpp"
#include "..\include\Frac.hpp"
#include "..\include\MeanObliquity.hpp"
#include "..\include\Mjday.hpp"
#include "..\include\Mjday_TDB.hpp"
#include "..\include\Position.hpp"
#include "..\include\R_x.hpp"
#include "..\include\R_y.hpp"
#include "..\include\R_z.hpp"
#include "..\include\sign_.hpp"
#include "..\include\timediff.hpp"
#include "..\include\AzElPa.hpp"
#include "..\include\IERS.hpp"
#include "..\include\Legendre.hpp"
#include <cstdio>
#include <cmath>

int tests_run = 0;

#define FAIL() printf("\nfailure in %s() line %d\n", __func__, __LINE__)
#define _assert(test) do { if (!(test)) { FAIL(); return 1; } } while(0)
#define _verify(test) do { int r=test(); tests_run++; if(r) return r; } while(0)

int m_equals(Matrix A, Matrix B, double p) {
	if (A.n_row != B.n_row || A.n_column != B.n_column)
		return 0;
	else
		for(int i = 1; i <= A.n_row; i++)
			for(int j = 1; j <= A.n_column; j++)
				if(fabs(A(i,j)-B(i,j)) > p) {
					printf("%2.20lf %2.20lf\n",A(i,j),B(i,j));
					return 0;
				}
	
	return 1;
}

int m_sum_01() {
    int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) =  2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) =  1; A(3,3) = 0; A(3,4) = 5;
	
	Matrix B(f, c);
	B(1,1) = 2; B(1,2) =  0; B(1,3) = 0; B(1,4) = 0;
	B(2,1) = 7; B(2,2) = -2; B(2,3) = 1; B(2,4) = 0;
	B(3,1) = 0; B(3,2) = -3; B(3,3) = 0; B(3,4) = 2;
	
	Matrix C(f, c);
	C(1,1) = 2; C(1,2) =  2; C(1,3) = 8; C(1,4) = 0;
	C(2,1) = 8; C(2,2) = -3; C(2,3) = 1; C(2,4) = 0;
	C(3,1) = 0; C(3,2) = -2; C(3,3) = 0; C(3,4) = 7;
	
	Matrix R = A + B;
    
    _assert(m_equals(C, R, 1e-10));
    
    return 0;
}

int m_sumn_01() {
    int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) =  2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) =  1; A(3,3) = 0; A(3,4) = 5;
	
	Matrix C(f, c);
	C(1,1) = 4.5; C(1,2) = 6.5; C(1,3) = 12.5; C(1,4) = 4.5;
	C(2,1) = 5.5; C(2,2) = 3.5; C(2,3) = 4.5; C(2,4) = 4.5;
	C(3,1) = 4.5; C(3,2) = 5.5; C(3,3) = 4.5; C(3,4) = 9.5;
	
	Matrix R = A + 4.5;
    
    _assert(m_equals(C, R, 1e-10));
    
    return 0;
}

int m_sub_01() {
    int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) = 2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) = 1; A(3,3) = 0; A(3,4) = 5;
	
	Matrix B(f, c);
	B(1,1) = 2; B(1,2) = 0; B(1,3) = 0; B(1,4) = 0;
	B(2,1) = 7; B(2,2) = -2; B(2,3) = 1; B(2,4) = 0;
	B(3,1) = 0; B(3,2) = -3; B(3,3) = 0; B(3,4) = 2;
	
	Matrix C(f, c);
	C(1,1) = -2; C(1,2) = 2; C(1,3) = 8; C(1,4) = 0;
	C(2,1) = -6; C(2,2) = 1; C(2,3) = -1; C(2,4) = 0;
	C(3,1) = 0; C(3,2) = 4; C(3,3) = 0; C(3,4) = 3;
	
	Matrix R = A - B;
    
    _assert(m_equals(C, R, 1e-10));
    
    return 0;
}

int m_subn_01() {
    int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) =  2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) =  1; A(3,3) = 0; A(3,4) = 5;
	
	Matrix C(f, c);
	C(1,1) = -1.1; C(1,2) = 0.9; C(1,3) = 6.9; C(1,4) = -1.1;
	C(2,1) = -0.1; C(2,2) = -2.1; C(2,3) = -1.1; C(2,4) = -1.1;
	C(3,1) = -1.1; C(3,2) = -0.1; C(3,3) = -1.1; C(3,4) = 3.9;
	
	Matrix R = A - 1.1;
    
    _assert(m_equals(C, R, 1e-10));
    
    return 0;
}

int m_mul_01() {
    int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) = 2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) = 1; A(3,3) = 0; A(3,4) = 5;
	
	Matrix B(c, f);
	B(1,1) = 2; B(1,2) = 0; B(1,3) = 0;
	B(2,1) = 7; B(2,2) = -2; B(2,3) = 1;
	B(3,1) = 0; B(3,2) = -3; B(3,3) = 0;
    B(4,1) = 1; B(4,2) = 0; B(4,3) = -2;
	
	Matrix C(f, f);
	C(1,1) = 14; C(1,2) = -28; C(1,3) = 2;
	C(2,1) = -5; C(2,2) = 2; C(2,3) = -1;
	C(3,1) = 12; C(3,2) = -2; C(3,3) = -9;
	
	Matrix R = A * B;

    _assert(m_equals(C, R, 1e-10));
    
    return 0;
}

int m_muln_01() {
    int f = 3;
    int c = 4;
    
    Matrix A(f, c);
    A(1,1) = 0; A(1,2) = 2; A(1,3) = 8; A(1,4) = 0;
    A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
    A(3,1) = 0; A(3,2) = 1; A(3,3) = 0; A(3,4) = 5;
    
    Matrix C(f, c);
    C(1,1) = 0; C(1,2) = 0.5; C(1,3) = 2; C(1,4) = 0;
    C(2,1) = 0.25; C(2,2) = -0.25; C(2,3) = 0; C(2,4) = 0;
    C(3,1) = 0; C(3,2) = 0.25; C(3,3) = 0; C(3,4) = 1.25;
    
    Matrix R = A * 0.25;

    _assert(m_equals(C, R, 1e-10));
    
    return 0;
}

int m_div_01() {
    int f = 3;
    int c = 3;
    
    Matrix A(f, c);
    A(1,1) = 0; A(1,2) = 2; A(1,3) = 8;
    A(2,1) = 1; A(2,2) = -1; A(2,3) = 0;
    A(3,1) = 0; A(3,2) = 1; A(3,3) = 0;
    
    Matrix B(f, c);
    B(1,1) = 2; B(1,2) = 0; B(1,3) = 0;
    B(2,1) = 7; B(2,2) = -2; B(2,3) = 1;
    B(3,1) = 0; B(3,2) = -3; B(3,3) = 0;
    
    Matrix C(f, f);
    C(1,1) = -28; C(1,2) = 8; C(1,3) = -6;
    C(2,1) = 0.5; C(2,2) = 0; C(2,3) = 0.3333333333;
    C(3,1) = 0; C(3,2) = 0; C(3,3) = -0.3333333333;
    
    Matrix R = A / B;

    _assert(m_equals(C,R , 1e-10));
    
    return 0;
}

int m_divn_01() {
    int f = 4;
    int c = 3;
    
    Matrix A(f, c);
    A(1,1) = 0; A(1,2) = 2; A(1,3) = 8;
    A(2,1) = 1; A(2,2) = -1; A(2,3) = 0;
    A(3,1) = 0; A(3,2) = 1; A(3,3) = 0;
    A(4,1) = 0; A(4,2) = 5; A(4,3) = 0;
    
    Matrix C(f, c);
    C(1,1) = 0; C(1,2) = 0.5; C(1,3) = 2;
    C(2,1) = 0.25; C(2,2) = -0.25; C(2,3) = 0;
    C(3,1) = 0; C(3,2) = 0.25; C(3,3) = 0;
    C(4,1) = 0; C(4,2) = 1.25; C(4,3) = 0;
    
    Matrix R = A / 4;

    _assert(m_equals(C,R , 1e-10));
    
    return 0;
}

int v_extract_vector_01() {
    int f = 4;
    
    Matrix A(f);
    A(1) = 0; A(2) = 2; A(3) = 8; A(4) = 0;
    
    Matrix B = A.extract_vector(2, 3);
    
    Matrix C(2);
    C(1) = 2; C(2) = 8;
    
    _assert(m_equals(B, C, 1e-10));
    
    return 0;
}

int m_extract_row_01() {
    int f = 3;
    int c = 4;
    
    Matrix A(f, c);
    A(1,1) = 0; A(1,2) = 2; A(1,3) = 8; A(1,4) = 0;
    A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
    A(3,1) = 0; A(3,2) = 1; A(3,3) = 0; A(3,4) = 5;
    
    Matrix B = A.extract_row(2);
    
    Matrix C(c);
    C(1) = 1; C(2) = -1; C(3) = 0; C(4) = 0;
    
    _assert(m_equals(B, C, 1e-10));
    
    return 0;
}

int m_extract_column_01() {
    int f = 3;
    int c = 4;
    
    Matrix A(f, c);
    A(1,1) = 0; A(1,2) = 2; A(1,3) = 8; A(1,4) = 0;
    A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
    A(3,1) = 0; A(3,2) = 1; A(3,3) = 0; A(3,4) = 5;
    
    Matrix B = A.extract_column(2);
    
    Matrix C(f);
    C(1) = 2; C(2) = -1; C(3) = 1;
    
    _assert(m_equals(B, C, 1e-10));
    
    return 0;
}

int m_assign_row_01() {
    int f = 3;
    int c = 4;
    
    Matrix A(f, c);
    A(1,1) = 0; A(1,2) = 2; A(1,3) = 8; A(1,4) = 0;
    A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
    A(3,1) = 0; A(3,2) = 1; A(3,3) = 0; A(3,4) = 5;
    
    Matrix B(c);
    B(1) = 10; B(2) = -10; B(3) = -10; B(4) = 0;

    Matrix C(f, c);
    C(1,1) = 0; C(1,2) = 2; C(1,3) = 8; C(1,4) = 0;
    C(2,1) = 10; C(2,2) = -10; C(2,3) = -10; C(2,4) = 0;
    C(3,1) = 0; C(3,2) = 1; C(3,3) = 0; C(3,4) = 5;
    
    A.assign_row(2, B);
    
    _assert(m_equals(A, C, 1e-10));
    
    return 0;
}

int m_assign_column_01() {
    int f = 3;
    int c = 4;
    
    Matrix A(f, c);
    A(1,1) = 0; A(1,2) = 2; A(1,3) = 8; A(1,4) = 0;
    A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
    A(3,1) = 0; A(3,2) = 1; A(3,3) = 0; A(3,4) = 5;
    
    Matrix B(f);
    B(1) = 10; B(2) = -10; B(3) = -10;

    Matrix C(f, c);
    C(1,1) = 10; C(1,2) = 2; C(1,3) = 8; C(1,4) = 0;
    C(2,1) = -10; C(2,2) = -1; C(2,3) = 0; C(2,4) = 0;
    C(3,1) = -10; C(3,2) = 1; C(3,3) = 0; C(3,4) = 5;
    
    A.assign_column(1, B);
    
    _assert(m_equals(A, C, 1e-10));
    
    return 0;
}

int m_zeros_01() {
    int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) = 0; A(1,3) = 0; A(1,4) = 0;
	A(2,1) = 0; A(2,2) = 0; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) = 0; A(3,3) = 0; A(3,4) = 0;
	
	Matrix B = zeros(3, 4);
    
    _assert(m_equals(A, B, 1e-10));
    
    return 0;
}

int v_zeros_01() {
    int f = 4;
    
    Matrix A(f);
    A(1) = 0; A(2) = 0; A(3) = 0; A(4) = 0;
    
    Matrix B = zeros(4);
    
    _assert(m_equals(A, B, 1e-10));
    
    return 0;
}

int m_eye_01() {
    int f = 3;
    int c = 3;
	
	Matrix A(f, c);
	A(1,1) = 1; A(1,2) = 0; A(1,3) = 0;
	A(2,1) = 0; A(2,2) = 1; A(2,3) = 0;
	A(3,1) = 0; A(3,2) = 0; A(3,3) = 1;
	
	Matrix B = eye(f);
    
    _assert(m_equals(A, B, 1e-10));
    
    return 0;
}

int m_transpose_01() {
    int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 1; A(1,2) = 2; A(1,3) = 3; A(1,4) = 4;
	A(2,1) = 2; A(2,2) = 3; A(2,3) = 9; A(2,4) = -2;
	A(3,1) = 1; A(3,2) = 7; A(3,3) = 0; A(3,4) = 5;
	
	Matrix B = transpose(A);
	
	Matrix C(c, f);
	C(1,1) = 1; C(1,2) = 2; C(1,3) = 1;
	C(2,1) = 2; C(2,2) = 3; C(2,3) = 7;
	C(3,1) = 3; C(3,2) = 9; C(3,3) = 0;
	C(4,1) = 4; C(4,2) = -2; C(4,3) = 5;
    
    _assert(m_equals(B, C, 1e-10));
    
    return 0;
}

int m_inv_01() {
    int f = 3;
    int c = 3;
	
	Matrix A(f, c);
	A(1,1) = 1; A(1,2) = 2; A(1,3) = 3;
	A(2,1) = 2; A(2,2) = 3; A(2,3) = 9;
	A(3,1) = 1; A(3,2) = 7; A(3,3) = 0;
	
	Matrix B = inv(A);
	
	Matrix C(f, c);
	C(1,1) = 5.25; C(1,2) = -1.75; C(1,3) = -0.75;
	C(2,1) = -0.75; C(2,2) = 0.25; C(2,3) = 0.25;
	C(3,1) = -0.9166666666; C(3,2) = 0.41666666666; C(3,3) = 0.08333333333;
    
    _assert(m_equals(B, C, 1e-10));
    
    return 0;
}

int m_norm_01() {
    int f = 1;
    int c = 4;
    
    Matrix A(f, c);
    A(1,1) = 0; A(1,2) = 2; A(1,3) = 8; A(1,4) = 0;
    
    double C = norm(A);

    _assert(fabs(C - 8.246211251235321) < 1e-10);
    
    return 0;
}

int v_dot_01() {
    int f = 4;
    
    Matrix A(f);
    A(1) = 0; A(2) = 2; A(3) = 8; A(4) = 0;
    
    Matrix B(f);
    B(1) = 1; B(2) = -1; B(3) = 1; B(4) = 0;
    
    double C = dot(A, B);
    
    _assert(fabs(C - 6) < 1e-10);
    
    return 0;
}

int v_cross_01() {
    int f = 3;
    
    Matrix A(f);
    A(1) = 0; A(2) = 2; A(3) = 8;
    
    Matrix B(f);
    B(1) = 1; B(2) = -1; B(3) = 0;
    
    Matrix C(f);
    C(1) = 8; C(2) = 8; C(3) = -2;
    
    Matrix R = cross(A, B);
    
    _assert(m_equals(C, R, 1e-10));
    
    return 0;
}

int v_union_vector_01() {
    int f = 3;
    
    Matrix A(f);
    A(1) = 0; A(2) = 2; A(3) = 8;
    
    Matrix B(f);
    B(1) = 1; B(2) = -1; B(3) = 0;
    
    Matrix C(f + f);
    C(1) = 0; C(2) = 2; C(3) = 8; C(4) = 1; C(5) = -1; C(6) = 0;
    
    Matrix R = union_vector(A, B);
    
    _assert(m_equals(C, R, 1e-10));
    
    return 0;
}

int AccelPointMass_01() {
    int f = 3;

    Matrix r(f);
    r(1) = 0; r(2) = 2; r(3) = 8;

    Matrix s(f);
    s(1) = 1; s(2) = -1; s(3) = 0;

    double GM = 2.0;

    Matrix C(f);
    C(1) = -0.703964953112390; C(2) = 0.697681296964076; C(3) = -0.025134624593258;

    Matrix R = AccelPointMass(r, s, GM);

    _assert(m_equals(C, R, 1e-10));

    return 0;
}

int Cheb3D_01() {
    int f = 3;

    int t = 1;
    int N = 3;
    int Ta = 0;
    int Tb = 3;
    Matrix Cx(f);
    Cx(1) = 0; Cx(2) = 2; Cx(3) = 8;
    Matrix Cy(f);
    Cy(1) = 1; Cy(2) = -1; Cy(3) = 0;
    Matrix Cz(f);
    Cz(1) = 0; Cz(2) = 1; Cz(3) = 5;

    Matrix C(f);
    C(1) = -6.888888888888889; C(2) = 1.333333333333333; C(3) = -4.222222222222222;

    Matrix R = Cheb3D(t, N, Ta, Tb, Cx, Cy, Cz);

    _assert(m_equals(C, R, 1e-10));

    return 0;
}

int EccAnom_01(){
    double M = 2.93;
    double e = 0.76;

    double C = 3.021244195604439;

    double R = EccAnom(M, e);

    _assert(fabs(C - R) < 1e-10);

    return 0;
}

int Frac_01() {
    double x = 1.5632498;

    double C = 0.5632498;

    double R = Frac(x);

    _assert(fabs(C - R) < 1e-10);

    return 0;
}

int MeanObliquity_01() {
    double Mjd_TT = 58000.0;

    double C = 0.40905268985035;

    double R = MeanObliquity(Mjd_TT);

    _assert(fabs(C - R) < 1e-10);

    return 0;
}

int Mjday_01() {
    double yr = 2025;
    double mon = 3;
    double day = 28;

    double C = 60762;

    double R = Mjday(yr, mon, day);

    _assert(fabs(C - R) < 1e-10);


    double hr = 16;
    double min = 24;
    double sec = 16;

    C = 60762.6835185187;

    R = Mjday(yr, mon, day, hr, min, sec);

    _assert(fabs(C - R) < 1e-10);

    return 0;
}

int Mjday_TDB_01() {
    double Mjd_TT = 58000.0;

    double C = 57999.9999999833;

    double R = Mjday_TDB(Mjd_TT);

    _assert(fabs(C - R) < 1e-10);

    return 0;
}

int Position_01() {
    double x = 235.35;
    double y = 2344;
    double z = 90.13;

    Matrix C(3);
    C(1) = -5730370.47656876; C(2) = 1582528.00953351; C(3) = 2303146.25187731;

    Matrix R = Position(x,y,z);

    _assert(m_equals(C, R, 1e-6));

    return 0;
}

int R_x_01() {
    double angle = 0.5;

    Matrix C(3, 3);
    C(1,1) = 1; C(1,2) = 0; C(1,3) = 0;
    C(2,1) = 0; C(2,2) = 0.877582561890373; C(2,3) = 0.479425538604203;
    C(3,1) = 0; C(3,2) = -0.479425538604203; C(3,3) = 0.877582561890373;

    Matrix R = R_x(angle);

    _assert(m_equals(C, R, 1e-10));

    return 0;
}

int R_y_01() {
    double angle = 0.4;

    Matrix C(3, 3);
    C(1,1) = 0.921060994002885; C(1,2) = 0; C(1,3) = -0.389418342308651;
    C(2,1) = 0; C(2,2) = 1; C(2,3) = 0;
    C(3,1) = 0.389418342308651; C(3,2) = 0; C(3,3) = 0.921060994002885;

    Matrix R = R_y(angle);

    _assert(m_equals(C, R, 1e-10));

    return 0;
}

int R_z_01() {
    double angle = 0.3;

    Matrix C(3, 3);
    C(1,1) = 0.955336489125606; C(1,2) = 0.29552020666134; C(1,3) = 0;
    C(2,1) = -0.29552020666134; C(2,2) = 0.955336489125606; C(2,3) = 0;
    C(3,1) = 0; C(3,2) = 0; C(3,3) = 1;

    Matrix R = R_z(angle);

    _assert(m_equals(C, R, 1e-10));

    return 0;
}

int sign__01(){
    double a = 5.3;
    double b = -2;
    double c = 9.7;

    double C = -5.3;
    double R = sign_(a,b);

    _assert(fabs(C - R) < 1e-10);

    C = 5.3;
    R = sign_(a,c);
    _assert(fabs(C - R) < 1e-10);

    return 0;
}

int timediff_01() {
    double UT1_UTC = 24.63;
    double TAI_UTC = 9.71;

    double A = 14.92;
    double B = 9.29;
    double C = 33.92;
    double D = 41.894;
    double E = -9.29;

    auto [a,b,c,d,e] = timediff(UT1_UTC, TAI_UTC);
    
    _assert(fabs(A - a) < 1e-10);
    _assert(fabs(B - b) < 1e-10);
    _assert(fabs(C - c) < 1e-10);
    _assert(fabs(D - d) < 1e-10);
    _assert(fabs(E - e) < 1e-10);

    return 0;
}

int AzElPa_01() {
    Matrix s(3);
    s(1) = 2; s(2) = 3; s(3) = 4;

    double A = 0.588002603547568;
    double B = 0.837215003154814;
    Matrix C(3);
    C(1) = 0.230769230769231; C(2) = -0.153846153846154; C(3) = 0;
    Matrix D(3);
    D(1) = -0.0765103718931351; D(2) = -0.114765557839703; D(3) = 0.124329354326344;

    auto [a,b,c,d] = AzElPa(s);

    _assert(fabs(A - a) < 1e-10);
    _assert(fabs(B - b) < 1e-10);
    _assert(m_equals(C, c, 1e-10));
    _assert(m_equals(D, d, 1e-10));
    
    return 0;
}

int IERS_01() {
    double Mjd_UTC = 49746.1163541665;

    double A = -5.59518621231704e-07;
    double B = 2.33458634442529e-06;
    double C = 0.3260677;
    double D = 0.0027213;
    double E = -1.16864337831454e-07;
    double F = -2.48709418409192e-08;
    double G = -8.19335121075116e-10;
    double H = -1.53201123230613e-09;
    double I = 29;

    auto [a,b,c,d,e,f,g,h,i] = IERS(eopdata, Mjd_UTC);

    _assert(fabs(A - a) < 1e-17);
    _assert(fabs(B - b) < 1e-16);
    _assert(fabs(C - c) < 1e-10);
    _assert(fabs(D - d) < 1e-10);
    _assert(fabs(E - e) < 1e-17);
    _assert(fabs(F - f) < 1e-18);
    _assert(fabs(G - g) < 1e-20);
    _assert(fabs(H - h) < 1e-19);
    _assert(fabs(I - i) < 1e-10);

    return 0;
}

int Legendre_01() {
    int n = 3;
    int m = 4;
    double fi = 2.24;

    Matrix A(n+1, m+1);
    A(1,1) = 1; A(1,2) = 0.0; A(1,3) = 0.0; A(1,4) = 0.0; A(1,5) = 0.0;
    A(2,1) = 1.3584750314316; A(2,2) = -1.07449783107129; A(2,3) = 0.0; A(2,4) = 0.0; A(2,5) = 0.0;
    A(3,1) = 0.945246767462336; A(3,2) = -1.8844368079547; A(3,3) = 0.745255973090802; A(3,4) = 0.0; A(3,5) = 0.0;
    A(4,1) = 0.0786022253778292; A(4,2) = -2.08634513956977; A(4,3) = 1.54648431188699; A(4,4) = -0.4993715268682; A(4,5) = 0.0;

    Matrix B(n+1, m+1);
    B(1,1) = 0.0; B(1,2) = 0.0; B(1,3) = 0.0; B(1,4) = 0.0; B(1,5) = 0.0;
    B(2,1) = -1.07449783107129; B(2,2) = -1.3584750314316; B(2,3) = 0.0; B(2,4) = 0.0; B(2,5) = 0.0;
    B(3,1) = -3.26394029503045; B(3,2) = -0.891959453844208; B(3,3) = 1.8844368079547; B(3,4) = 0.0; B(3,5) = 0.0;
    B(4,1) = -5.11048101928169; B(4,2) = 2.25267105081762; B(4,3) = 2.68719859668037; B(4,4) = -1.89404872967114; B(4,5) = 0.0;

    auto [a,b] = Legendre(n, m, fi);
    _assert(m_equals(A, a, 1e-10));
    _assert(m_equals(B, b, 1e-10));

    return 0;
}


int all_tests()
{
    _verify(m_sum_01);
	_verify(m_sumn_01);
    _verify(m_sub_01);
	_verify(m_subn_01);
    _verify(m_mul_01);
    _verify(m_muln_01);
    _verify(m_div_01);
    _verify(m_divn_01);
    _verify(v_extract_vector_01);
    _verify(m_extract_row_01);
    _verify(m_extract_column_01);
    _verify(m_assign_row_01);
    _verify(m_assign_column_01);
    _verify(m_zeros_01);
    _verify(v_zeros_01);
	_verify(m_eye_01);
	_verify(m_transpose_01);
	_verify(m_inv_01);
    _verify(m_norm_01);
    _verify(v_dot_01);
    _verify(v_cross_01);
    _verify(v_union_vector_01);
    _verify(AccelPointMass_01);
    _verify(Cheb3D_01);
    _verify(EccAnom_01);
    _verify(Frac_01);
    _verify(MeanObliquity_01);
    _verify(Mjday_01);
    _verify(Mjday_TDB_01);
    _verify(Position_01);
    _verify(R_x_01);
    _verify(R_y_01);
    _verify(R_z_01);
    _verify(sign__01);
    _verify(timediff_01);
    _verify(AzElPa_01);
    _verify(IERS_01);
    _verify(Legendre_01);

    return 0;
}


int main()
{
    eop19620101(40000);

    int result = all_tests();

    if (result == 0)
        printf("PASSED\n");

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}

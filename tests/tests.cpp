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
#include "..\include\NutAngles.hpp"
#include "..\include\TimeUpdate.hpp"
#include "..\include\AccelHarmonic.hpp"
#include "..\include\EqnEquinox.hpp"
#include "..\include\LTC.hpp"
#include "..\include\NutMatrix.hpp"
#include "..\include\JPL_Eph_DE430.hpp"
#include "..\include\PoleMatrix.hpp"
#include "..\include\PrecMatrix.hpp"
#include "..\include\gmst.hpp"
#include "..\include\gast.hpp"
#include "..\include\MeasUpdate.hpp"
#include "..\include\G_AccelHarmonic.hpp"
#include "..\include\GHAMatrix.hpp"
#include "..\include\Accel.hpp"
#include "..\include\VarEqn.hpp"
#include "..\include\DEInteg.hpp"
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

int NutAngles_01() {
    double Mjd_UTC = 83746.12;

    double A = 5.88403005430328e-05;
    double B = -3.2505118763951e-05;

    auto [a,b] = NutAngles(Mjd_UTC);

    _assert(fabs(A - a) < 1e-8);
    _assert(fabs(B - b) < 1e-8);

    return 0;
}

int TimeUpdate_01() {
    Matrix P(3,3);
    P(1,1) = 9; P(1,2) = 8; P(1,3) = 9;
    P(2,1) = 4; P(2,2) = 5; P(2,3) = 6;
    P(3,1) = 3; P(3,2) = 2; P(3,3) = 0;

    Matrix Phi(2,3);
    Phi(1,1) = 1; Phi(1,2) = 2; Phi(1,3) = 3;
    Phi(2,1) = 4; Phi(2,2) = 5; Phi(2,3) = 6;

    Matrix R = TimeUpdate(P, Phi, 2);

    Matrix C(2,2);
    C(1,1) = 139; C(1,2) = 352;
    C(2,1) = 412; C(2,2) = 1039;

    _assert(m_equals(R, C, 1e-10));

    return 0;
}

int AccelHarmonic_01() {
    Matrix r(3);
    r(1) = 5; r(2) = 3; r(3) = 6.5;

    Matrix E(3,3);
    E(1,1) = 1; E(1,2) = 2; E(1,3) = 3;
    E(2,1) = 4; E(2,2) = 5; E(2,3) = 6;
    E(3,1) = 7; E(3,2) = 8; E(3,3) = 9;

    int n_max = 4;
    int m_max = 5;

    Matrix C = AccelHarmonic(transpose(r), E, n_max, m_max);

    Matrix R(3);
    R(1) = 6.17908715598067e+24; R(2) = 7.32798396948108e+24; R(3) = 8.47688078298148e+24;
    
    _assert(m_equals(transpose(C), R, 1e+10));

    return 0;
}

int EqnEquinox_01() {
    double Mjd_UTC = 23551.2;

    double A = EqnEquinox(Mjd_UTC);
    
    double a = -2.24482778139221e-05;

    _assert(fabs(A - a) < 1e-7);

    return 0;
}

int LTC_01() {
    double lon = 234;
    double lat = 15.2;

    Matrix C(3,3);
    C(1,1) = -0.998816691202808; C(1,2) = 0.0486335005389691; C(1,3) = 0;
    C(2,1) = -0.0236552708965251; C(2,2) = -0.485823129006337; C(2,3) = -0.87373698301108;
    C(3,1) = -0.0424928880341866; C(3,2) = -0.872703082352651; C(3,3) = 0.4863986888538;

    Matrix R = LTC(lon, lat);

    _assert(m_equals(C, R, 1e-10));

    return 0;
}

int NutMatrix_01() {
    double Mjd_TT = 235.9173;

    Matrix C(3,3);
    C(1,1) = 0.999999998585968; C(1,2) = -4.87845314796075e-05; C(1,3) = -2.11691613886533e-05;
    C(2,1) = 4.87838437796019e-05; C(2,2) = 0.999999998282423; C(2,3) = -3.24852356541339e-05;
    C(3,1) = 2.1170746129295e-05; C(3,2) = 3.24842028951444e-05; C(3,3) = 0.999999999248288;

    Matrix R = NutMatrix(Mjd_TT);

    _assert(m_equals(C, R, 1e-8));

    return 0;
}

int JPL_Eph_DE430_01() {
    double Mjd_TDB = 59726.91;

    Matrix A(3);
    A(1) = 45624943907.0238; A(2) = 66610814401.4845; A(3) = 24350539316.9015;
    Matrix B(3);
    B(1) = 156041917196.322; B(2) = 81414818272.6245; B(3) = 28521345918.8757;
    Matrix C(3);
    C(1) = -62313632426.8118; C(2) = -127060711361.205; C(3) = -55048145195.1134;
    Matrix D(3);
    D(1) = 221075870798.561; D(2) = 9340551553.04433; D(3) = -3242845351.76138;
    Matrix E(3);
    E(1) = 797099670109.136; E(2) = 41752247633.327; E(3) = 596693478.124687;
    Matrix F(3);
    F(1) = 1179258547126.20; F(2) = -749619410188.408; F(3) = -355173538778.337;
    Matrix G(3);
    G(1) = 2154257860353.50; G(2) = 2038632460078.54; G(3) = 862677136874.476;
    Matrix H(3);
    H(1) = 4502545520335.66; H(2) = -334529543081.609; H(3) = -244429338162.394;
    Matrix I(3);
    I(1) = 2387424254946.29; I(2) = -4029844389371.32; I(3) = -1942743917545.93;
    Matrix J(3);
    J(1) = 314714672.316101; J(2) = 226384796.318904; J(3) = 88055992.3880059;
    Matrix K(3);
    K(1) = 60972567794.3542; K(2) = 127333684449.306; K(3) = 55197846561.2721;

    auto [a,b,c,d,e,f,g,h,i,j,k] = JPL_Eph_DE430(Mjd_TDB);

    _assert(m_equals(transpose(A), a, 1e-2));
    _assert(m_equals(transpose(B), b, 1e-2));
    _assert(m_equals(transpose(C), c, 1e-2));
    _assert(m_equals(transpose(D), d, 1e-2));
    _assert(m_equals(transpose(E), e, 1e-2));
    _assert(m_equals(transpose(F), f, 1e-2));
    _assert(m_equals(transpose(G), g, 1e-2));
    _assert(m_equals(transpose(H), h, 1e-2));
    _assert(m_equals(transpose(I), i, 1e-2));
    _assert(m_equals(transpose(J), j, 1e-2));
    _assert(m_equals(transpose(K), k, 1e-2));

    return 0;
}

int PoleMatrix_01() {
    double xp = 24.3;
    double yp = 155;

    Matrix C(3,3);
    C(1,1) = 0.672850388318347; C(1,2) = 0.646057502948598; C(1,3) = 0.360391534062153;
    C(2,1) = 0; C(2,2) = -0.487161349803341; C(2,3) = 0.873311982774648;
    C(3,1) = 0.739778585077893; C(3,2) = -0.587608306732987; C(3,3) = -0.327786703388868;

    Matrix R = PoleMatrix(xp,yp);

    _assert(m_equals(C, R, 1e-10));

    return 0;
}

int PrecMatrix_01() {
    double Mjd_1 = 31.425;
    double Mjd_2 = 3512.8;

    Matrix C(3,3);
    C(1,1) = 0.9999973028945; C(1,2) = -0.00212964323490222; C(1,3) = -0.000926727261271979;
    C(2,1) = 0.00212964323488723; C(2,2) = 0.999997732306788; C(2,3) = -9.86816720735239e-07;
    C(3,1) = 0.000926727261306412; C(3,2) = -9.86784383367008e-07; C(3,3) = 0.999999570587712;

    Matrix R = PrecMatrix(Mjd_1, Mjd_2);

    _assert(m_equals(C, R, 1e-10));

    return 0;
}

int gmst_01() {
    double Mjd_UT1 = 14752.197;

    double A = 4.66255041375004;

    double R = gmst(Mjd_UT1);

    _assert(fabs(A - R) < 1e-10);

    return 0;
}

int gast_01() {
    double Mjd_UT1 = 2876.918;

    double A = 5.96671101553505;

    double R = gast(Mjd_UT1);

    _assert(fabs(A - R) < 1e-5);

    return 0;
}

int MeasUpdate_01() {
    Matrix x(6);
    x(1) = 7101581.92349524; x(2) = 1295292.19517406; x(3) = 12756.8421553549; x(4) = 576.071316476826; x(5) = -3084.40067275274; x(6) = -6736.0684125736;
    Matrix z(1);
    z(1) = 3.196905628244;
    Matrix g(1);
    g(1) = 3.19764645601254;
    Matrix s(1);
    s(1) = 0.00039095375244673;
    Matrix G(6);
    G(1) = 6.80114307990267e-08; G(2) = -3.73341445315677e-07; G(3) = 1.98045516802794e-08; G(4) = 0; G(5) = 0; G(6) = 0;
    Matrix P(6,6);
    P(1,1) = 15805.525623051; P(1,2) = -5466.2904517875; P(1,3) = 8513.26186955627; P(1,4) = 48.4400404376865; P(1,5) = -12.8711251723986; P(1,6) = 22.1680278945983;
    P(2,1) = -5466.2904517875; P(2,2) = 23868.0534547662; P(2,3) = -1474.89681782464; P(2,4) = -4.30145121552882; P(2,5) = 58.1199042738506; P(2,6) = -26.3979271254963;
    P(3,1) = 8513.26186955628; P(3,2) = -1474.89681782464; P(3,3) = 6002.62417854919; P(3,4) = 26.6595677717561; P(3,5) = -3.99275083547992; P(3,6) = 15.3960339617429;
    P(4,1) = 48.4400404376865; P(4,2) = -4.30145121552881; P(4,3) = 26.6595677717561; P(4,4) = 0.178098285646633; P(4,5) = -0.0181106772921105; P(4,6) = 0.0664457241477247;
    P(5,1) = -12.8711251723986; P(5,2) = 58.1199042738506; P(5,3) = -3.9927508354799; P(5,4) = -0.0181106772921107; P(5,5) = 0.149155622683187; P(5,6) = -0.073416295987578;
    P(6,1) = 22.1680278945983; P(6,2) = -26.3979271254963; P(6,3) = 15.3960339617429; P(6,4) = 0.0664457241477248; P(6,5) = -0.0734162959875781; P(6,6) = 0.0817265490462198;
    int n = 6;


    Matrix A(6);
    A(1) = 20976.9551146181; A(2) = -59474.6479131673; A(3) = 7974.21486149458; A(4) = 34.6706648688294; A(5) = -144.683563527389; A(6) = 74.5230337241579;

    Matrix B(6);
    B(1) = 7101566.38318439; B(2) = 1295336.25564476; B(3) = 12750.9346355531; B(4) = 576.045631485538; B(5) = -3084.29348715123; B(6) = -6736.12362130638;

    Matrix C(6,6);
    C(1,1) = 15736.6299495157; C(1,2) = -5270.95486071329; C(1,3) = 8487.07175279262; C(1,4) = 48.3261698213362; C(1,5) = -12.395933634626; C(1,6) = 21.9232681296913;
    C(2,1) = -5270.95486071329; C(2,2) = 23314.2306792217; C(2,3) = -1400.64161897372; C(2,4) = -3.97860098402076; C(2,5) = 56.7726234484914; C(2,6) = -25.7039750832856;
    C(3,1) = 8487.07175279263; C(3,2) = -1400.64161897372; C(3,3) = 5992.66822368445; C(3,4) = 26.6162808048809; C(3,5) = -3.81211072818796; C(3,6) = 15.3029905746473;
    C(4,1) = 48.3261698213362; C(4,2) = -3.97860098402075; C(4,3) = 26.6162808048809; C(4,4) = 0.17791008054459; C(4,5) = -0.0173252817728562; C(4,6) = 0.0660411857513704;
    C(5,1) = -12.3959336346259; C(5,2) = 56.7726234484914; C(5,3) = -3.81211072818794; C(5,4) = -0.0173252817728564; C(5,5) = 0.145878101962599; C(5,6) = -0.0717281236669827;
    C(6,1) = 21.9232681296913; C(6,2) = -25.7039750832856; C(6,3) = 15.3029905746473; C(6,4) = 0.0660411857513705; C(6,5) = -0.0717281236669829; C(6,6) = 0.080857011970185;

    auto [a,b,c] = MeasUpdate(transpose(x), z, g, s, G, P, n);

    _assert(m_equals(transpose(A), a, 1e-9));
    _assert(m_equals(transpose(B), b, 1e-8));
    _assert(m_equals(transpose(C), c, 1e-9));

    return 0;
}

int G_AccelHarmonic_01() {
    Matrix r(3);
    r(1) = 31.2; r(2) = 415; r(3) = 7.2;

    Matrix E(3,3);
    E(1,1) = 1; E(1,2) = 2; E(1,3) = 3;
    E(2,1) = 4; E(2,2) = 5; E(2,3) = 6;
    E(3,1) = 7; E(3,2) = 8; E(3,3) = 9;

    int n_max = 4;
    int m_max = 5;

    Matrix C = G_AccelHarmonic(transpose(r), E, n_max, m_max);

    Matrix R(3,3);
    R(1,1) = -86231822460812; R(1,2) = -102337777399258; R(1,3) = -118443886018676;
    R(2,1) = -102337431986604; R(2,2) = -120944388826618; R(2,3) = -139551517957733;
    R(3,1) = -118443041512400; R(3,2) = -139551000253980; R(3,3) = -160659149896788;

    _assert(m_equals(C, R, 1e3));

    return 0;
}

int GHAMatrix_01() {
    double Mjd_UT1 = 1425.2583;

    Matrix A = GHAMatrix(Mjd_UT1);

    Matrix R(3,3);
    R(1,1) = -0.39962618404794; R(1,2) = 0.916678194909905; R(1,3) = 0;
    R(2,1) = -0.916678194909905; R(2,2) = -0.39962618404794; R(2,3) = 0;
    R(3,1) = 0; R(3,2) = 0; R(3,3) = 1;

    _assert(m_equals(A, R, 1e-8));

    return 0;
}

int Accel_01() {
    double x = 3754.1453;
    Matrix Y(6,1);
    Y(1,1) = 241.25; 
    Y(2,1) = -1925; 
    Y(3,1) = 15.375; 
    Y(4,1) = 0.5; 
    Y(5,1) = -0.25; 
    Y(6,1) = 0.125;

    Matrix A = Accel(x,Y);

    Matrix R(6,1);
    R(1,1) = 0.5; 
    R(2,1) = -0.25; 
    R(3,1) = 0.125;
    R(4,1) = -2.72649962746669e+72;
    R(5,1) = 1.31132822764409e+72;
    R(6,1) = -1.26811480153501e+72;

    _assert(m_equals(A, R, 1e+65));
    
    return 0;
}

int VarEqn_01() {
    double x = 3754.1453;
    Matrix Y(42,1);
    for (int i = 1; i <= 42; i++) {
        Y(i,1) = i;
    }

    Matrix A = VarEqn(x,Y);

    Matrix R(42,1);
    for (int i = 1; i <= 42; i++) {
        R(i,1) = i+3;
    }
    R(4,1) = -9.40171957064303e+131;
    R(5,1) = -1.69984860252462e+132;
    R(6,1) = -4.07130323643034e+132;

    R(10,1) = -8.9210476434981e+133;
    R(11,1) = 3.15765813545868e+134;
    R(12,1) = 2.326251346306e+134;

    R(16,1) = -1.53479928435685e+134;
    R(17,1) = 5.27634766063153e+134;
    R(18,1) = 3.9713120473768e+134;

    R(22,1) = -2.17749380436389e+134;
    R(23,1) = 7.39503718580438e+134;
    R(24,1) = 5.61637274844761e+134;

    R(28,1) = -2.82018832437094e+134;
    R(29,1) = 9.51372671097723e+134;
    R(30,1) = 7.26143344951841e+134;

    R(34,1) = -3.46288284437798e+134;
    R(35,1) = 1.16324162361501e+135;
    R(36,1) = 8.90649415058921e+134;

    R(40,1) = -4.10557736438502e+134;
    R(41,1) = 1.37511057613229e+135;
    R(42,1) = 1.055155485166e+135;

    _assert(m_equals(A, R, 1e+130));
    
    return 0;
}

int DEInteg_01() {
    Matrix Y0(6);
    Y0(1) = 6221397.62857869;
    Y0(2) = 2867713.77965738;
    Y0(3) = 3006155.98509949;
    Y0(4) = 4645.04725161806;
    Y0(5) = -2752.21591588204;
    Y0(6) = -7507.99940987031;

    Matrix Y = DEInteg(Accel, 0, -134.999991953373, 1e-13, 1e-6, 6, transpose(Y0));

    Matrix R(6);
    R(1) = 5542555.89427452;
    R(2) = 3213514.83814162;
    R(3) = 3990892.92789074;
    R(4) = 5394.06894044389;
    R(5) = -2365.2129057402;
    R(6) = -7061.8448137347;

    _assert(m_equals(Y, transpose(R), 1e-6));

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
    _verify(NutAngles_01);
    _verify(TimeUpdate_01);
    _verify(AccelHarmonic_01);
    _verify(EqnEquinox_01);
    _verify(LTC_01);
    _verify(NutMatrix_01);
    _verify(JPL_Eph_DE430_01);
    _verify(PoleMatrix_01);
    _verify(PrecMatrix_01);
    _verify(gmst_01);
    _verify(gast_01);
    _verify(MeasUpdate_01);
    _verify(G_AccelHarmonic_01);
    _verify(GHAMatrix_01);
    _verify(Accel_01);
    _verify(VarEqn_01);
    _verify(DEInteg_01);

    return 0;
}


int main()
{
    eop19620101(21413);
    GGM03S();
    DE430Coeff();

    AuxParam.Mjd_UTC = 49746.1163541665;
    AuxParam.Mjd_TT = 49746.1170623147;
    AuxParam.n = 20;
    AuxParam.m = 20;
    AuxParam.sun = 1;
    AuxParam.moon = 1;
    AuxParam.planets = 1;

    int result = all_tests();

    if (result == 0)
        printf("PASSED\n");

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}

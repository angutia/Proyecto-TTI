#include "..\include\matrix.hpp"
#include "..\include\global.hpp"
#include "..\include\SAT_Const.hpp"
#include "..\include\Position.hpp"
#include "..\include\Mjday.hpp"
#include "..\include\DEInteg.hpp"
#include "..\include\Accel.hpp"
#include "..\include\LTC.hpp"
#include "..\include\IERS.hpp"
#include "..\include\timediff.hpp"
#include "..\include\VarEqn.hpp"
#include "..\include\gmst.hpp"
#include "..\include\R_z.hpp"
#include "..\include\TimeUpdate.hpp"
#include "..\include\AzElPa.hpp"
#include "..\include\MeasUpdate.hpp"
#include <iostream>

using namespace std;

int main() {
	eop19620101(21413); // c = 21413
    GGM03S();
    DE430Coeff();

    int nobs = 46;
    GEOS3(nobs);

	AuxParam.Mjd_UTC = 49746.1112847221;
    AuxParam.Mjd_TT = 49746.1108586111;
    AuxParam.n = 20;
    AuxParam.m = 20;
    AuxParam.sun = 1;
    AuxParam.moon = 1;
    AuxParam.planets = 1;
	
    
    //--------------------------------------------------------------------------
    //
    //  Initial Orbit Determination using Gauss and Extended Kalman Filter methods
    //
    // References:
    //   O. Montenbruck, E. Gill, "Satellite Orbits - Models, Methods, and
    //   Applications", Springer Verlag, Heidelberg, 2000.
    //   
    //   D. Vallado, "Fundamentals of Astrodynamics and Applications", 
    //   4th Edition, 2013.
    //
    //   G. Seeber, "Satellite Geodesy", 2nd Edition, 2003.
    //
    // Last modified:   2020/03/16   Meysam Mahooti
    //--------------------------------------------------------------------------
    
    double sigma_range = 92.5;          // [m]
    double sigma_az = 0.0224*SAT_Const::Rad; // [rad]
    double sigma_el = 0.0139*SAT_Const::Rad; // [rad]

    // Kaena Point station
    double lat = SAT_Const::Rad*21.5748;     // [rad]
    double lon = SAT_Const::Rad*(-158.2706); // [rad]
    double alt = 300.20;                // [m]

    Matrix Rs = transpose(Position(lon, lat, alt));

    double Mjd1 = obs(1,1);
    double Mjd2 = obs(9,1);
    double Mjd3 = obs(18,1);

    Matrix& r2 = zeros(3);
    Matrix& v2 = zeros(3);
    r2(1) = 6221397.62857869; r2(2) =  2867713.77965738; r2(3) =  3006155.98509949;
    v2(1) = 4645.04725161806; v2(2) = -2752.21591588204; v2(3) = -7507.99940987031;
    // [r2,v2] = anglesg(obs(1,2),obs(9,2),obs(18,2),obs(1,3),obs(9,3),obs(18,3),Mjd1,Mjd2,Mjd3,Rs,Rs,Rs);
    // [r2,v2] = anglesdr(obs(1,2),obs(9,2),obs(18,2),obs(1,3),obs(9,3),obs(18,3),Mjd1,Mjd2,Mjd3,Rs,Rs,Rs);

    Matrix Y0_apr(6,1);
    for (int i=1; i<=3; i++) {
        Y0_apr(i,1) = r2(i);
        Y0_apr(i+3,1) = v2(i);
    }

    double Mjd0 = Mjday(1995,1,29,02,38,0);

    double Mjd_UTC = obs(9,1);

    AuxParam.Mjd_UTC = Mjd_UTC;
    AuxParam.n      = 20;
    AuxParam.m      = 20;
    AuxParam.sun     = 1;
    AuxParam.moon    = 1;
    AuxParam.planets = 1;

    int n_eqn  = 6;
    Matrix Y = DEInteg(Accel,0,-(obs(9,1)-Mjd0)*86400.0,1e-13,1e-6,6,Y0_apr);

    Matrix P = zeros(6,6);
    
    for (int i=1; i<=3; i++){
        P(i,i)=1e8;
    }
    for (int i=4; i<=6; i++){
        P(i,i)=1e3;
    }

    Matrix LT = LTC(lon,lat);

    Matrix yPhi = zeros(42,1);
    Matrix Phi  = zeros(6,6);

    // Measurement loop
    double t = 0;

    double Mjd_TT, Mjd_UT1;

    for (int i=1; i<=nobs; i++){
        // Previous step
        double t_old = t;
        Matrix Y_old = Y;
        
        // Time increment and propagation
        Mjd_UTC = obs(i,1);                       // Modified Julian Date
        t       = (Mjd_UTC-Mjd0)*86400.0;         // Time since epoch [s]
        
        auto [x_pole,y_pole,UT1_UTC,LOD,dpsi,deps,dx_pole,dy_pole,TAI_UTC] = IERS(eopdata,Mjd_UTC,'l');
        auto [UT1_TAI,UTC_GPS,UT1_GPS,TT_UTC,GPS_UTC] = timediff(UT1_UTC,TAI_UTC);
        Mjd_TT = Mjd_UTC + TT_UTC/86400;
        Mjd_UT1 = Mjd_TT + (UT1_UTC-TT_UTC)/86400.0;
        AuxParam.Mjd_UTC = Mjd_UTC;
        AuxParam.Mjd_TT = Mjd_TT;
            
        for (int ii=1; ii<=6; ii++){
            yPhi(ii) = Y_old(ii);
            for (int j=1; j<=6; j++){  
                if (ii==j){ 
                    yPhi(6*j+ii) = 1; 
                } else {
                    yPhi(6*j+ii) = 0;
                }
            }
        }

        yPhi = DEInteg (VarEqn,0,t-t_old,1e-13,1e-6,42,yPhi);

        // Extract state transition matrices
        for (int j=1; j<=6; j++){
            Phi.assign_column(j,yPhi.extract_vector(6*j+1,6*j+6));
        }

        Y = DEInteg (Accel,0,t-t_old,1e-13,1e-6,6,Y_old);

        // Topocentric coordinates
        double theta = gmst(Mjd_UT1);                    // Earth rotation
        Matrix U = R_z(theta);
        Matrix r = Y.extract_vector(1,3);
        Matrix s = LT*(U*r-Rs);                          // Topocentric position [m]
        
        // Time update
        P = TimeUpdate(P, Phi);
            
        // Azimuth and partials
        auto [Azim, Elev, dAds, dEds] = AzElPa(s);       // Azimuth, Elevation
        Matrix dAdY = union_vector(dAds*LT*U,zeros(1,3));
        
        // Measurement update
        Matrix auxM1(1); auxM1(1) = obs(i,2);
        Matrix auxM2(1); auxM2(1) = Azim;
        Matrix auxM3(1); auxM3(1) = sigma_az;
        Matrix K;
        tie(K, Y, P) = MeasUpdate ( Y, auxM1, auxM2, auxM3, dAdY, P, 6 );

        // Elevation and partials
        r = Y.extract_vector(1,3);
        s = LT*(U*r-Rs);                               // Topocentric position [m]
        tie(Azim, Elev, dAds, dEds) = AzElPa(s);     // Azimuth, Elevation
        Matrix dEdY = union_vector(dEds*LT*U,zeros(1,3));

        // Measurement update
        auxM1(1) = obs(i,3);
        auxM2(1) = Elev;
        auxM3(1) = sigma_el;
        tie(K, Y, P) = MeasUpdate ( Y, auxM1, auxM2, auxM3, dEdY, P, 6 );

        // Range and partials
        r = Y.extract_vector(1,3);
        s = LT*(U*r-Rs);                                                // Topocentric position [m]
        double Dist = norm(s); Matrix dDds = transpose(s/Dist);         // Range
        Matrix dDdY = union_vector(dDds*LT*U,zeros(1,3));
        
        // Measurement update
        auxM1(1) = obs(i,4);
        auxM2(1) = Dist;
        auxM3(1) = sigma_range;
        tie(K, Y, P) = MeasUpdate ( Y, auxM1, auxM2, auxM3, dDdY, P, 6 );
    }

    auto [x_pole,y_pole,UT1_UTC,LOD,dpsi,deps,dx_pole,dy_pole,TAI_UTC] = IERS(eopdata,obs(46,1),'l');
    auto [UT1_TAI,UTC_GPS,UT1_GPS,TT_UTC,GPS_UTC] = timediff(UT1_UTC,TAI_UTC);
    Mjd_TT = Mjd_UTC + TT_UTC/86400;
    AuxParam.Mjd_UTC = Mjd_UTC;
    AuxParam.Mjd_TT = Mjd_TT;

    Matrix Y0 = DEInteg (Accel,0,-(obs(46,1)-obs(1,1))*86400.0,1e-13,1e-6,6,Y);

    Matrix Y_true(6,1);
    Y_true(1,1) = 5753.173e3;
    Y_true(2,1) = 2673.361e3;
    Y_true(3,1) = 3440.304e3;
    Y_true(4,1) = 4.324207e3;
    Y_true(5,1) = -1.924299e3;
    Y_true(6,1) = -5.728216e3;

    printf("\nError of Position Estimation\n");
    printf("dX%10.1f [m]\n",Y0(1)-Y_true(1));
    printf("dY%10.1f [m]\n",Y0(2)-Y_true(2));
    printf("dZ%10.1f [m]\n",Y0(3)-Y_true(3));
    printf("\nError of Velocity Estimation\n");
    printf("dVx%8.1f [m/s]\n",Y0(4)-Y_true(4));
    printf("dVy%8.1f [m/s]\n",Y0(5)-Y_true(5));
    printf("dVz%8.1f [m/s]\n",Y0(6)-Y_true(6));

    return 0;
}
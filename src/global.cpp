#include "..\include\global.hpp"
#include "..\include\Mjday.hpp"
#include "..\include\SAT_Const.hpp"
#include <cstring>

Param AuxParam;
Matrix eopdata;
Matrix Cnm;
Matrix Snm;
Matrix PC;
Matrix obs;
double eps = 2.2204e-16;

void eop19620101(int c){
	eopdata = zeros(13,c);
	
	FILE *fid = fopen("..\\data\\eop19620101.txt", "r");
	if (fid == NULL) {
		printf("Fail open eop19620101.txt file\n");
		exit(EXIT_FAILURE);
	}
	
	for (int j = 1; j <= c; j++) {
		fscanf(fid,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
		&(eopdata(1,j)), &(eopdata(2,j)), &(eopdata(3,j)), 
		&(eopdata(4,j)), &(eopdata(5,j)), &(eopdata(6,j)), 
		&(eopdata(7,j)), &(eopdata(8,j)), &(eopdata(9,j)), 
		&(eopdata(10,j)), &(eopdata(11,j)), &(eopdata(12,j)), &(eopdata(13,j)));
	}
	
	fclose(fid);
}

void GGM03S(){
    Cnm = zeros(181,181);
    Snm = zeros(181,181);
    FILE *fid = fopen("..\\data\\GGM03S.txt","r");
    if (fid == NULL) {
		printf("Fail open GGM03S.txt file\n");
		exit(EXIT_FAILURE);
	}

    Matrix temp = zeros(6);
    for (int n = 0; n <= 180; n++){
        for (int m = 0; m <= n; m++){
            fscanf(fid,"%lf %lf %lf %lf %lf %lf", &(temp(1)), &(temp(2)), &(temp(3)), &(temp(4)), &(temp(5)), &(temp(6)));        
            Cnm(n+1,m+1) = temp(3);
            Snm(n+1,m+1) = temp(4);
        }
    }
	
	fclose(fid);
}

void DE430Coeff(){
    PC = zeros(2285,1020);
    FILE *fid = fopen("..\\data\\DE430Coeff.txt","r");
    if (fid == NULL) {
		printf("Fail open DE430Coeff.txt file\n");
		exit(EXIT_FAILURE);
	}

    for (int n = 1; n <= 2285; n++){
        for (int m = 1; m <= 1020; m++){
            fscanf(fid,"%lf", &(PC(n,m)));
        }
    }
	
	fclose(fid);    
}

void GEOS3(int f){
    obs = zeros(f,4);
    FILE *fid = fopen("..\\data\\GEOS3.txt","r");
    if (fid == NULL) {
		printf("Fail open GEOS3.txt file\n");
		exit(EXIT_FAILURE);
	}

    int Y, MO, D, H, MI, S;
    double AZ, EL, DIST;
    char line[55], y[5], mo[3], d[3], h[3], mi[3], s[7], az[9], el[8], dist[11];
    for(int i=1; i<=f; i++) {
        fgets(line,sizeof(line)+2,fid);

        strncpy(y,&(line[0]),4);
        y[4] = '\0';
        Y = atoi(y);
        strncpy(mo,&(line[5]),2);
        mo[2] = '\0';
        MO = atoi(mo);
        strncpy(d,&(line[8]),2);
        d[2] = '\0';
        D = atoi(d);
        strncpy(h,&(line[12]),2);
        h[2] = '\0';
        H = atoi(h);
        strncpy(mi,&(line[15]),2);
        mi[2] = '\0';
        MI = atoi(mi);
        strncpy(s,&(line[18]),6);
        s[6] = '\0';
        S = atoi(s);

        strncpy(az,&(line[25]),8);
        az[8] = '\0';
        AZ = atof(az);
        strncpy(el,&(line[35]),7);
        el[7] = '\0';
        EL = atof(el);
        strncpy(dist,&(line[44]),10);
        dist[10] = '\0';
        DIST = atof(dist);

        obs(i,1) = Mjday(Y,MO,D,H,MI,S);
        obs(i,2) = (SAT_Const::Rad)*AZ;
        obs(i,3) = (SAT_Const::Rad)*EL;
        obs(i,4) = 1e3*DIST;

    }

}

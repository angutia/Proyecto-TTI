#include "..\include\global.hpp"

Matrix eopdata;
Matrix Cnm;
Matrix Snm;
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



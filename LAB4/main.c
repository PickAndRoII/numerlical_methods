#include <math.h>
#include <stdio.h>
#include "/opt/NR/numerical_recipes.c/nrutil.h"
#include "/opt/NR/numerical_recipes.c/nrutil.c"
#include "/opt/NR/numerical_recipes.c/tred2.c"
#include "/opt/NR/numerical_recipes.c/tqli.c"
#include "/opt/NR/numerical_recipes.c/pythag.c"

int main(){
    int nx = 20;
    int ny = 20;
    int n = nx*ny;
    int m = 10;
    float t= -0.021;
    float **H;
    float **Y;
    float **X;
    Y = matrix(1, n, 1, n);
	X = matrix(1, n, 1, n);
    H = matrix(1, n, 1, n);

    int i, j, k, l;

    for(int i=1; i<=n; ++i){

		for(int j=1; j<=n; ++j){
            if(i==j)
                Y[i][j] = 1.0;
			else
                Y[i][j] = 0.0;
            }
	}
	

    float *d = vector(1, n);
    float *e = vector(1, n);

    
	
    for(i=1;i<=nx;i++){
        for(j=1;j<=ny;j++){
            l=j+(i-1)*ny;
            for(k=1;k<=n;k++)H[l][k]=0.;
            if(i>1)
                H[l][l-ny]=t;   //dla i=1 nie ma sasiada z lewej strony
            if(i<nx) 
                H[l][l+ny]=t;   //dla i=nx nie ma sasiada z prawej strony
            H[l][l]=-4*t;
            if(j>1)
                H[l][l-1]=t;    //dla j=1 nie ma sasiada ponizej siatki
            if(j<ny)  
                H[l][l+1]=t;    //dla j=ny nie ma sasiada powyzej siatki
            }
        }
    

    tred2(H,n,d,e);
    tqli(d,e,n,Y);

    double val = 0.0;
    for(int i = 1; i <=n; ++i){
        for(int j = 1; j <=n; ++j){
            for(int k = 1; k <=n; ++k){
                val = val +(H[i][k] * Y[k][j]);
            }
        X[i][j] = val;
        val = 0.0;
        }
    }

    float e1, e2, l1, l2;

    int indx[n+1];

    for(l=1;l<=n;l++) 
        indx[l]=l; // inicjalizacja
    for(l=1;l<=n-1;l++){
        for(k=n;k>=l+1;k--){
        e1=d[k-1];
        e2=d[k];
        l1=indx[k-1];
        l2=indx[k];
        if(e2<e1){  //wymieniamy energie i indeksy wektorów miejscami
            d[k]=e1;
            d[k-1]=e2;
            indx[k]=l1;
            indx[k-1]=l2;
            }
        }
    }

    FILE *fp;
    fp=fopen("dane.dat","w");
    for(i=1;i<=nx;i++){
        for(j=1;j<=ny;j++){
            l=j+(i-1)*ny;
            fprintf(fp,"%6d  %6d ",i,j);
            for(k=1;k<=m;k++)
                 fprintf(fp," %12.6f  ",X[l][indx[k]]);
            fprintf(fp,"\n");
        }
        fprintf(fp,"\n");
    }
fclose(fp);

for(int i=i; i<=10;++i){
printf("wartosc wlasna: %f ",d[i]);

}

free_matrix(Y,1, n, 1, n);
free_matrix(H,1, n, 1, n);
free_matrix(X,1, n, 1, n);
free_vector(d,1,n);
free_vector(d,1,n);

return 0;
}

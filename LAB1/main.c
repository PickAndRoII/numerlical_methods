#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "/opt/NR/numerical_recipes.c/nrutil.h"
#include "/opt/NR/numerical_recipes.c/nrutil.c"
#include "/opt/NR/numerical_recipes.c/gaussj.c"

#define N 400 // rozmiar macierzy A: NxN

double omega = 1;
double v0 = 0;
double h = 0.1;
double a1 = 1;

int main(void) {
    FILE *fp;
	float **A,**b;
//	Alokacja macierzy
	A = matrix(1, N, 1, N);
	b = matrix(1, N, 1, 1);
	
// 	Wypelnienie macierzy A i wektora b
	for(int i=1; i<=N; ++i){
		b[i][1] = 0.0;
		for(int j=1; j<=N; ++j)
            if(i == j)
                A[i][j] = 1.0;
            else
			    A[i][j] = 0.0;
	}
	
    

    b[1][1] = a1;
	b[2][1] = v0 * h;
    float x = omega * omega * h * h - 2;
	
	// A[1][1] = 2.0; A[1][2] = 3.0; A[1][3] = 0.0;
	// A[2][1] = -1.0; A[2][2] = 1.0; A[2][3] = 4.0;
	// A[3][1] = 3.0; A[3][2] = 11.0; A[3][3] = 1.0;

    for(int i = 1; i<=N; ++i){
        for(int j = 1; j<=N; ++j){
            if(i-2 == j){
                A[i][j] = 1.0;
            }
        }
    }

     for(int i = 1; i<=N; ++i){
        for(int j = 1; j<=N; ++j){
            if(i-1 == j){
                A[i][j] = x;
            }
        }
    }
    
    A[2][1] = -1.0;

    // for(int i = 1; i<=N; ++i){
    //     for(int j = 1; j<=N; ++j){
    //         printf("%lf ", A[i][j]);
    //     }
    //     printf("\n");
    // }

    // for(int i=1; i<=N; i++){
    //     printf("%lf \n", b[i][1]);
    // }
	
//	Rozwiazanie ukladu rownan Ax=b - wywolanie procedury:
	gaussj(A,N,b,1);
    
    fp = fopen("out.dat", "w");
    //fprintf(fp, "%g\n", b);
    


//	Wypisanie rozwiazania, ktore procedura gaussj(A,N,b,1); zapisala w wektorze b.
	
    for(int i=1; i<=N; ++i){
      printf("%d %g\n", i, b[i][1]); 
        fprintf(fp, "%d %g\n", i, b[i][1]);
    }
    fclose(fp);
    
//	Zwolnienie pamieci
	free_matrix(A,1,N,1,N);
	free_matrix(b,1,N,1,1);    
	
	return 0;
}

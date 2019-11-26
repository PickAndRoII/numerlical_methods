#define N 2000
#include <math.h>
#include <stdio.h>
#include "/opt/NR/numerical_recipes.c/nrutil.h"
#include "/opt/NR/numerical_recipes.c/nrutil.c"

void Jakobi(float beta, float f0, float ome, char* nazwapliku );
void saveToFile(float *v, float n, const char * nazwapliku);

int main(){
    Jakobi(0.0, 0.0, 0.8, "A.dat");
	Jakobi(0.4, 0.0, 0.8, "B.dat");
	Jakobi(0.4, 0.1, 0.8, "C.dat");
}

void Jakobi(float beta, float f0, float ome, char* nazwapliku ){
    float omega = 1;
    float v0 = 0;
    float x0 = 1;
    float n = 2000;
    float h = 0.02;

    float a1 = 1;
    float a2 = omega*omega*h*h - 2 - beta*h;
    float a3 = 1 + beta*h;

    float *b = vector(0, N);
    b[0] = 1;
    b[1] = 0;

    for(int i = 2; i <= N; i++){
        b[i] = f0* sin(ome * h * i) * h * h;
    }
    float *d0 = vector(0, N);
    d0[0] = 1;
    d0[1] = 1;
    for(int i = 2; i <= N; i++){
        d0[i] = a3;
    }
    float *d1 = vector(0, N);
    d1[0] = 0;
    d1[1] = -1;
     for(int i = 2; i <= N; i++){
        d1[i] = a2;
    }
    float *d2 = vector(0, N);
    d2[0] = 0;
    d2[1] = 0;
     for(int i = 2; i <= N; i++){
        d2[i] = a1;
    }

    float *xn = vector(0, N);
	float *xs = vector(0, N);
    
     for(int i = 0; i <= N; i++){
        xs[i] = 0;
    }

     for(int i = 0; i <= N; i++){
        xn[i] = 0;
    }
   
    int it = 0;
    while(it < 10000){
       
        it++;
        float sumxs = 0;
        float sumxn = 0;

        for(int i = 0; i <= N; i++){
            sumxs = sumxs + fabs(xs[i]*xs[i]);
           
            if(i == 0){
                xn[i] = 1/d0[i] * b[i] ;
             
            }
            else if(i == 1){
                xn[i] = 1/d0[i] * (b[i] - d1[i] * xn[i-1]);
             
            }
            else{
                xn[i] = 1/d0[i] * (b[i] - d1[i] * xn[i-1] - d2[i] * xn[i-2]);
            }
            
            sumxn = sumxn + fabs(xn[i]*xn[i]);
        }
        //printf("sumxn = %f, sumxs =%f\n", sumxn, sumxs);
        for(int i=0; i <= N; i++)
            xs[i] = xn[i];

        if(fabs(sumxn - sumxs) < 0.00001)
            break;
    }
    printf("Petla zatrzymala sie po %i obiegach\n", it);
    saveToFile(xn, h, nazwapliku);
    free_vector(d0, 0, N);
	free_vector(d1, 0, N);
	free_vector(d2, 0, N);
	free_vector(b, 0, N);

	free_vector(xn, 0, N);
	free_vector(xs, 0, N);
}

void saveToFile(float * v, float h, const char * nazwapliku)
{
	FILE * file = fopen(nazwapliku, "w");

	float t0 = 0.0;

	for(int i = 1; i <= N; ++i)
	{
		fprintf(file, "%f\t%f\n", t0, v[i]);
		t0 += h;
	}

	fclose(file);
}

#include <math.h>
#include <iostream>
#include </usr/include/gsl/gsl_linalg.h>


void wyznacz_M(double *xw, double *yw, double *m, int n, double alfa, double beta);
double wyznacz_Sx(double *xw, double *yw, double *m, int n, double x);
double fun1(double x);
double fun2(double x);

    double lambda = 0.5;
    double mi = 0.5;
    int n =5;
    double h = 10.0/((double)n-1.0);

int main(){
   
   FILE *fp;
   fp = fopen("dane.dat", "w");
    
    double alfa = 0.0;
    double beta = 0.0;
    
    
    double xw[n];
    double yw[n];
    double m[n];

    xw[0] = -5.0;
    for(int i =1; i<n; ++i){
        xw[i]=xw[i-1]+h;
    }
    
    for(int i=0; i<n; ++i){
        yw[i]=fun1(xw[i]);
    }
    wyznacz_M(xw, yw, m, n,  alfa,  beta);

    for(double x =-5.0; x<= 5.0; x+=0.01){
        fprintf(fp, "%g %g\n", x, wyznacz_Sx(xw, yw, m, n, x));
    }
    fclose(fp);
    return 0;
}

void wyznacz_M(double *xw, double *yw, double *m, int n, double alfa, double beta){
    gsl_matrix *A = gsl_matrix_calloc(n,n);
    gsl_vector *d = gsl_vector_calloc(n);
    
    for(int i = 0; i<n; ++i){
        for(int j = 0; j<n; ++j){
            if(i == j){
                gsl_matrix_set(A, i, j, 2);
            }
            if(i==j+1){
                gsl_matrix_set(A, i, j, 0.5);
            }
            if(i+1==j){
                gsl_matrix_set(A, i, j, 0.5);
            }
        }
    }
    gsl_matrix_set(A, 0, 0, 1);
    gsl_matrix_set(A, n-1, n-1, 1);
    gsl_matrix_set(A, 0, 1, 0);
    gsl_matrix_set(A, n-1, n-2, 0);

    
    gsl_vector_set(d, 0, alfa);
    gsl_vector_set(d, n-1, beta);
    for(int i = 1; i<n-1; ++i){
        double di = (6/1.0)*((yw[i+1]-yw[i])/0.5 - (yw[i]-yw[i-1])/0.5);
        gsl_vector_set(d, i, di);
    }
    // for(int i = 0; i < n; ++i){
    //    for(int j = 0; j < n; ++j){
    //        printf("%f ", gsl_matrix_get(A, i, j));
    //    }
    //    printf("\n");
    // }
    // printf("\n");

    gsl_linalg_HH_svx(A,d);
   
    for(int i = 0; i < n; ++i){
        m[i] = gsl_vector_get(d, i);
    }

     for(int i = 0; i < n; ++i){
       std::cout<<m[i]<<" ";
    }
}
double wyznacz_Sx(double *xw, double *yw, double *m, int n, double x){

    int i = 1;
    
    for(i; i < n; ++i){
        if(x<xw[i]) {
            break;
        }
    }
    double sx;
    sx = (m[i-1]* pow((xw[i] - x),3)/6*h + m[i]*pow((x-xw[i-1]),3)/6.0*h + (yw[i]-yw[i-1])/h - (h/6.0)*(m[i]-m[i-1])+ yw[i-1]-m[i-1]*h*h/6.0);
   
    return sx;
}
double fun1(double x){
    return 1.0/(1.0+(x*x));
}

double fun2(double x){
    return cos(2*x);
}


#include <iostream>
#include <math.h>
#include "/usr/include/gsl/gsl_errno.h"
#include "/usr/include/gsl/gsl_fft_complex.h"
#include <time.h>

double szum(){
    return 2*(rand()/(RAND_MAX + 1.0))-1;
}
double fun(int i, double omega);
double aproksymacja(int k, const char* name1, const char* name2);

int main(){
    srand(time(NULL));

    aproksymacja(8,"aproksymacja8.1.dat", "aproksymacja8.2.dat");
    aproksymacja(10,"aproksymacja10.1.dat","aproksymacja10.2.dat");
    aproksymacja(12,"aproksymacja12.1.dat","aproksymacja12.2.dat");

    return 0;
}


double aproksymacja(int k, const char* name1, const char* name2){
    int N = pow(2,k);
    double y[2*N];
    double kopia[2*N];
    double omega = 2*(2*M_PI/N);
    size_t stride = 1;

    for(int i =0; i<N; ++i){
        y[2*i] = fun(i, omega) + szum();
        y[2*i+1] = 0;
        kopia[2*i] = y[2*i];
        kopia[2*i+1] = y[2*i+1];
    }
    gsl_fft_complex_radix2_forward(y,stride ,N);
    if(k==8){
    FILE *fp;
        fp = fopen("dane.dat", "w");
        for(int i =0; i<N; ++i){
            fprintf(fp,"%d %g %g %g \n", i, y[2*i], y[2*i+1], sqrt(pow(y[2*i],2)+pow(y[2*i+1],2)));
        }
    fclose(fp);
    }
    double max = sqrt(pow(y[0],2)+pow(y[1],2));
    for(int i =1; i<N; ++i){
        if(max<sqrt(pow(y[2*i],2)+pow(y[2*i+1],2)))
            max = sqrt(pow(y[2*i],2)+pow(y[2*i+1],2));
    }

    for(int i =0; i<N; ++i){
        if(sqrt(pow(y[2*i],2)+pow(y[2*i+1],2)) < 0.5*max){
            y[2*i] = 0;
            y[2*i+1] = 0;
        }
    }

    gsl_fft_complex_radix2_backward(y,stride ,N);
    
    for(int i =0; i<N; ++i){
        y[2*i] /= N;
    }

    FILE *fp2 = fopen(name1,"w");
    FILE *fp3 = fopen(name2,"w");

    for(int i =0; i<N; ++i){
        fprintf(fp2, "%d %g %g\n", i, kopia[2*i], y[2*i]);
        fprintf(fp3, "%d %g %g\n", i, fun(i,omega), y[2*i]);
    }

    fclose(fp2);
    fclose(fp3);
}
double fun(int i, double omega){
    return sin(omega*i)+sin(2*omega*i)+sin(3*omega*i);
}

//plot "wynik.dat" i 0 u 1:(sqrt($2**2+$3**2))
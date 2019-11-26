#include <iostream>
#include <math.h>
#include <time.h>

#define xmin 0
#define xmax 2*M_PI

#define n 100

double f1(double x, double alfa);
double f2(double x, double alfa);
double f3(double x, double alfa);
double szum();
double aprox(double arg, double *a, double *b, int MS, int MC);
void fullApp(int MS, int MC, double alfa, double (*fun)(double arg, double alfa), const char* name);


int main(){
	srand(time(NULL));

    fullApp(5,5, 0, f1,"dane1.dat");
    fullApp(5,5, 0,f2,"dane2.dat");
    fullApp(5,0, 0,f3,"dane3a.dat");
    fullApp(5,5,0,f3,"dane3b.dat");
    fullApp(10,10,0,f3,"dane3c.dat");
    fullApp(5,5,szum(),f1,"dane4b.dat");
    fullApp(30,30,szum(),f1,"dane4c.dat");
}

double szum(){
    return (rand()/(RAND_MAX+1.0)-0.5);
}

double f1(double x, double alfa){
    return (2*sin(x)+sin(2*x)+2*sin(3*x)+alfa);
}

double f2(double x, double alfa){
    return (2*sin(x)+sin(2*x)+2*cos(x)+cos(2*x));
}
double f3(double x, double alfa){
    return (2*sin(1.1*x)+sin(2.1*x)+2*sin(3.1*x));
}

double aprox(double arg, double *a, double *b, int MS, int MC){
    double sum1 = 0;
    double sum2 = 0;

    for(int k = 0; k <= MS; ++k){
        sum1 = sum1 + a[k]*sin(k*arg);
    }

    for(int j = 0; j <= MC; ++j){
        sum2 = sum2 + b[j]*cos(j*arg);
    }

    return (sum1 + sum2);
}

void fullApp(int MS, int MC, double alfa, double (*fun)(double arg, double alfa), const char* name){
    FILE *fp;
    fp = fopen(name, "w");

    // int MC = 5;
    // int MS = 5;

    double args[n];
    double val[n];

    args[0] = xmin;
    args[n-1] = xmax;

    double krok = ((xmax - xmin)/(n-1.0));

    for(int i = 1; i < n-1; ++i){
        args[i] = args[i-1] + krok; 
    }

    for(int i = 0; i < n; ++i){
        val[i] = fun(args[i], szum());
    }

    double a[MS+1];
    double b[MC+1];

    for(int k = 0; k < MS+1; ++k){
        double sum = 0;
        for(int i = 0; i < n; ++i){
            sum = (sum + (val[i]*sin(k*args[i])));
        }
        a[k] = ((2.0/n)*sum);
    }

    for(int j = 0; j < MC+1; ++j){
        double sum = 0;
        for(int i = 0; i < n; ++i){
            sum = (sum + (val[i]*cos(j*args[i])));
        }
        b[j] = ((2.0/n)*sum);
    }

    for(double x = xmin; x < xmax; x=x+0.01){
        fprintf(fp, "%g %g %g\n",x, fun(x, szum()), aprox(x, a, b, MS, MC));
    }
    
    if(MS == 30 and MC == 30 and alfa){
	FILE *fp2;
	fp2=fopen("name.dat", "w");
        for(int i = 0; i<30; ++i){
            std::cout<<a[i]<<" "<<b[i]<<std::endl;
            fprintf(fp2, "%d %g %g\n",i, a[i], b[i]);
        }
		fclose(fp2);
    }

    fclose(fp);
}

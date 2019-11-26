#include <iostream>
#include <math.h>

#define r ((sqrt(5.0)-1.0)/2.0)
#define epsilon 1e-6


double f1(double x);
double f2(double x);
double zlotyPodzial(double xa, double xb, double (*fun)(double arg), const char* name,double xdok);
double rownyPodzial(double xa, double xb, double (*fun)(double arg), const char* name,double xdok);

int main(){
    std::cout<<zlotyPodzial(-0.5, 1.0, f1, "dane1.dat", -0.1673198)<<std::endl;
    std::cout<<rownyPodzial(-0.5, 1.0, f1, "dane2.dat", -0.1673198)<<std::endl;
    std::cout<<zlotyPodzial(-4.0, 1.0, f2, "dane3.dat", 0)<<std::endl;
    std::cout<<rownyPodzial(-4.0, 1.0, f2, "dane4.dat", 0)<<std::endl;
}

double f1(double x){
    return log(pow(x,5)+3*pow(x,2)+x+9);
}

double f2(double x){
    return pow(x,6);
}

double zlotyPodzial(double xa, double xb, double (*fun)(double arg),const char* name, double xdok){
    double x1;
    double x2;
    double xmin;
    int it = 0;

    FILE *fp;
    fp = fopen(name, "w");

    while(true){
        x1 = xa + pow(r,2)*(xb-xa);
        x2 = xa + r * (xb-xa);
        it++;
        if(fun(x1)>fun(x2)){
            xa = x1;
        }
        else{
            xb = x2;
        }
        xmin = (x1+x2)/2.0;
        fprintf(fp, "%d %g %g\n", it, xmin, fabs(xdok-xmin));
        if(fabs(x1-x2)<epsilon)
            break;
    }

    
    fclose(fp);
    return xmin;
}

double rownyPodzial(double xa, double xb, double (*fun)(double arg), const char* name, double xdok){
    double x1;
    double x2;
    double xmin;
    int it = 0;

    FILE *fp;
    fp = fopen(name, "w");

    while(true){
        x1 = xa + (1.0/3.0)*(xb-xa);
        x2 = xa + (2.0/3.0)*(xb-xa);
        it++;
        if(fun(x1)>fun(x2)){
            xa = x1;
        }
        else{
            xb = x2;
        }
        xmin = (x1+x2)/2.0;
        fprintf(fp, "%d %g %g\n", it, xmin, fabs(xdok-xmin));
        if(fabs(x1-x2)<epsilon)
            break;
    }

    
    fclose(fp);
    return xmin;
}

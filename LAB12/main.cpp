#include <iostream>
#include <math.h>
#define n 8

double fun(double x);
void Milne(double **D, int a, int b);
void Simpson(double **D, int a, int b);

int main(){
    int a = 0;
    int b = 1;

    double **D1;
    D1 = new double* [n+1];
    for(int i = 0; i <= n ; ++i){
        D1[i] = new double[i+1];
    }
    double **D2;
    D2 = new double* [n+1];
    for(int i = 0; i <= n ; ++i){
        D2[i] = new double[i+1];
    }

    Simpson(D1,a,b);
    std::cout<<std::endl<<std::endl;
    Milne(D2,a,b);

    for(int i = 0; i<=n; ++i){
            delete[] D1[i];  
    }
    delete[] D1;

    for(int i = 0; i<=n; ++i){
            delete[] D2[i];  
    }
    delete[] D2;

    return 0;
}

void Milne(double **D, int a, int b){
    int N = 0;
    double h = 0;
    double suma = 0;

    for(int i = 0;i <= n; ++i){
        N = pow(2,i+2);
        h = (b-a)/static_cast<double>(N);

        suma = 0;

        for(int j= 0; j <= (N/4)-1.0; ++j){
            suma = suma + ((4*h)/90.0)*(7*fun(a+4*j*h)+32*fun(a+(4*j+1)*h)+12*fun(a+(4*j+2)*h)+32*fun(a+(4*j+3)*h)+7*fun(a+(4*j+4)*h));
        }
        D[i][0] = suma;
        
        for(int k = 1; k <= i; ++k ){
            D[i][k] = (pow(4,k)*D[i][k-1]-D[i-1][k-1])/(pow(4,k)-1.0);
        }
    }

    std::cout<<"Milne"<<std::endl;
    for(int w = 0; w<=n; ++w){
        for(int k = 0; k<=w; ++k){
            std::cout<<D[w][k]<<" ";
        }
        std::cout<<std::endl;
    }
}

void Simpson(double **D, int a, int b){
    int N = 0;
    double h = 0;
    double suma = 0;

    for(int i = 0;i <= n; ++i){
        N = pow(2,i+1);
        h = (b-a)/static_cast<double>(N);

        suma = 0;
        
        for(int j= 0; j <= (N/2)-1.0; ++j){
            suma = suma + (h/3.0)*(fun(a+2*j*h)+4*fun(a+(2*j+1)*h)+fun(a+(2*j+2)*h));
        }
        D[i][0] = suma;

        for(int k = 1; k <= i; ++k ){
            D[i][k] = (pow(4,k)*D[i][k-1]-D[i-1][k-1])/(pow(4,k)-1.0);
            }

        }
        std::cout<<"Simpson"<<std::endl;
        for(int w = 0; w<=n; ++w){
            for(int k = 0; k<=w; ++k){
                std::cout<<D[w][k]<<" ";
                }
            std::cout<<std::endl;
        }
    }


double fun(double x){
    return (log(pow(x,3)+3*pow(x,2)+x+0.1)*sin(18*x));
}

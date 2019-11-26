#include <iostream>
#include <cmath>
#define N 9

double fun(double x);
void ilorazyRoznicowe(double *x, double *f);
double wielomananInter(double val, double *x, double *f);

int main(){
    using namespace std;
    

    FILE *fp2;
    fp2 = fopen("dane.dat", "w");
    if(!fp2)
        exit(-1);
    double roz = 10.0/6.0;

    double x[10];
    x[0] = -5;
    for(int i =1; i<10; ++i){
        x[i]=x[i-1]+1.0;
    }
    cout<<"elo"<<endl;
    double f2[10] = {0,0,0,0,0,0,0,0,0,0};
    ilorazyRoznicowe(x,f2);
    cout<<"elo2"<<endl;
    for(double i = -5; i<=5; i=i+0.01){
        //cout<<i<<" "<<wielomananInter(i, x, f2)<<endl;
        fprintf(fp2, "%f, %f %f",i, fun(i), wielomananInter(i, x, f2));
        fprintf(fp2,"\n");
    }
    fclose(fp2);
    cout<<endl<<endl;
    cout<<"elo3"<<endl;
for(int i = 0; i<10; ++i){
cout<<f2[i]<<endl;
}
}

double fun(double x){
    return ((1.0)/(1.0 + pow(x,2)));
}

void ilorazyRoznicowe(double *x, double *f){
        for(int j=0; j<=N; ++j){
            for(int k=0; k<=j; ++k){
                double iloczyn = 1;
                for(int l = 0; l<=j; ++l){
                    if(l!=k){
                    iloczyn = iloczyn * 1/(x[k] - x[l]);
                    }
                }
                f[j] += fun(x[k])*iloczyn;
            }
        }
}

double wielomananInter(double val, double*x, double *f){
    double ret = 0.0;
        for(int j = 0; j<=N; ++j){
            double iloczyn = 1;
            for(int i = 0; i<=j-1; ++i){
                iloczyn = iloczyn * (val - x[i]);
            }
            ret += f[j]*iloczyn;
        }
return ret;
}

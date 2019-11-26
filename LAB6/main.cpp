#include <iostream>
#include <cmath>
#define N 5
#define IT_MAX 30

double licz_r(double *a, double *b, int n, double x0){
    b[n]=0;
    for(int k= n-1; k>=0; --k){
        b[k] = a[k+1]+x0*b[k+1];
    }
    return a[0]+x0*b[0];
}

int main(){
    double a[N+1]= {240, -196, -92, 33, 14, 1};
    double b[N+1];
    double c[N];
    double Rj;
    double Rjj;
    double x0;
    double x1;
    int n;

    FILE *fp;
    fp = fopen("dane.txt", "w");
    if(!fp)
        exit(-1);

    fprintf(fp,"L, it, x0, Rj, Rjj");
    fprintf(fp,"\n");
    for(int L=1; L<=N; L++){
        n = N-L+1;
        x0 = 0;
        for(int it=1; it<=IT_MAX; it++){
            Rj = licz_r(a,b,n,x0);
            Rjj = licz_r(b,c,n-1, x0);
            x1 = x0 - Rj/Rjj;
            fprintf(fp,"%d, %d, %f, %f, %f",L,it,x0,Rj,Rjj);
            fprintf(fp,"\n");
            if(fabs(x1-x0)<1.0E-7)
                break;
            x0=x1;
            
        }
        fprintf(fp,"\n");
    for(int i=0; i<=(n-1);++i)
        a[i]=b[i];
    }
  
    fclose(fp);
}

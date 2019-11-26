#include <iostream>
#include <math.h>
#include "/opt/NR/numerical_recipes.c/gauleg.c"
#include "/opt/NR/numerical_recipes.c/gaulag.c"
#include "/opt/NR/numerical_recipes.c/gauher.c"
#include "/opt/NR/numerical_recipes.c/gammln.c"
#include "/opt/NR/numerical_recipes.c/nrutil.c"


float fun1(float x);
float fun2(float x);
float fun3(float x);
float fun4(float x);

void c1(float a, float b, int n);
void c2a(int n);
void c2b(float a, float b, int n);
void c3(int n, float alfa);



int main(){

    for(int n=2; n<=100; ++n){
        if(n==2){
            std::cout<<"------------ZAD1------------"<<std::endl;
        }
        c1(1,2,n);
        
    }

 

    for(int n=2; n<=100; n=n+2){
        if(n==2){
            std::cout<<"------------ZAD2A------------"<<std::endl;
        }
        c2a(n);
    }

       for(int n=2; n<=100; ++n){ 
        if(n==2){
            std::cout<<"------------ZAD2B------------"<<std::endl;
        }
        c2b(0,5, n);
    }

    for(int n=2; n<=10; ++n){
        if(n==2){
            std::cout<<"------------ZAD3------------"<<std::endl;
        }
        c3(n,0);
    }

    return 0;
}

void c1(float a, float b, int n){
    float *x = vector(1, n);
    float *w = vector(1,n);

    gauleg(a, b, x, w, n);

    float sum = 0.0;

    for(int k =1; k<=n; ++k){
        sum+= w[k]* fun1(x[k]);
    }
    std::cout<<"suma dla n = "<<n<<" to:"<<sum<<" dla bledu rownego: "<<fabs(sum-M_PI/3)<<std::endl;

    free_vector(x, 1,n);
    free_vector(w, 1,n);
}

void c2a(int n){
    float *x = vector(1, n);
    float *w = vector(1,n);

    gauher(x, w, n);

    float sum = 0.0;

    for(int k =1; k<=n; ++k){
        sum+= w[k]* fun2(x[k]);
    }
    sum = sum/2.0;
    std::cout<<"suma dla n = "<<n<<" to:"<<sum<<" dla bledu rownego: "<<fabs(sum+0.8700577)<<std::endl;

    free_vector(x, 1,n);
    free_vector(w, 1,n);
}

void c2b(float a, float b, int n){
    float *x = vector(1, n);
    float *w = vector(1,n);

    gauleg(a, b, x, w, n);

    float sum = 0.0;

    for(int k =1; k<=n; ++k){
        sum+= w[k]* fun3(x[k]);
    }

    std::cout<<"suma dla n = "<<n<<" to:"<<sum<<" dla bledu rownego: "<<fabs(sum+0.8700577)<<std::endl;

    free_vector(x, 1,n);
    free_vector(w, 1,n);
}

void c3(int n,float alfa){
    float *x = vector(1, n);
    float *w = vector(1,n);

    gaulag(x, w, n, alfa);

    float sum = 0.0;

    for(int k =1; k<=n; ++k){
        sum+= w[k]* fun4(x[k]);
    }

    std::cout<<"suma dla n = "<<n<<" to:"<<sum<<" dla bledu rownego: "<<fabs(sum-2.0/13.0)<<std::endl;

    free_vector(x, 1,n);
    free_vector(w, 1,n);
}

float fun1(float x){
    return (1.0/(x*sqrt(pow(x,2)-1.0)));
}

float fun2(float x){
    return log(fabs(x));
}

float fun3(float x){
    return (log(x)*exp(-pow(x,2)));
}

float fun4(float x){
    return (sin(2*x)*exp(-2*x));
}

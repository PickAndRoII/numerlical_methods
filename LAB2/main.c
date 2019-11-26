#include <math.h>
#include </usr/include/gsl/gsl_linalg.h>

#define SIZE 4

int main(){
    FILE *fp;
    int delta = 2;
    gsl_matrix *A = gsl_matrix_calloc(SIZE, SIZE);

    fp = fopen("wynik.dat", "w");

    for(int i = 0; i < SIZE; ++i){
        for(int j= 0; j < SIZE; ++j){
            gsl_matrix_set(A, i, j, 1.0/(i+j+delta));
        }
    }
    
    int signum;
    gsl_permutation *p = gsl_permutation_calloc(SIZE);
    gsl_linalg_LU_decomp(A, p, &signum);
    
    double wyznacznik = 1;
    for(int i = 0; i < SIZE; ++i){
        wyznacznik = wyznacznik * gsl_matrix_get(A, i, i);
        fprintf(fp, "%g ", gsl_matrix_get(A, i, i));
    }
    fprintf(fp, "\nWyznacznik macierzy A: %g \n",wyznacznik);
    fprintf(fp,"\n");

    
    gsl_vector *b = gsl_vector_calloc(SIZE);
    gsl_vector *x = gsl_vector_calloc(SIZE);
    gsl_matrix *Aodw = gsl_matrix_calloc(SIZE, SIZE);
    for(int i = 0; i < SIZE; ++i){
        gsl_vector_set_zero(b);
        gsl_vector_set(b, i, 1.0);
        gsl_linalg_LU_solve(A, p, b, x);

        for(int j = 0; j < SIZE; ++j){
            gsl_matrix_set(Aodw, j, i, gsl_vector_get(x, j));
        }
    }
    
   for(int i = 0; i < SIZE; ++i){
       for(int j = 0; j < SIZE; ++j){
           fprintf(fp, "%g ", gsl_matrix_get(Aodw, i, j));
       }
       fprintf(fp,"\n");
   }
    fprintf(fp,"\n");
    gsl_matrix *A2 = gsl_matrix_calloc(SIZE, SIZE);
    for(int i = 0; i < SIZE; ++i){
        for(int j= 0; j < SIZE; ++j){
            gsl_matrix_set(A2, i, j, 1.0/(i+j+delta));
        }
    }

    gsl_matrix *C = gsl_matrix_calloc(SIZE, SIZE);
    double val = 0.0;
    for(int i = 0; i < SIZE; ++i){
        for(int j = 0; j < SIZE; ++j){
            for(int k = 0; k < SIZE; ++k){
                val = val + (gsl_matrix_get(A2, i, k) * gsl_matrix_get(Aodw, k, j));
            }
        gsl_matrix_set(C, i, j, val);
        val = 0.0;
        }
    }

    for(int i = 0; i < SIZE; ++i){
       for(int j = 0; j < SIZE; ++j){
           fprintf(fp, "%g ", gsl_matrix_get(C, i, j));
       }
       fprintf(fp,"\n");
    }
    fprintf(fp,"\n");

    double Amax =0.0, Aodwmax = 0.0;
    for(int i = 0; i < SIZE; ++i){
       for(int j = 0; j < SIZE; ++j){
           if(fabs(gsl_matrix_get(A2, i, j)) > Amax){
               Amax = fabs(gsl_matrix_get(A2, i, j));
           }
            if(fabs(gsl_matrix_get(Aodw, i, j)) > Aodwmax){
               Aodwmax = fabs(gsl_matrix_get(Aodw, i, j));
           }
       }
    }
    fprintf(fp,"%g\n", Amax);
    fprintf(fp,"%g\n", Aodwmax);

    double wum = Amax * Aodwmax;
    fprintf(fp,"%g\n", wum);

    fclose(fp);
    gsl_matrix_free(A);
    gsl_matrix_free(Aodw);
    gsl_matrix_free(C);
    gsl_vector_free(b);
    gsl_vector_free(x);
    gsl_permutation_free(p);
    return 0;
}

/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"

/*
 * Add your optimized implementation here
 */

double* my_solver(int N, double *A, double* B) {
	printf("OPT SOLVER\n");
	int i, j, k;
	double *transpose = calloc(N * N, sizeof(double));
	double *A2 = calloc(N * N, sizeof(double));
	double *result = calloc(N * N, sizeof(double));
	
	for (i = 0; i < N; i++){
		register double *pa = &transpose[i*N];
		for (j = 0; j < N; j++){
			register double *pb = &A[j * N];
			*(pa + j) = *(pb + i);
			//transpose[i * N + j] = A[j * N + i];
		}
	}
	
	// B * A tran
	for (i = 0; i < N; i++){
		register double *orig_pa = &B[i*N];
		for (j = 0; j < N; j++){
			register double suma = 0;
			register double *pa = orig_pa;
			register double *pb = &transpose[j];
			for (k = 0; k < N; k++){
				suma += *pa * *pb;
                pa++;
                pb += N;
			}
			result[i * N + j] = suma;
		}
	}
	// A ^ 2
	for (i = 0; i < N; i++){
		register double *orig_pa = &A[i*N];
		for (j = i; j < N; j++){
			register double suma = 0;
			register double *pa = orig_pa;
			register double *pb = &A[j];
			for (k = 0; k < N; k++){
				suma += *pa * *pb;
                pa++;
                pb += N;
			}
			A2[i * N + j] = suma;
			
		}
	}
	// A ^ 2 * B
	for (i = 0; i < N; i++){
		register double *orig_pa = &A2[i*N];
		for (j = 0; j < N; j++){
			register double suma = 0;
			register double *pa = orig_pa;
			register double *pb = &B[j];
			for (k = 0; k < N; k++){
				suma += *pa * *pb;
                pa++;
                pb += N;
			}
			result[i * N + j] += suma;
		}
	}

	free(A2);
	free(transpose);
	return result;	
}

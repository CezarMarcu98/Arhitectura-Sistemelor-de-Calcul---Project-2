/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"
#include <cblas.h>

/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {
	printf("BLAS SOLVER\n");
	double *alpha = calloc(N * N, sizeof(double));
	double *beta = calloc(N * N, sizeof(double));
	double *C = calloc(N * N, sizeof(double));
	int i, j;
	cblas_dcopy(N * N, A, 1, alpha, 1);
	cblas_dtrmm(101, 141, 121, 111, 131, N, N, 1, A, N, alpha, N);
	//alpha = A ^ 2

	cblas_dcopy(N * N, B, 1, beta, 1);
	cblas_dtrmm(101, 141, 121, 111, 131, N, N, 1, alpha, N, beta, N);
	//beta = A ^ 2 * B
	
	cblas_dtrmm(101, 142, 121, 112, 131, N, N, 1, A, N, B, N);
	// B = A tran * B

	for (i = 0; i < N; i++){
		for (j = 0; j < N; j ++){
			C[i * N + j] = B[i * N + j] + beta[i * N + j];
		}
	}
	free(beta);
	free(alpha);
	return C;
}

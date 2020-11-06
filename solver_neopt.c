/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	printf("NEOPT SOLVER\n");
	int i, j, k;
	double *transpose = calloc(N * N, sizeof(double));
	double *alpha = calloc(N * N, sizeof(double));
	double *beta = calloc(N * N, sizeof(double));
	double *A2 = calloc(N * N, sizeof(double));
	double *result = calloc(N * N, sizeof(double));

	// transposing A
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			transpose[i * N + j] = A[j * N + i];
		}
	}
	
	// B * A tran
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			//  if ((i + j) < (N - 1)){
			// 	 alpha[i*N + j] = 0;
			// 	 continue;
			//  }
			for (k = 0; k < N; k++){
				alpha[i * N + j] += B[i * N + k] * transpose[k * N + j];
			}
			result[i * N + j] = alpha[i * N + j];
		}
	}
	// A ^ 2
	for (i = 0; i < N; i++){
		for (j = i; j < N; j++){
			for (k = i; k < N; k++){
				A2[i * N + j] += A[i * N + k] * A[k * N + j];
			}
		}
	}
	// A ^ 2 * B
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			for (k = i; k < N; k++){
				beta[i * N + j] += A2[i * N + k] * B[k * N + j];
			}
			result[i * N + j] += beta[i * N + j];
		}
	}


	free(A2);
	free(beta);
	free(alpha);
	free(transpose);
	return result;
}

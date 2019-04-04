/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
	int bias_x, bias_y, offset_x, offset_y, v0, v1, v2, v3, v4, v5, v6, v7;
	if(M == 32){
		for(bias_x = 0; bias_x < N; bias_x += 8){
			for(bias_y = 0; bias_y < M; bias_y += 8){
				for(offset_x = 0; offset_x < 8 && offset_x + bias_x < N; offset_x++){
					for(offset_y = 0; offset_y < 8 && offset_y + bias_y < M; offset_y++){
						if(offset_x+bias_x == offset_y+bias_y){
							v0 = A[offset_x + bias_x][offset_y+bias_y];
							v1 = offset_x + bias_x;
						}
						else{
							B[bias_y + offset_y][bias_x + offset_x] = A[bias_x + offset_x][bias_y + offset_y];
						}
					}
					if(bias_x == bias_y){
						B[v1][v1] = v0;
					}
				}
			}
		}	
	}

	else if(M == 64){
		for(bias_x = 0; bias_x < N; bias_x += 8){
			for(bias_y = 0; bias_y < M; bias_y += 8){
				
				//set B[0]~B[3], at the same time, make it hot.
				for(offset_x = 0; offset_x < 4; offset_x++){
					v0 = A[bias_x + offset_x][bias_y + 0];
					v1 = A[bias_x + offset_x][bias_y + 1];
					v2 = A[bias_x + offset_x][bias_y + 2];
					v3 = A[bias_x + offset_x][bias_y + 3];
					v4 = A[bias_x + offset_x][bias_y + 4];
					v5 = A[bias_x + offset_x][bias_y + 5];
					v6 = A[bias_x + offset_x][bias_y + 6];
					v7 = A[bias_x + offset_x][bias_y + 7];
					
					B[bias_y + 0][bias_x + offset_x + 0] = v0;
					B[bias_y + 1][bias_x + offset_x + 0] = v1;
					B[bias_y + 2][bias_x + offset_x + 0] = v2;
					B[bias_y + 3][bias_x + offset_x + 0] = v3;
					B[bias_y + 0][bias_x + offset_x + 4] = v4;				
					B[bias_y + 1][bias_x + offset_x + 4] = v5;
					B[bias_y + 2][bias_x + offset_x + 4] = v6;				
					B[bias_y + 3][bias_x + offset_x + 4] = v7;	
				}
				
				for(offset_x = 4; offset_x < 8; offset_x++){
					//load A[n] into registers
					v0 = A[bias_x + offset_x][bias_y + 0];
					v1 = A[bias_x + offset_x][bias_y + 1];
					v2 = A[bias_x + offset_x][bias_y + 2];
					v3 = A[bias_x + offset_x][bias_y + 3];
					v4 = A[bias_x + offset_x][bias_y + 4];
					v5 = A[bias_x + offset_x][bias_y + 5];
					v6 = A[bias_x + offset_x][bias_y + 6];
					v7 = A[bias_x + offset_x][bias_y + 7];
					
					//make B[0]~B[n-1] hot again to kick out A[n].
					for(offset_y = 0; offset_y < offset_x; offset_y++){
						B[bias_y + offset_y][bias_x] = B[bias_y + offset_y][bias_x];
					}
					
					//set B[n], B[n-4] again.
					B[bias_y + offset_x][bias_x + 0] = B[bias_y + offset_x - 4][bias_x + 4];
					B[bias_y + offset_x][bias_x + 1] = B[bias_y + offset_x - 4][bias_x + 5];
					B[bias_y + offset_x][bias_x + 2] = B[bias_y + offset_x - 4][bias_x + 6];
					B[bias_y + offset_x][bias_x + 3] = B[bias_y + offset_x - 4][bias_x + 7];
					
					B[bias_y + offset_x - 4][bias_x + 4] = v0;
					B[bias_y + offset_x - 4][bias_x + 5] = v1;
					B[bias_y + offset_x - 4][bias_x + 6] = v2;
					B[bias_y + offset_x - 4][bias_x + 7] = v3;

					B[bias_y + offset_x][bias_x + 4] = v4;
					B[bias_y + offset_x][bias_x + 5] = v5;
					B[bias_y + offset_x][bias_x + 6] = v6;
					B[bias_y + offset_x][bias_x + 7] = v7;
				}
				
				//finish B[n][4]~B[n][8].
				for(offset_x = 0; offset_x < 4; offset_x++){
					for(offset_y = 0; offset_y < offset_x; offset_y++){
						v0 = B[bias_y + 0 + offset_x][bias_x + 4 + offset_y];
						B[bias_y + 0 + offset_x][bias_x + 4 + offset_y] = B[bias_y + 0 + offset_y][bias_x + 4 + offset_x];
						B[bias_y + 0 + offset_y][bias_x + 4 + offset_x] = v0;
						
						v1 = B[bias_y + 4 + offset_x][bias_x + 4 + offset_y];
						B[bias_y + 4 + offset_x][bias_x + 4 + offset_y] = B[bias_y + 4 + offset_y][bias_x + 4 + offset_x];
						B[bias_y + 4 + offset_y][bias_x + 4 + offset_x] = v1;
					}
				}

			}
		}
	}

	else{
		for(bias_x = 0; bias_x < N; bias_x += 16){
			for(bias_y = 0; bias_y < M; bias_y += 8){
				for(offset_x = 0; offset_x < 16 && offset_x + bias_x < N; offset_x++){
					for(offset_y = 0; offset_y < 8 && offset_y + bias_y < M; offset_y++){
						B[bias_y + offset_y][bias_x + offset_x] = A[bias_x + offset_x][bias_y + offset_y];
					}
				}
			}
		}
	}

}
/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 
char transpose_6167best_desc[] = "6167best";
void transpose_6167best(int M, int N, int A[N][M], int B[M][N])
{
	int bias_x, bias_y, offset_x, offset_y;
	for(bias_x = 0; bias_x < N; bias_x += 16){
		for(bias_y = 0; bias_y < M; bias_y += 8){
			for(offset_x = 0; offset_x < 16 && offset_x + bias_x < N; offset_x++){
				for(offset_y = 0; offset_y < 8 && offset_y + bias_y < M; offset_y++){
					B[bias_y + offset_y][bias_x + offset_x] = A[bias_x + offset_x][bias_y + offset_y];
				}
			}
		}
	}
}

char transpose_3232best_desc[] = "3232best";
void transpose_3232best(int M, int N, int A[N][M], int B[M][N])
{
	int bias_x, bias_y, offset_x, offset_y, svd, tmp;
	for(bias_x = 0; bias_x < N; bias_x += 8){
		for(bias_y = 0; bias_y < M; bias_y += 8){
			for(offset_x = 0; offset_x < 8 && offset_x + bias_x < N; offset_x++){
				for(offset_y = 0; offset_y < 8 && offset_y + bias_y < M; offset_y++){
					if(offset_x+bias_x == offset_y+bias_y){
						svd = A[offset_x + bias_x][offset_y+bias_y];
						tmp = offset_x + bias_x;
					}
					else{
						B[bias_y + offset_y][bias_x + offset_x] = A[bias_x + offset_x][bias_y + offset_y];
					}
				}
				if(bias_x == bias_y){
					B[tmp][tmp] = svd;
				}
			}
		}
	}
}

char transpose_6464best_desc[] = "6464best";
void transpose_6464best(int M, int N, int A[N][M], int B[M][N])
{
	int bias_x, bias_y, t03, t13, t23, t33, t12, t22, t32, t21, t31, t30;
	for(bias_x = 0; bias_x < M; bias_x += 4){
		for(bias_y = 0; bias_y < N; bias_y += 4){
			//a0, a1, a2, a3 open
			t03 = A[bias_x + 3][bias_y];
			t13 = A[bias_x + 3][bias_y + 1];
			t23 = A[bias_x + 3][bias_y + 2];
			t33 = A[bias_x + 3][bias_y + 3];
			t12 = A[bias_x + 2][bias_y + 1];
			t22 = A[bias_x + 2][bias_y + 2];
			t32 = A[bias_x + 2][bias_y + 3];
			t21 = A[bias_x + 1][bias_y + 2];
			t31 = A[bias_x + 1][bias_y + 3];
			t30 = A[bias_x][bias_y + 3];
			//b0, a0, a1, a2 open
			B[bias_y][bias_x + 3] = t03;
			B[bias_y][bias_x + 2] = A[bias_x + 2][bias_y];
			B[bias_y][bias_x + 1] = A[bias_x + 1][bias_y];
			B[bias_y][bias_x] = A[bias_x][bias_y];
			//b1, b0, a0, a1 open
			B[bias_y + 1][bias_x + 3] = t13;
			B[bias_y + 1][bias_x + 2] = t12;
			B[bias_y + 1][bias_x + 1] = A[bias_x + 1][bias_y + 1];
			B[bias_y + 1][bias_x] = A[bias_x][bias_y + 1];
			//b2, b1, b0, a0 open
			B[bias_y + 2][bias_x + 3] = t23;
			B[bias_y + 2][bias_x + 2] = t22;
			B[bias_y + 2][bias_x + 1] = t21;
			B[bias_y + 2][bias_x] = A[bias_x][bias_y + 2];
			//b3, b2, b1, b0 open
			B[bias_y + 3][bias_x + 3] = t33;
			B[bias_y + 3][bias_x + 2] = t32;
			B[bias_y + 3][bias_x + 1] = t31;
			B[bias_y + 3][bias_x] = t30;

		}
	}
}

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 
	registerTransFunction(transpose_6167best, transpose_6167best_desc);
	registerTransFunction(transpose_3232best, transpose_3232best_desc);
	registerTransFunction(transpose_6464best, transpose_6464best_desc);
    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}


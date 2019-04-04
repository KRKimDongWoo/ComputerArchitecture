#include <stdio.h>



int main() {

	int A[8][8];
	int B[8][8];
	int bias_x, bias_y, offset_x, offset_y, v0, v1, v2, v3, v4, v5, v6, v7;
	int M = 8, N = 8;
	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++){
			A[i][j] = i * 8 + j;
			B[i][j] = 99;
		}
	}

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
			printf("---------------set B[0]-B[3]----------------\n");

			for(int i = 0; i < 8; i++){
				for(int j = 0; j < 8; j++){
					printf("%d ", B[i][j]);
					if(B[i][j] < 10) printf(" ");
				}
				printf("\n");
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
			printf("---------------set B[n], B[-4]----------------\n");
			for(int i = 0; i < 8; i++){
				for(int j = 0; j < 8; j++){
					printf("%d ", B[i][j]);
					if(B[i][j] < 10) printf(" ");
				}
				printf("\n");
			}

		
			//finish B[n][4]~B[n][8].
			for(offset_x = 0; offset_x < 4; offset_x++){
				for(offset_y = 0; offset_y < offset_x; offset_y++){
					v0 = B[bias_y + 0 + offset_x][bias_x + 4 + offset_y];
					B[bias_y + 0 + offset_x][bias_x + 4 + offset_y] = B[bias_y + 0 + offset_y][bias_x + 4 + offset_x];
					B[bias_y + 0 + offset_y][bias_x + 4 + offset_x] = v0;
					printf("(%d, %d), (%d, %d) swaped\n", bias_y + 0 + offset_x, bias_x + 4 + offset_y, bias_y + 0 + offset_y, bias_x + 4 + offset_x);

					v1 = B[bias_y + 4 + offset_x][bias_x + 4 + offset_y];
					B[bias_y + 4 + offset_x][bias_x + 4 + offset_y] = B[bias_y + 4 + offset_y][bias_x + 4 + offset_x];
					B[bias_y + 4 + offset_y][bias_x + 4 + offset_x] = v1;
					printf("(%d, %d), (%d, %d) swaped\n", bias_y + 4 + offset_x, bias_x + 4 + offset_y, bias_y + 4 + offset_y, bias_x + 4 + offset_x);
				}
			}
		}
	}
	printf("-------------------------done!---------------------\n");
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			printf("%d ", B[i][j]);
			if(B[i][j] < 10) printf(" ");
		}
		printf("\n");
	}


}

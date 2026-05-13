// Problem Statement:Vector Multiplication
//**colab */
// !nvidia-smi    or nvcc 
//!nvcc vector_mul.cu -o vector_mul
//!./vector_mul
//**window */
//nvcc --version
//nvcc program.cu -o program
//program

%%writefile matrix_mul_input.cu
#include <stdio.h>

#define N 3   // Change size if needed

__global__ void matrixMultiply(int *A, int *B, int *C) {
    int row = threadIdx.y;
    int col = threadIdx.x;

    int sum = 0;

    for (int k = 0; k < N; k++) {
        sum += A[row * N + k] * B[k * N + col];
    }

    C[row * N + col] = sum;
}

int main() {
    int A[N][N], B[N][N], C[N][N];

    int *d_A, *d_B, *d_C;

    // Take input for Matrix A
    printf("Enter elements of Matrix A:\n");
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            scanf("%d", &A[i][j]);
        }
    }

    // Take input for Matrix B
    printf("Enter elements of Matrix B:\n");
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            scanf("%d", &B[i][j]);
        }
    }

    // Allocate memory on GPU
    cudaMalloc((void**)&d_A, N*N*sizeof(int));
    cudaMalloc((void**)&d_B, N*N*sizeof(int));
    cudaMalloc((void**)&d_C, N*N*sizeof(int));

    // Copy data to GPU
    cudaMemcpy(d_A, A, N*N*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, N*N*sizeof(int), cudaMemcpyHostToDevice);

    dim3 threads(N, N);

    // Kernel launch
    matrixMultiply<<<1, threads>>>(d_A, d_B, d_C);

    // Copy result back
    cudaMemcpy(C, d_C, N*N*sizeof(int), cudaMemcpyDeviceToHost);

    // Print result
    printf("\nResult Matrix:\n");
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    // Free memory
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}
/*✅ 🟢 GOOGLE COLAB / LINUX (FINAL)
1. Check GPU
!nvidia-smi
2. Save and compile CUDA file
!nvcc matrix_mul_input.cu -o matrix_mul
3. Run program
!./matrix_mul
⚠️ IMPORTANT (Colab input note)

Since your program uses:

scanf()

In Colab, input may not work smoothly in terminal execution.

✔ Better option in Colab:

run in terminal mode
OR hardcode matrices for testing
✅ 🟢 WINDOWS (FINAL)
1. Check CUDA
nvcc --version
2. Compile
nvcc matrix_mul_input.cu -o matrix_mul.exe
3. Run
matrix_mul.exe
*/


/*
==========================
EXPECTED SAMPLE OUTPUT
==========================

Enter elements of Matrix A:
1 2 3
4 5 6
7 8 9

Enter elements of Matrix B:
9 8 7
6 5 4
3 2 1

Result Matrix:
30 24 18
84 69 54
138 114 90

==========================
*/

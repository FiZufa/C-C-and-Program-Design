#include <iostream>
#include <chrono>
#include <algorithm>
#include <cblas.h>
#include <cstdlib>
#include <random>
#include <Eigen/Dense>
#include <omp.h>
using namespace std::chrono;

void gemm_cblas(double alpha, double beta, double* A, double* B, double* C, int size);
void gemm_naive(double alpha, double beta, double* A, double* B, double* C, int size);
void gemm_naive_and_omp(double alpha, double beta, double* A, double* B, double* C, int size);
void gemm_eigen(double alpha, double beta, int size);
void gemm_m_block_multi(double alpha, double beta, double* A, double* B, double* C, int size, int m);
void gemm_block64_and_omp(double alpha, double beta, double* A, double* B, double* C, int size);

int main(){

    int n=3;    // matrix size nxn
    std::cout<<"n = "<< n << std::endl;

    // alpha and beta are fixed to make the observation easier
    double alpha = 1.0;
    double beta = 1.0;

    //create matrix with size n*n
    double * A = new double[n*n];
    double * B = new double[n*n];
    double * C = new double[n*n];

    //generate random matrix
    for (int i = 0; i < n * n; ++i) {
        A[i] = (double)rand() / RAND_MAX;
        B[i] = (double)rand() / RAND_MAX;
        C[i] = (double)rand() / RAND_MAX;
    }

    //start measuring the execution time
    auto start = std::chrono::high_resolution_clock::now();
    // call gemm function -> uncomment function that want to be called

    //gemm_cblas(alpha,beta,A,B,C,n); //-> OpenBLAS
    //gemm_naive(alpha,beta,A,B,C,n); //-> Naive
    //gemm_naive_and_omp(alpha,beta,A,B,C,n); // -> Naive + OpenMP
    //gemm_eigen(alpha,beta,n); // -> Eigen
    int m = 2 ; // -> blocksize for m-block matrix multiplication, can be set to 2,4,8,16,32, or 64
    //gemm_m_block_multi(alpha,beta,A,B,C,n,m);
    //gemm_block64_and_omp(alpha,beta,A,B,C,n);

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Execution time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns" << std::endl;


    //print the matrix result
    /*
    for(int i=0 ; i<n*n ; i++){
        std::cout<< C[i] << " " ;
    }
    */

   delete[] A;
   delete[] B;
   delete[] C;

    return 0;
}

void gemm_cblas(double alpha, double beta, double* A, double* B, double* C, int size){

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, size, size, size, alpha, size, size, B, size, beta, C, size);

}

void gemm_naive(double alpha, double beta, double* A, double* B, double* C, int size){

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            // Calculate the index for element (i, j)
            const int index = i * size + j;
            // Perform the computation
            C[index] = alpha * A[index] * B[index] + beta * C[index];
        }
    }
}

void gemm_naive_and_omp(double alpha, double beta, double* A, double* B, double* C, int size){

    #pragma omp parallel for
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            double temp = 0.0;

            for (int k = 0; k < size; ++k) {
                temp += A[i * size + k] * B[k * size + j];
            }

            C[i * size + j] = alpha * temp + beta * C[i * size + j];
        }
    }
}

void gemm_eigen(double alpha, double beta, int size){

    Eigen::MatrixXd A(size, size);
    Eigen::MatrixXd B(size, size);
    Eigen::MatrixXd C(size, size);

    A.setRandom();
    B.setRandom();
    C.setRandom();

    C = alpha*A*B + beta*C;

}

void gemm_m_block_multi(double alpha, double beta, double* A, double* B, double* C, int size, int m){

    int blockSize = m;

    for (int i = 0; i < size; i += blockSize) {
        for (int j = 0; j < size; j += blockSize) {
            for (int k = 0; k < size; k += blockSize) {
                // Compute block matrix multiplication within the block
                int blockRowSize = std::min(blockSize, size - i);
                int blockColSize = std::min(blockSize, size - j);
                int blockKSize = std::min(blockSize, size - k);
                for (int ii = 0; ii < blockRowSize; ii++) {
                    for (int jj = 0; jj < blockColSize; jj++) {
                        double sum = 0.0;
                        for (int kk = 0; kk < blockKSize; kk++) {
                            sum += A[(i + ii) * size + (k + kk)] * B[(k + kk) * size + (j + jj)];
                        }
                        C[(i + ii) * size + (j + jj)] = alpha * sum + beta * C[(i + ii) * size + (j + jj)];
                    }
                }
            }
        }
    }
}


void gemm_block64_and_omp(double alpha, double beta, double* A, double* B, double* C, int size){

    int blockSize = 64;

    #pragma omp parallel for
    for (int i = 0; i < size; i += blockSize) {
        for (int j = 0; j < size; j += blockSize) {
            for (int k = 0; k < size; k += blockSize) {
                // Compute block matrix multiplication within the block
                int blockRowSize = std::min(blockSize, size - i);
                int blockColSize = std::min(blockSize, size - j);
                int blockKSize = std::min(blockSize, size - k);
                for (int ii = 0; ii < blockRowSize; ii++) {
                    for (int jj = 0; jj < blockColSize; jj++) {
                        double sum = 0.0;
                        for (int kk = 0; kk < blockKSize; kk++) {
                            sum += A[(i + ii) * size + (k + kk)] * B[(k + kk) * size + (j + jj)];
                        }
                        C[(i + ii) * size + (j + jj)] = alpha * sum + beta * C[(i + ii) * size + (j + jj)];
                    }
                }
            }
        }
    }

}






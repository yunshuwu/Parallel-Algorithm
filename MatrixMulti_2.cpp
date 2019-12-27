#include <algorithm>
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include "get_time.h"
#include "reduce.h"

using namespace std;

void MatrixMulti_Tiled (long long int** A, long long int** B, long long int** Mul, long long int n) {
    cilk_for (long long int ih=0;ih < n;ih += 32) {
        cilk_for (long long int jh=0;jh < n;jh += 32) {
            for (long long int kh=0;kh < n;kh += 32) { // calculate each part (of size 32*32)
                for (long long int il=0; il < 32;il++)
                    for (long long int kl=0;kl < 32; kl++)
                        for (long long int jl=0; jl < 32; jl++)
                            Mul[ih+il][jh+jl] += A[ih+il][kh+kl] * B[kh+kl][jh+jl];
            }
        }
    }
}

int main(){
    long long int n;
    cin >> n;

    long long int** A = new long long int* [n]; // row
    for (long long int i=0;i<n;i++) A[i] = new long long int[n];// col
    long long int** B = new long long int* [n];
    for (long long int i=0;i<n;i++) B[i] = new long long int[n];
    long long int** Mul = new long long int* [n];
    for (long long int i=0;i<n;i++) Mul[i] = new long long int[n];

    for (long long int i=0;i<n;i++)
        for (long long int j=0;j<n;j++) A[i][j] = 1;
    for (long long int i=0;i<n;i++)
        for (long long int j=0;j<n;j++) B[i][j] = 1;
    
    timer t;
    t.start();
    MatrixMulti_Tiled(A, B, Mul, n);
    t.stop();

    for (long long int i=0;i<n;i++) {
        for (long long int j=0;j<n;j++) cout << Mul[i][j] << " ";
        cout << endl;
    }
    cout << "Time taken by function: " << t.get_total() << endl;

    for (long long int i=0;i<n;i++) delete[] A[i];
    delete[] A;
    for (long long int i=0;i<n;i++) delete[] B[i];
    delete[] B;
    for (long long int i=0;i<n;i++) delete[] Mul[i];
    delete[] Mul;
}

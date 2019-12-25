#include <algorithm>
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include "get_time.h"
#include "reduce.h"

using namespace std;

// int n;

void MatrixMulti (int** A, int** B, int** Mul, int n) {
    // int i, j, k;
    cilk_for (int i=0;i<n;i++) {
        cilk_for (int j=0;j<n;j++) {
            int temp[n];
            cilk_for (int k=0;k<n;k++) temp[k] = A[i][k] * B[k][j];
            Mul[i][j] = reduce(temp, n);
        }
    }
}

int main(){
    int n;
    cin >> n;
    int** A;
    int** B;
    int** Mul;

    A = (int **)malloc(n * sizeof(int *));
    for (int i=0;i < n;i++) A[i] = (int *)malloc(n * sizeof(int));

    B = (int **)malloc(n * sizeof(int *));
    for (int i=0;i < n;i++) B[i] = (int *)malloc(n * sizeof(int));

    Mul = (int **)malloc(n * sizeof(int *));
    for (int i=0;i < n;i++) Mul[i] = (int *)malloc(n * sizeof(int));

    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++) cin >> A[i][j];
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++) cin >> B[i][j];
    
    timer t;
    t.start();
    MatrixMulti(A, B, Mul, n);
    t.stop();

    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) cout << Mul[i][j] << " ";
        cout << endl;
    }
    cout << "Time taken by function: " << t.get_total() << endl;
    
    free(A);
    free(B);
    free(Mul);
}

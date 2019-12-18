#include <iostream>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include "get_time.h"

using namespace std;

void scan(int* in, int* out, int n, int* B, int* C){ // B of size n/2, C (of size n/2) is the prefix sum of B
    if (n == 0) {
        //out[n] = in[n];
	//cout << "out[1]" << out[n] << endl;
        return;
    }
    cout << "n is: " << n << endl;

    cilk_for (int i=0;i < n/2;i++) B[i] = in[2*i] + in[2*i+1]; // B in level n has n/2, left n-n/2 space
    
    for (int i=0;i<n/2;i++) cout << B[i] << " ";
    cout << endl;

    scan(B, C, n/2, B+n/2, C+n/2);

    out[0] = in[0];

    cout << "array C: " << endl;
    for (int i=0;i <n;i++) cout << C[i] << " ";
    cout << endl;

    cilk_for (int i = 1;i < n;i++) {
        if (i%2 == 0) out[i] = C[(i-1)/2] + in[i];
        else out[i] = C[(i-1)/2];
    }
    cout << "array out: " << endl;
    for (int i=0;i < n;i++) cout << out[i] << " ";
    cout << endl;
}

int main() {
    int n;
    cin >> n; 
    int* in = new int[n];
    int* out = new int[n];
    int* B = new int[n];
    int* C = new int[n];

    cilk_for (int i=0;i < n;i++) in[i] = i+1;

    timer t;
    t.start();
    scan(in, out, n, B, C);
    t.stop();

    cout << "Prefix sum of array in: " << endl;
    for (int i=0;i < n;i++) cout << out[i] << " ";
    cout << endl;

    cout << "Time taken by function: " << t.get_total() << endl;    

    delete[] in;
    delete[] out;
    delete[] B;
    delete[] C;
}

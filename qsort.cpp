#include <algorithm>
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include <chrono> 
using namespace std;
using namespace std::chrono;

int* A2;
long long int* B;
int* F;
int* e1;
int* e2;
int n;

void scanUp(int l, int r, int* A, long long int* sum, int k){
        if (l==r-1){
                sum[k] = A[l];
                //cout << "K is: " << k << " Range is: (" << l <<", " << r << "); sum[k]: " << sum[k] << endl;
                //printf("\n");
                return;
        }
        int mid = (l+r)/2;
        cilk_spawn scanUp(l, mid, A, sum, 2*k+1);
        scanUp(mid, r, A, sum, 2*k+2);
        cilk_sync;
        sum[k] = sum[2*k+1] + sum[2*k+2];
        //cout << "K is: " << k << " Range is: (" << l <<", " << r << "); sum[k]: " << sum[k] << endl;
        //printf("\n");
}

void scanDown(int l, int r, int* A, long long int* B, long long int* sum, int k, long long int offset){
        if(l == r-1){
                B[l] = A[l] + offset;
                return;
        }
        int mid = (l + r)/2;
        cilk_spawn scanDown(l, mid, A, B, sum, 2*k+1, offset);
        scanDown(mid, r, A, B, sum, 2*k+2, offset+sum[2*k+1]);
        cilk_sync;
}

void scan(int l, int r, int* A, long long int* B, long long int* sum){
	scanUp(l, r, A, sum, 0);
        scanDown(l, r, A, B, sum, 0, 0);
	//B is the prefix sum.
}

void qsort(int* A, int start, int end) {
        if (start == end) return;
        if (start > end-100) {
                sort(A+start, A+end);
                return;
        }
        int pivot = A[start];
	int nodenum = 4*n;
	long long int* sum = new long long int[nodenum];
	//int sum[2000000];
        cilk_for (int i = start; i < end; i++) A2[i] = A[i];

        cilk_for (int i = start; i < end; i++) {
                if (A2[i] < pivot) F[i] = 1; else F[i] = 0;
        }
        scan(start, end, F, B, sum);

        cilk_for (int i = start+1; i < end; i++) {
                if (F[i]) A[start+B[i]-1] = A2[i];
        }

        int x = B[end-1];
        A[start+x] = pivot;

        cilk_for (int i = start+1; i < end; i++) {
                if (A2[i] >= pivot) F[i] = 1; else F[i] = 0;
        }
        scan(start, end, F, B, sum);

        cilk_for (int i = start+1; i < end; i++) {
                if (F[i]) A[start+x+B[i]] = A2[i];
        }

        cilk_spawn
        qsort(A, start, start+x);
        qsort(A, start+x+1, end);
        cilk_sync;

        return;
}

int main(){
        //int n;
        cin >> n;
        int* A = new int[n];

        for(int i=0;i<n;i++) A[i] = rand() % n + 1;// %(rangeR-rangeL+1)+1
	cout << "A needs sort: " << endl;
        for(int i=0;i<n;i++) cout << A[i] << " ";
        cout << endl;

        A2 = new int[n];
	B = new long long int[n];
	F = new int[n];
	e1 = new int[n];
	e2 = new int[n];

        auto start = high_resolution_clock::now();

        qsort(A, 0, n);

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
	
	for (int i=0; i<n;i++) cout << A[i] << " ";
	cout << endl;
        cout << "Time taken by function: " << duration.count() << " microseconds" << endl;

	delete[] A;
	delete[] A2;
	delete[] B;
	delete[] F;
	delete[] e1;
	delete[] e2;

        return 0;
}



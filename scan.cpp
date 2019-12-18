#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include <chrono>
#include "get_time.h"

using namespace std;

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

int main(){
	int n;
	cin >> n;
	int* A = new int[n];
        long long int* B = new long long int[n];
        //int nodenum = 4*n;
        long long int* sum = new long long int[4*n];

	cilk_for(int i = 0;i < n;i++) A[i] = i+1;
	//cout << "This is array A: " << endl;
	//for(int i=0;i < n;i++) cout << A[i] << " ";

	timer t;
	t.start();
	
	scanUp(0, n, A, sum, 0);
	scanDown(0, n, A, B, sum, 0, 0);
	t.stop();
 
  	cout << "This is array A's prefix sum B: " << endl;
        for(int i=0;i < n;i++) cout << "B[" << i << "]=" << B[i] << endl;

	cout << "time taken by function: " << t.get_total() << endl;
 	
        delete[] A;
	delete[] B;
	delete[] sum;	
  	return 0; 
}

#include <iostream>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include <chrono>
#include "get_time.h"

using namespace std;

void scanSeq(int* A, int* B, int n){
	B[0] = A[0];
	for(int i = 1;i < n; i++){
		B[i] = A[i] + B[i-1];
	}
	return;
}

int main(){
	int n;
	cin >> n;
	int* A = new int[n];
	int* B = new int[n];

	cilk_for(int i=0;i<n;i++) A[i] = i+1;
	//cout << "Array A: " << endl;
	//for (int i = 0;i<n;i++) cout << A[i] << endl;

	timer t;
	t.start();
	scanSeq(A, B, n);
	t.stop();


	cout << "prefix sum of A: " << endl;
	for(int i=0;i < n;i++) cout << "B[" << i << "]=" << B[i] << endl;

	cout << "time taken by function: " << t.get_total() << endl;
	
	return 0;
}

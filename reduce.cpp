#include <iostream>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include <chrono>
#include "get_time.h"

using namespace std;
using namespace std::chrono;

int reduce(int* A, int n){
	if(n == 1) return A[0];
	int L, R;
	L = cilk_spawn reduce(A, n/2);
	R = reduce(A+n/2, n-n/2);
	cilk_sync;
	return L+R;
}

int main(){
	int n;
	cin >> n;
	int* A = new int[n];

	cilk_for(int i=0; i < n;i++) A[i] = i+1;
	
	//cout << "This is array A" << endl;
	//for(int i = 0;i<n;i++) cout << A[i] << endl;
	
	timer t;
	t.start();
	int sum = reduce(A, n);
	t.stop();

	cout << "time taken by function: " << t.get_total() << endl;
	
	cout << "Sum of A: " << sum << endl;
	return 0;
}

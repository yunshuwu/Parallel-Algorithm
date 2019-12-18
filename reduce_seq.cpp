#include <iostream>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include <chrono> 
#include "get_time.h"

using namespace std;
using namespace std::chrono;

int main(){
	int n;
	cin >> n;
	int* A = new int[n];
	cilk_for(int i=0; i < n;i++) A[i] = i+1;
	
	//cout << "This is array A" << endl;
	//for(int i = 0;i<n;i++) cout << A[i] << endl;

	int sum = 0;
	timer t; 
	t.start();
	for (int i=0;i<n;i++ ) sum += A[i];
	t.stop(); 
	cout << "time taken by function: " << t.get_total() << endl;
	
	cout << "Sum of A: " << sum << endl;

	return 0;
}

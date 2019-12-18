#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>

#include <chrono> 
using namespace std; 
using namespace std::chrono; 


void scanUp(int l, int r, int* A, int* sum, int k){
	if (l==r-1){
		sum[k] = A[l];
		return;		
	}
	int mid = (l+r)/2;
	cilk_spawn scanUp(l, mid, A, sum, 2*k+1);
	scanUp(mid, r, A, sum, 2*k+2);
	cilk_sync;
}

void scanDown(int l, int r, int* A, int* B, int* sum, int k, int offset){
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
	int* B = new int[n];
	int* sum = new int[int(pow(2, log(n)+1))-1];

    auto start = high_resolution_clock::now();	
	scanUp(0, n, A, sum, 0);
	scanDown(0, n, A, B, sum, 0, 0);
  
    // Get ending timepoint 
    auto stop = high_resolution_clock::now(); 
  
    // Get duration. Substart timepoints to  
    // get durarion. To cast it to proper unit 
    // use duration cast method 
    auto duration = duration_cast<microseconds>(stop - start); 
  
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 
}


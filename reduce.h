#include <iostream>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include "get_time.h"

using namespace std;

int reduce(int* A, int n){
	if(n == 1) return A[0];
    if (n < 100) {
        int sum = 0;
        for (int i=0;i<n;i++) sum += A[i];
        return sum;
    }
	int L, R;
	L = cilk_spawn reduce(A, n/2);
	R = reduce(A+n/2, n-n/2);
	cilk_sync;
	return L+R;
}

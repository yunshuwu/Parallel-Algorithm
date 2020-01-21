#include <iostream>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include "get_time.h"

using namespace std;

int main(){
	int n=1;
	int A[1];

	A[0] = 233;
	cout << "this is n: " << n << endl;
	
	cout << "this is array A: " << endl;
	for (int i=0; i< n/2; i++) cout << A[i] << endl;

	return 0;
}

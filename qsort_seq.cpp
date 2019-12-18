#include <stdlib.h>
#include <iostream>
#include <chrono> 

using namespace std::chrono;
using namespace std;

int compare(const void* p, const void* q){
	return (*(int*) p - *(int*)q);
}

int main(){
	int n;
	cin >> n;
	int* A = new int[n];
       	for(int i=0;i<n;i++) A[i] = rand() % n + 1;// %(rangeR-rangeL+1)+1

	for(int i=0;i<n;i++) cout << A[i] << " ";
	cout << endl;

	auto start = high_resolution_clock::now();
	qsort(A, n, sizeof(int), compare);
	auto stop = high_resolution_clock::now(); 
	auto duration = duration_cast<microseconds>(stop - start);

	for(int i=0;i<n;i++) cout << A[i] << " ";
	cout << endl;

	cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
	return 0;
}

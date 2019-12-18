#include <algorithm>
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include "get_time.h"

using namespace std;

int* temp;
long long int* B;
int* flag;
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

void qsort(int* A, int st, int ed){ //A: [st, ed)		
    if (st == ed) return;
    long long int* sum = new long long int[4*n];
    cilk_for (int i=st;i < ed;i++) temp[i] = A[i];

    //cout << "Array temp: " << endl;
    //for (int i=st;i<ed;i++) cout << temp[i] << " ";
    //cout << endl;

    int pivot = A[st];
    int pivotpos;
    // samller than pivot
    cilk_for (int i = st;i < ed;i++){
        if (temp[i] < pivot) {
            flag[i] = 1;
        }else{
            flag[i] = 0;
        }
    }
    scan(st, ed, flag, B, sum);
    
//    cout << "flag - for the smaller part:" << endl;
//    for(int i=st;i<ed;i++) cout << flag[i] << " ";
//    cout << endl;
//
//    cout << "prefix sum B - for the smaller part:" << endl;
//    for(int i=st;i<ed;i++) cout << B[i] << " ";
//    cout << endl;

    cilk_for (int i=st+1;i < ed;i++) {
        if (B[i] != B[i-1]) {
            A[B[i] - 1 + st] = temp[i];
        }
    }
    pivotpos = B[ed-1];// position of pivot

    //larger than pivot
    cilk_for (int i=st+1;i < ed;i++) {
	if(temp[i] >= pivot){
            flag[i] = 1;
        }else{
            flag[i] = 0;
        }
    }
    //cilk_for (int i=0;i < 4*n;i++) sum[i] = 0;
    scan(st, ed, flag, B, sum);
    
//    cout << "flag - for the larger part:" << endl;
//    for(int i=st;i<ed;i++) cout << flag[i] << " ";
//    cout << endl;
//
//    cout << "pefix sum B - for the larger part:" << endl;
//    for(int i=st;i<ed;i++) cout << B[i] << " ";
//    cout << endl;
    
    cilk_for (int i=st+1;i < ed;i++){
        if (B[i] != B[i-1]){
            A[st + pivotpos + B[i]] = temp[i];
        }
    }

    A[st+pivotpos] = pivot;
    
//    cout << "A:" << endl;
//    for(int i=0;i<n;i++) cout << A[i] << " ";
//    cout << endl;

    cilk_spawn qsort(A, st, st + pivotpos);
    qsort(A, st + pivotpos+1, ed);
    cilk_sync;
}

int main(){
        //int n;
        cin >> n;
        int* A = new int[n];
        temp = new int[n];
        B = new long long int[n];
        flag = new int[n];

        //for (int i=0;i<n;i++) cin >> A[i];
	cilk_for(int i=0;i<n;i++) A[i] = rand() % n + 1;// %(rangeR-rangeL+1)+1
        cout << "A needs sort: " << endl;
        for(int i=0;i<n;i++) cout << A[i] << " ";
	cout << endl;

        timer t;
        t.start();
        qsort(A, 0, n);
        t.stop();

        for (int i=0; i<n;i++) cout << A[i] << " ";
	cout << endl;
        cout << "Time taken by function: " << t.get_total() << endl;

        delete[] A;
        delete[] temp;
        delete[] B;
        delete[] flag;

        return 0;
}


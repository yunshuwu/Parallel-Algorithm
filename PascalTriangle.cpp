#include <iostream>
#include <stdlib.h>

#define CHOOSE_SIZE 100
int choose[CHOOSE_SIZE][CHOOSE_SIZE];

using namespace std;

void init_choose () {
    for (int n = 0; n < CHOOSE_SIZE;++n) {
        choose[n][0] = 1; // first col
        choose[n][n] = 1; // diagonal
    }
    for (int n = 1;n < CHOOSE_SIZE;++n) {
        choose[0][n] = 0;
        for (int k = 1; k < n; ++k) {
            choose[n][k] = choose[n-1][k-1] + choose[n-1][k];
            choose[k][n] = 0;
        }
    }
}

int main() {
    init_choose();
    
    int n;
    cin >> n;
    
    cout << "int choose[" << n << "][" << n << "] = {\n" << endl;
    for (int i = 0;i < n;++i) {
        cout << "   {";
        for (int j = 0;j < n;++j) {
            cout << choose[i][j] << " ";
        }
        cout << "}" << endl;
    }
    cout << "}" << endl;
}

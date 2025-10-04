#include <vector>
#include <iostream>
using namespace std;

using Matrix = vector<vector<double> >;

Matrix Input_vector(int N){
    Matrix v(N, vector<double>(N));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            double a;
            cin >> a;
            v[i][j] = a;
        }
    }
    return v;
}

int Print_vector(const Matrix &v, int N){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << v[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}

#include <vector>
#include <iostream>
using namespace std;

using RelationMatrix = vector<vector<int>>;

// 5x5 관계 행렬 입력 함수
RelationMatrix inputRelationMatrix() {
    const int SIZE = 5;
    RelationMatrix matrix(SIZE, vector<int>(SIZE));
    
    cout << "5x5 관계 행렬을 입력하세요 (0 또는 1):\n";
    for (int i = 0; i < SIZE; i++) {
        cout << "행 " << (i + 1) << ": ";
        for (int j = 0; j < SIZE; j++) {
            cin >> matrix[i][j];
        }
    }
    
    return matrix;
}

// 관계 행렬 출력 함수
void printRelationMatrix(const RelationMatrix& matrix) {
    const int SIZE = 5;
    
    cout << "관계 행렬:\n";
    cout << "   ";
    for (int i = 1; i <= SIZE; i++) {
        cout << i << " ";
    }
    cout << "\n";
    
    for (int i = 0; i < SIZE; i++) {
        cout << (i + 1) << "  ";
        for (int j = 0; j < SIZE; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

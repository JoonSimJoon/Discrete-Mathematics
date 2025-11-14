#include <vector>
#include <iostream>
#include <set>
using namespace std;

using RelationMatrix = vector<vector<int>>;
const int SIZE = 5;

// 반사 관계 판별 (Reflexive)
bool isReflexive(const RelationMatrix& matrix) {
    for (int i = 0; i < SIZE; i++) {
        if (matrix[i][i] != 1) {
            return false;
        }
    }
    return true;
}

// 대칭 관계 판별 (Symmetric)
bool isSymmetric(const RelationMatrix& matrix) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] != matrix[j][i]) {
                return false;
            }
        }
    }
    return true;
}

// 추이 관계 판별 (Transitive)
bool isTransitive(const RelationMatrix& matrix) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == 1) {
                for (int k = 0; k < SIZE; k++) {
                    if (matrix[j][k] == 1 && matrix[i][k] != 1) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

// 반사 폐포 생성 (Reflexive Closure)
RelationMatrix reflexiveClosure(const RelationMatrix& matrix) {
    RelationMatrix result = matrix;
    
    for (int i = 0; i < SIZE; i++) {
        result[i][i] = 1;
    }
    
    return result;
}

// 대칭 폐포 생성 (Symmetric Closure)
RelationMatrix symmetricClosure(const RelationMatrix& matrix) {
    RelationMatrix result = matrix;
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (result[i][j] == 1) {
                result[j][i] = 1;
            }
        }
    }
    
    return result;
}

// 추이 폐포 생성 (Transitive Closure) - Warshall 알고리즘
RelationMatrix transitiveClosure(const RelationMatrix& matrix) {
    RelationMatrix result = matrix;
    
    for (int k = 0; k < SIZE; k++) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (result[i][k] == 1 && result[k][j] == 1) {
                    result[i][j] = 1;
                }
            }
        }
    }
    
    return result;
}

// 동치류 계산 함수
vector<set<int>> computeEquivalenceClasses(const RelationMatrix& matrix) {
    vector<set<int>> classes;
    vector<bool> visited(SIZE, false);
    
    for (int i = 0; i < SIZE; i++) {
        if (!visited[i]) {
            set<int> equivalenceClass;
            
            for (int j = 0; j < SIZE; j++) {
                if (matrix[i][j] == 1) {
                    equivalenceClass.insert(j + 1); // 1-based indexing
                    visited[j] = true;
                }
            }
            
            classes.push_back(equivalenceClass);
        }
    }
    
    return classes;
}

// 동치류 출력 함수
void printEquivalenceClasses(const RelationMatrix& matrix) {
    vector<set<int>> classes = computeEquivalenceClasses(matrix);
    
    cout << "\n동치류:\n";
    for (size_t i = 0; i < classes.size(); i++) {
        cout << "동치류 " << (i + 1) << ": { ";
        for (int elem : classes[i]) {
            cout << elem << " ";
        }
        cout << "}\n";
    }
}

#include <vector>
#include <iostream>
using namespace std;

using RelationMatrix = vector<vector<int>>;
const int SIZE = 5;

// 관계의 합성 (Composition) R1 ∘ R2
// 수학적 정의: (a,c) ∈ R1∘R2 ⟺ ∃b: (a,b)∈R1 ∧ (b,c)∈R2
RelationMatrix composeRelations(const RelationMatrix& R1, const RelationMatrix& R2) {
    RelationMatrix result(SIZE, vector<int>(SIZE, 0));
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // i에서 j로 가는 경로가 있는지 확인
            for (int k = 0; k < SIZE; k++) {
                if (R1[i][k] == 1 && R2[k][j] == 1) {
                    result[i][j] = 1;
                    break;
                }
            }
        }
    }
    
    return result;
}

// 관계 합성 분석 및 출력
void analyzeComposition(const RelationMatrix& matrix) {
    cout << "\n========================================\n";
    cout << "=== 추가 기능: 관계의 합성 분석 ===\n";
    cout << "========================================\n";
    
    cout << "\n원본 관계 R:\n";
    cout << "   1 2 3 4 5\n";
    for (int i = 0; i < SIZE; i++) {
        cout << (i + 1) << "  ";
        for (int j = 0; j < SIZE; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
    
    // R ∘ R 계산
    RelationMatrix R2 = composeRelations(matrix, matrix);
    
    cout << "\nR ∘ R (R을 자기 자신과 합성):\n";
    cout << "   1 2 3 4 5\n";
    for (int i = 0; i < SIZE; i++) {
        cout << (i + 1) << "  ";
        for (int j = 0; j < SIZE; j++) {
            cout << R2[i][j] << " ";
        }
        cout << "\n";
    }
    
    // R^3 = R ∘ R ∘ R 계산
    RelationMatrix R3 = composeRelations(R2, matrix);
    
    cout << "\nR^3 (R을 3번 합성):\n";
    cout << "   1 2 3 4 5\n";
    for (int i = 0; i < SIZE; i++) {
        cout << (i + 1) << "  ";
        for (int j = 0; j < SIZE; j++) {
            cout << R3[i][j] << " ";
        }
        cout << "\n";
    }
    
    // 합성의 의미 설명
    cout << "\n--- 관계 합성의 의미 ---\n";
    cout << "• R ∘ R: 두 단계로 연결된 관계\n";
    cout << "  예: (1,2)∈R, (2,3)∈R → (1,3)∈R∘R\n";
    cout << "• R^3: 세 단계로 연결된 관계\n";
    
    // 추이 관계와의 관계
    bool isTransitive = true;
    for (int i = 0; i < SIZE && isTransitive; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (R2[i][j] == 1 && matrix[i][j] == 0) {
                isTransitive = false;
                break;
            }
        }
    }
    
    cout << "\n--- 합성과 추이 관계 ---\n";
    if (isTransitive) {
        cout << "✓ R ∘ R ⊆ R: 추이 관계를 만족합니다.\n";
        cout << "  모든 2단계 경로가 R에 이미 포함되어 있습니다.\n";
    } else {
        cout << "✗ R ∘ R ⊈ R: 추이 관계를 만족하지 않습니다.\n";
        cout << "  2단계 경로 중 R에 없는 관계가 있습니다.\n";
        
        // 어떤 관계가 추가되는지 보여주기
        cout << "\n  추이 폐포로 추가될 관계:\n";
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (R2[i][j] == 1 && matrix[i][j] == 0) {
                    cout << "  (" << (i + 1) << ", " << (j + 1) << ")\n";
                }
            }
        }
    }
}


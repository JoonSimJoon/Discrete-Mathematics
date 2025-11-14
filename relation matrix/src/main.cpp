#include <vector>
#include <iostream>
using namespace std;

using RelationMatrix = vector<vector<int>>;

// 기본 함수 extern 선언
extern RelationMatrix inputRelationMatrix();
extern void printRelationMatrix(const RelationMatrix& matrix);
extern bool isReflexive(const RelationMatrix& matrix);
extern bool isSymmetric(const RelationMatrix& matrix);
extern bool isTransitive(const RelationMatrix& matrix);
extern RelationMatrix reflexiveClosure(const RelationMatrix& matrix);
extern RelationMatrix symmetricClosure(const RelationMatrix& matrix);
extern RelationMatrix transitiveClosure(const RelationMatrix& matrix);
extern void printEquivalenceClasses(const RelationMatrix& matrix);

// 추가 기능 extern 선언›
extern void analyzeComposition(const RelationMatrix& matrix);

int main() {
    cout << "=== 동치 관계 판별 프로그램 ===\n";
    cout << "집합 A = {1, 2, 3, 4, 5}\n\n";
    
    // 관계 행렬 입력
    RelationMatrix matrix = inputRelationMatrix();
    
    cout << "\n";
    printRelationMatrix(matrix);
    
    // 동치 관계 판별
    cout << "\n=== 동치 관계 판별 ===\n";
    bool reflexive = isReflexive(matrix);
    bool symmetric = isSymmetric(matrix);
    bool transitive = isTransitive(matrix);
    
    cout << "반사 관계 (Reflexive): " << (reflexive ? "O" : "X") << "\n";
    cout << "대칭 관계 (Symmetric): " << (symmetric ? "O" : "X") << "\n";
    cout << "추이 관계 (Transitive): " << (transitive ? "O" : "X") << "\n";
    
    // 동치 관계 판정
    bool isEquivalence = reflexive && symmetric && transitive;
    
    if (isEquivalence) {
        cout << "\n✓ 이 관계는 동치 관계입니다!\n";
        printEquivalenceClasses(matrix);
    } else {
        cout << "\n✗ 이 관계는 동치 관계가 아닙니다.\n";
        
        // 폐포 생성 및 변환
        cout << "\n=== 폐포 생성 ===\n";
        RelationMatrix currentMatrix = matrix;
        
        // 반사 폐포
        if (!reflexive) {
            cout << "\n--- 반사 폐포 생성 ---\n";
            cout << "변환 전:\n";
            printRelationMatrix(currentMatrix);
            
            currentMatrix = reflexiveClosure(currentMatrix);
            
            cout << "\n변환 후:\n";
            printRelationMatrix(currentMatrix);
            cout << "반사 관계: " << (isReflexive(currentMatrix) ? "O" : "X") << "\n";
        }
        
        // 대칭 폐포
        if (!symmetric) {
            cout << "\n--- 대칭 폐포 생성 ---\n";
            cout << "변환 전:\n";
            printRelationMatrix(currentMatrix);
            
            currentMatrix = symmetricClosure(currentMatrix);
            
            cout << "\n변환 후:\n";
            printRelationMatrix(currentMatrix);
            cout << "대칭 관계: " << (isSymmetric(currentMatrix) ? "O" : "X") << "\n";
        }
        
        // 추이 폐포
        if (!transitive) {
            cout << "\n--- 추이 폐포 생성 ---\n";
            cout << "변환 전:\n";
            printRelationMatrix(currentMatrix);
            
            currentMatrix = transitiveClosure(currentMatrix);
            
            cout << "\n변환 후:\n";
            printRelationMatrix(currentMatrix);
            cout << "추이 관계: " << (isTransitive(currentMatrix) ? "O" : "X") << "\n";
        }
        
        // 최종 폐포 후 동치 관계 재판별
        cout << "\n=== 폐포 변환 후 최종 결과 ===\n";
        printRelationMatrix(currentMatrix);
        
        bool finalReflexive = isReflexive(currentMatrix);
        bool finalSymmetric = isSymmetric(currentMatrix);
        bool finalTransitive = isTransitive(currentMatrix);
        
        cout << "\n반사 관계: " << (finalReflexive ? "O" : "X") << "\n";
        cout << "대칭 관계: " << (finalSymmetric ? "O" : "X") << "\n";
        cout << "추이 관계: " << (finalTransitive ? "O" : "X") << "\n";
        
        if (finalReflexive && finalSymmetric && finalTransitive) {
            cout << "\n✓ 폐포 변환 후 동치 관계가 되었습니다!\n";
            printEquivalenceClasses(currentMatrix);
        } else {
            cout << "\n✗ 폐포 변환 후에도 동치 관계가 아닙니다.\n";
        }
    }
    
    // ========== 추가 기능: 관계의 합성 ==========
    analyzeComposition(matrix);
    
    cout << "\n프로그램을 종료합니다.\n";
    return 0;
}

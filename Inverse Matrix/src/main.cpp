#include <vector>
#include <iostream>
using namespace std;

using Matrix = vector<vector<double> >;

extern Matrix Input_vector(int N);
extern int Print_vector(const Matrix &v, int N);
extern double determinant(const Matrix& matrix);
extern Matrix inverseMatrix(const Matrix& matrix);
extern Matrix inverseMatrixGaussJordan(const Matrix& matrix);

int main(){
    int N;
    cout << "행렬의 크기 N을 입력: ";
    cin >> N;
    cout << "NxN 행렬의 원소들을 입력하세요:\n";
    Matrix matrix = Input_vector(N);
    
    cout << "입력된 행렬:\n";
    Print_vector(matrix, N);
    
    Matrix inverse1, inverse2;
    bool method1Success = false, method2Success = false;
    
    cout << "=== 방법 1: 행렬식을 이용한 역행렬 계산 ===\n";
    try {
        double det = determinant(matrix);
        cout << "행렬식: " << det << "\n";
        
        inverse1 = inverseMatrix(matrix);
        cout << "\n행렬식 방법 역행렬:\n";
        for (const auto& row : inverse1) {
            for (double val : row) {
                cout << val << " ";
            }
            cout << "\n";
        }
        cout << "행렬식 방법 성공!\n";
        method1Success = true;
        
    } catch (const exception& e) {
        cout << "행렬식 방법 오류: " << e.what() << "\n";
    }
    
    cout << "\n=== 방법 2: 가우스-조던 소거법을 이용한 역행렬 계산 ===\n";
    try {
        inverse2 = inverseMatrixGaussJordan(matrix);
        cout << "가우스-조던 방법 역행렬:\n";
        for (const auto& row : inverse2) {
            for (double val : row) {
                cout << val << " ";
            }
            cout << "\n";
        }
        cout << "가우스-조던 방법 성공!\n";
        method2Success = true;
        
    } catch (const std::exception& e) {
        cout << "가우스-조던 방법 오류: " << e.what() << "\n";
    }
    cout << "\n=== 두 방법의 결과 비교 ===\n";
    if (method1Success && method2Success) {
        bool isEqual = true;
        double tolerance = 1e-10;
        double maxDifference = 0.0;
        
        for (int i = 0; i < N && isEqual; i++) {
            for (int j = 0; j < N; j++) {
                double diff = abs(inverse1[i][j] - inverse2[i][j]);
                if (diff > maxDifference) {
                    maxDifference = diff;
                }
                if (diff > tolerance) {
                    isEqual = false;
                    break;
                }
            }
        }
        
        if (isEqual) {
            cout << "✓ 두 방법의 결과가 일치합니다!\n";
            cout << "최대 오차: " << maxDifference << "\n";
        } else {
            cout << "✗ 두 방법의 결과가 다릅니다.\n";
            cout << "최대 오차: " << maxDifference << " (허용오차: " << tolerance << ")\n";
        }
    }
    cout << "\n역행렬 계산 테스트가 완료되었습니다!" << "\n";
    
    return 0;
}
#include <iostream>
#include <cmath>
#include <vector>
#include <stdexcept>

using Matrix = std::vector<std::vector<double> >;

Matrix getMinor(const Matrix& matrix, int excludeRow, int excludeCol) {
    int n = matrix.size();
    Matrix minor(n - 1, std::vector<double>(n - 1));
    
    int minorRow = 0;
    for (int i = 0; i < n; i++) {
        if (i == excludeRow) continue;
        
        int minorCol = 0;
        for (int j = 0; j < n; j++) {
            if (j == excludeCol) continue;
            
            minor[minorRow][minorCol] = matrix[i][j];
            minorCol++;
        }
        minorRow++;
    }
    return minor;
}

double determinant(const Matrix& matrix) {
    int n = matrix.size();
    if (n == 1) {
        return matrix[0][0];
    }
    if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    double det = 0.0;
    for (int j = 0; j < n; j++) {
        Matrix minor = getMinor(matrix, 0, j);
        double cofactorValue = ((0 + j) % 2 == 0 ? 1 : -1) * determinant(minor);
        det += matrix[0][j] * cofactorValue;
    }
    
    return det;
}

double cofactor(const Matrix& matrix, int row, int col) {
    Matrix minor = getMinor(matrix, row, col);
    double minorDet = determinant(minor);
    return ((row + col) % 2 == 0 ? 1 : -1) * minorDet;
}

Matrix adjugate(const Matrix& matrix) {
    int n = matrix.size();
    Matrix adj(n, std::vector<double>(n));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[j][i] = cofactor(matrix, i, j);
        }
    }
    
    return adj;
}
Matrix inverseMatrix(const Matrix& matrix) {
    double det = determinant(matrix);
    if (std::abs(det) < 1e-10) {
        throw std::runtime_error("역행렬을 구할 수 없습니다. 행렬식이 0입니다.");
    }
    
    int n = matrix.size();
    if (n == 1) {
        return {{1.0 / matrix[0][0]}};
    }
    
    Matrix adj = adjugate(matrix);
    Matrix inverse(n, std::vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inverse[i][j] = adj[i][j] / det;
        }
    }
    
    return inverse;
}

Matrix inverseMatrixGaussJordan(const Matrix& matrix) {
    int n = matrix.size();
    Matrix augmented(n, std::vector<double>(2 * n, 0.0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmented[i][j] = matrix[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        augmented[i][i + n] = 1.0;
    }
    
    for (int i = 0; i < n; i++) {
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (std::abs(augmented[k][i]) > std::abs(augmented[maxRow][i])) {
                maxRow = k;
            }
        }
        if (std::abs(augmented[maxRow][i]) < 1e-10) {
            throw std::runtime_error("가우스-조던 소거법: 역행렬을 구할 수 없습니다. 행렬이 특이행렬입니다.");
        }
        
        if (maxRow != i) {
            std::swap(augmented[i], augmented[maxRow]);
        }
        
        double pivot = augmented[i][i];
        for (int j = 0; j < 2 * n; j++) {
            augmented[i][j] /= pivot;
        }
        
        for (int k = 0; k < n; k++) {
            if (k != i && std::abs(augmented[k][i]) > 1e-10) {
                double factor = augmented[k][i];
                for (int j = 0; j < 2 * n; j++) {
                    augmented[k][j] -= factor * augmented[i][j];
                }
            }
        }
    }
    
    Matrix inverse(n, std::vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inverse[i][j] = augmented[i][j + n];
        }
    }
    
    return inverse;
}
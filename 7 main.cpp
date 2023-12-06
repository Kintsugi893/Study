#include "matrix_operations.hpp"
#include <iostream>

int main() {
    int** matrix = nullptr;
    int n = 0;

    MatrixOperations::readMatrix("input.txt", matrix, n);

    int firstRow, secondRow;
    if (MatrixOperations::findDuplicateRows(matrix, n, firstRow, secondRow)) {
        int largestPrime = MatrixOperations::findLargestPrime(matrix, n);
        MatrixOperations::replaceMinInColumnsWithPrime(matrix, n, largestPrime);
        MatrixOperations::writeMatrix("output.txt", matrix, n);
        std::cout << "Программа выполнена успешно !" << std::endl;
    }

    // Освобождаем память после использования динамического массива
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}

#ifndef MATRIX_OPERATIONS_HPP
#define MATRIX_OPERATIONS_HPP

namespace MatrixOperations {
    void readMatrix(const char* filename, int**& matrix, int& n);
    bool findDuplicateRows(int** matrix, int n, int& firstRow, int& secondRow);
    int findLargestPrime(int** matrix, int n);
    void replaceMinInColumnsWithPrime(int** matrix, int n, int prime);
    void writeMatrix(const char* filename, int** matrix, int n);
}

#endif
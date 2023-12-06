#include "matrix_operations.hpp"
#include <iostream>
#include <fstream>

namespace MatrixOperations {
    // Реализация вычисления квадратного корня
    double mySqrt(int num) {
        if (num <= 1) return 0;
        double x = num;
        double y = (x + num / x) / 2;
        while (y < x) {
            x = y;
            y = (x + num / x) / 2;
        }
        return x;
    }

    void readMatrix(const char* filename, int**& matrix, int& n) {
        std::ifstream input(filename);
        input >> n;
        matrix = new int* [n];
        for (int i = 0; i < n; ++i) {
            matrix[i] = new int[n];
            for (int j = 0; j < n; ++j) {
                input >> matrix[i][j];
            }
        }
        input.close();
    }

    bool findDuplicateRows(int** matrix, int n, int& firstRow, int& secondRow) {
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                bool duplicate = true;
                for (int k = 0; k < n; ++k) {
                    if (matrix[i][k] != matrix[j][k]) {
                        duplicate = false;
                        break;
                    }
                }
                if (duplicate) {
                    firstRow = i;
                    secondRow = j;
                    return true;
                }
            }
        }
        return false;
    }

    bool isPrime(int num) {
        if (num <= 1) return false;
        int sqrtNum = mySqrt(num);
        for (int i = 2; i <= sqrtNum; ++i) {
            if (num % i == 0) {
                return false;
            }
        }
        return true;
    }

    int findLargestPrime(int** matrix, int n) {
        int largestPrime = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (isPrime(matrix[i][j]) && matrix[i][j] > largestPrime) {
                    largestPrime = matrix[i][j];
                }
            }
        }
        return largestPrime;
    }

    void replaceMinInColumnsWithPrime(int** matrix, int n, int prime) {
        for (int j = 0; j < n; ++j) {
            int minInColumn = matrix[0][j];
            for (int i = 1; i < n; ++i) {
                if (matrix[i][j] < minInColumn) {
                    minInColumn = matrix[i][j];
                }
            }
            for (int i = 0; i < n; ++i) {
                if (matrix[i][j] == minInColumn) {
                    matrix[i][j] = prime;
                }
            }
        }
    }

    void writeMatrix(const char* filename, int** matrix, int n) {
        std::ofstream output(filename);
        //output << n << std::endl;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    output << matrix[i][j] << " ";
                }
                output << std::endl;
            }
        output.close();
    }
}

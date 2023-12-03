#include <iostream>
#include <random>
#include <fstream>
#include "Stopwatch.h"
#include "MatrixMultiplication.h"
#include <algorithm>

using namespace std;

MatrixMultiplication::MatrixMultiplication(int n, int m, int k, int max)
{
    this->n = n;
    this->m = m;
    this->k = k;
    this->max = max;

    matrix1.resize(n);
    for (int i = 0; i < n; ++i) {
        matrix1[i].resize(m);
    }

    matrix2.resize(m);
    for (int i = 0; i < m; ++i) {
        matrix2[i].resize(k);
    }

    resultMatrix.resize(n);
    for (int i = 0; i < n; ++i)
    {
        resultMatrix[i].resize(k);
    }

}

void MatrixMultiplication::fillMatrixRandomly()
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            matrix1[i][j] = rand() % max;
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < k; ++j) {
            matrix2[i][j] = rand() % max;
        }
    }
}

void MatrixMultiplication::multiply() {
    for (int i = 0; i < this->n; ++i) {
        for (int j = 0; j < this->k; ++j) {
            for (int l = 0; l < this->m; ++l) {
                resultMatrix[i][j] += matrix1[i][l] * matrix2[l][j];
            }
        }
    }
}

void MatrixMultiplication::print(vector <vector<int>> matrix) {
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

long MatrixMultiplication::measureTimeForMultiplication() {
    Stopwatch stopwatch;

    stopwatch.start();

    this->multiply();

    auto elapsedTime = stopwatch.stop();

    return elapsedTime.count();
}

void MatrixMultiplication::writeInFile(vector <vector<int>> matrix, ofstream& fout) {
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            fout << matrix[i][j] << " ";
        }
        fout << "\n";
    }
}

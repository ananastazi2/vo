#pragma once
#include <vector>
using namespace std;

class MatrixMultiplication
{
public:
    int n, m, k, max;
    vector <vector<int>> matrix1, matrix2, resultMatrix;

    MatrixMultiplication(int n, int m, int k, int max);

    void fillMatrixRandomly();

    void multiply();

    void print(vector <vector<int>> matrix);

    long measureTimeForMultiplication();

    void writeInFile(vector <vector<int>> matrix, ofstream& fout);
};
#include <iostream>
#include "t4.h"
#include "Stopwatch.h"
#include "MatrixMultiplication.h"
#include <thread>
#include <limits>
#include <functional>
#include <omp.h>

using namespace std;

FourthTask::FourthTask(int n, int m, int k)
{
    this->n = n;
    this->m = m;
    this->k = k;

    matrix1.resize(n);
    for (int i = 0; i < n; ++i) {
        matrix1[i].resize(m);
    }

    matrix2.resize(m);
    for (int i = 0; i < m; ++i) {
        matrix2[i].resize(k);
    }

    resultMatrix.resize(n);
    for (int i = 0; i < n; ++i) {
        resultMatrix[i].resize(k);
        for (int j = 0; j < k; ++j) {
            resultMatrix[i][j] = 0;
        }
    }
}

bool FourthTask::OpenFileForReading()
{
    fin1.open(path);
    fin2.open(path);

    if (!fin1.is_open() || !fin2.is_open())
    {
        cout << "Cannot open the file for reading" << endl;
        fin1.close();
        fin2.close();
        return false;
    }
}

ifstream& FourthTask::GotoLine(ifstream& file, unsigned int num) {
    file.seekg(ios::beg);
    for (int i = 0; i < (num - 1); ++i) {
        file.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return file;
}

void FourthTask::ReadMatrix(ifstream& file, vector<vector<int>>& matrix)
{
    int element = 0;

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[0].size(); ++j) {
            file >> element;
            matrix[i][j] = element;
        }
    }
}

void FourthTask::ReadInputMatrices() {
    int i, numOfInputMatricies = 2;
    omp_set_num_threads(numOfInputMatricies);

#pragma omp parallel sections
    { 
#pragma omp section
        {
            GotoLine(fin1, 2);
            ReadMatrix(fin1, matrix1);
        }

#pragma omp section
        {
            GotoLine(fin2, n + 3);
            ReadMatrix(fin2, matrix2);
        }
    }
}

void FourthTask::multiplyMatrixFromStartPoint(int start, int end)
{
    for (int i = start; i < end; ++i) {
        for (int j = 0; j < k; ++j) {
            for (int l = 0; l < m; ++l) {
                resultMatrix[i][j] += matrix1[i][l] * matrix2[l][j];
            }
        }
    }
}

void FourthTask::ParallelNaiveAlgorithm()
{
    ReadInputMatrices();

    int numOfSections = 5;
    int step = n / numOfSections;
    vector<int> sectionsStart(numOfSections);

    sectionsStart[0] = 0;
    for (int i = 1; i < numOfSections; ++i) {
        sectionsStart[i] += step;
    }

#pragma omp parallel sections
    {
#pragma omp section
        {
            multiplyMatrixFromStartPoint(sectionsStart[0], sectionsStart[1]);
        }
#pragma omp section
        {
            multiplyMatrixFromStartPoint(sectionsStart[1], sectionsStart[2]);
        }
#pragma omp section
        {
            multiplyMatrixFromStartPoint(sectionsStart[2], sectionsStart[3]);
        }
#pragma omp section
        {
            multiplyMatrixFromStartPoint(sectionsStart[3], sectionsStart[4]);
        }
#pragma omp section
        {
            multiplyMatrixFromStartPoint(sectionsStart[4], n);
        }
    }
}

int FourthTask::measureTimeForAlgo()
{
    double startTime = omp_get_wtime();

    ParallelNaiveAlgorithm();

    double endTime = omp_get_wtime();

    double elapsedTimeMilliseconds = (endTime - startTime) * 1000.0;

    return static_cast<int>(elapsedTimeMilliseconds);
}

bool FourthTask::checkResultMatrix() {
    int matrixElementFromFile;

    GotoLine(fin1, (n + m + 4));

    for (int i = 0; i < resultMatrix.size(); ++i) {
        for (int j = 0; j < resultMatrix[0].size(); ++j) {
            fin1 >> matrixElementFromFile;
            if (resultMatrix[i][j] != matrixElementFromFile)
            {
                cout << "Dot product doesn't match at resultMatrix[" << i << "][" << j << "]";
                return false;
            }
        }
    }

    cout << endl << "Matricies match" << endl;

    return true;
}

void FourthTask::closeFile()
{
    fin1.close();
    fin2.close();
}
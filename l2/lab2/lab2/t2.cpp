#include "t2.h"
#include <iostream>
#include <fstream> 
#include <string>
#include "MatrixMultiplication.h"
#include <omp.h>

using namespace std;

SecondTask::SecondTask(int n, int m, int k, int maxValue) {
    this->n = n;
    this->m = m;
    this->k = k;
    this->maxValue = maxValue;
}


bool SecondTask::OpenFileForWriting()
{
    fout.open(path);

    if (!fout.is_open())
    {
        cout << "Cannot open the file for writing" << endl;
        fout.close();
        return false;
    }
}


void SecondTask::checkOpenMPSupport() 
{
    #ifdef _OPENMP
        std::cout << endl << "OpenMP is supported" << std::endl;
    #if _OPENMP >= 202107 // OpenMP 5.1
        std::cout << "OpenMP version 5.1 or higher is available" << std::endl;
    #elif _OPENMP >= 201811 // OpenMP 5.0
        std::cout << "OpenMP version 5.0 is available" << std::endl;
    #elif _OPENMP >= 201511 // OpenMP 4.5
        std::cout << "OpenMP version 4.5 is available" << std::endl;
    #elif _OPENMP >= 201307 // OpenMP 4.0
        std::cout << "OpenMP version 4.0 is available" << std::endl;
    #elif _OPENMP >= 201111 // OpenMP 3.1
        std::cout << "OpenMP version 3.1 is available" << std::endl;
    #elif _OPENMP >= 200807 // OpenMP 3.0
        std::cout << "OpenMP version 3.0 is available" << std::endl;
    #elif _OPENMP >= 200505 // OpenMP 2.5
        std::cout << "OpenMP version 2.5 is available" << std::endl;
    #elif _OPENMP >= 199810 // OpenMP 4.5
        std::cout << "OpenMP version 2.0 is available" << std::endl;
    #else
        std::cout << "OpenMP version is unknown" << std::endl;
    #endif
    #else
        std::cout << "OpenMP is not supported" << std::endl;
    #endif
}

void SecondTask::IterativeNaiveAlgorithm()
{
    MatrixMultiplication test(n, m, k, maxValue);

    test.fillMatrixRandomly();

    fout << "Matrix 1:\n";
    test.writeInFile(test.matrix1, fout);

    fout << "Matrix 2:\n";
    test.writeInFile(test.matrix2, fout);

    test.multiply();

    fout << "Result matrix:\n";
    test.writeInFile(test.resultMatrix, fout);
}

int SecondTask::measureTimeForAlgo() {
    double startTime = omp_get_wtime();

    checkOpenMPSupport();
    IterativeNaiveAlgorithm();

    double endTime = omp_get_wtime();

    double elapsedTimeMilliseconds = (endTime - startTime) * 1000.0;

    return static_cast<int>(elapsedTimeMilliseconds);
}

void SecondTask::closeFile()
{
    fout.close();
}
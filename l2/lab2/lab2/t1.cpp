#include <iostream>
#include "t1.h"
#include "Stopwatch.h"
#include "MatrixMultiplication.h"

using namespace std;

FirstTask::FirstTask(int n, int m, int k, int maxValue)
{
    this->n = n;
    this->m = m;
    this->k = k;
    this->maxValue = maxValue;
}

bool FirstTask::OpenFileForWriting()
{
    fout.open(path);

    if (!fout.is_open())
    {
        cout << "Cannot open the file for writing" << endl;
        fout.close();
        return false;
    }
}

void FirstTask::IterativeNaiveAlgorithm()
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

int FirstTask::measureTimeForAlgo() {
    Stopwatch stopwatch;

    stopwatch.start();

    IterativeNaiveAlgorithm();

    auto elapsedTime = stopwatch.stop();

    return elapsedTime.count();
}

void FirstTask::closeFile()
{
    fout.close();
}

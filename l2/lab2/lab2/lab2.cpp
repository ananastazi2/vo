// t1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>
#include <fstream>
#include "Stopwatch.h"
#include "MatrixMultiplication.h"
#include "t1.h"
#include "t2.h"
#include "t3.h"
#include "t4.h"
#include <algorithm>

using namespace std;

class RunProgram
{
private:
    int n, m, k;
    int maxValue;
    bool success;
public:
    RunProgram()
    {
        do {
            cout << "Input matrix dimension n, m, k: ";
            cin >> this->n >> this->m >> this->k;

            cout << "Input max value of matrix: ";
            cin >> this->maxValue;
        } while (!ValidatorForDimensions());
    }

    bool ValidatorForDimensions()
    {
        if (n <= 0 || m <= 0 || k <= 0)
        {
            cout << "Wrong n, m, k" << endl;
            return false;
        }
    }

    bool runFirstTask() {
        FirstTask test = FirstTask(n, m, k, maxValue);

        success = test.OpenFileForWriting();
        if (!success) return false;

        cout << "Time taken by iterative naive algorithm (measured by clock): " << test.measureTimeForAlgo() << " millisec" << endl;

        test.closeFile();
    }

    bool runSecondTask() {
        SecondTask test2 = SecondTask(n, m, k, maxValue);

        success = test2.OpenFileForWriting();
        if (!success) return false;

        cout << endl << "Time taken by iterative naive algorithm (measured by OpenMP functions): " << test2.measureTimeForAlgo() << " millisec" << endl;

        test2.closeFile();
        return true;
    }

    bool runThirdTask() {
        ThirdTask test3 = ThirdTask(n, m, k);

        success = test3.OpenFileForReading();
        if (!success) return false;

        cout << endl << "Time taken by parallel naive algorithm (measured by OpenMP functions): " << test3.measureTimeForAlgo() << " millisec" << endl;
        test3.checkResultMatrix();

        test3.closeFile();
        return true;
    }

    bool runFourthTask() {
        FourthTask test4 = FourthTask(n, m, k);

        success = test4.OpenFileForReading();
        if (!success) return false;

        cout << endl << "Time taken by parallel naive algorithm with sections (measured by OpenMP functions): " << test4.measureTimeForAlgo() << " millisec" << endl;
        test4.checkResultMatrix();

        test4.closeFile();
        return true;
    }
};

int main()
{
    srand(time(NULL));

    RunProgram go = RunProgram();

    if (/*!go.runFirstTask() || */ !go.runSecondTask() || !go.runThirdTask() || !go.runFourthTask()) return 0;

    return 0;
}

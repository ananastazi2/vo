#pragma once
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class SecondTask {
private:
	int n, m, k, maxValue;
	string path = "GeneratedMatrix.txt";
	ofstream fout;
public:
	SecondTask(int n, int m, int k, int maxValue);
	bool OpenFileForWriting();
	void checkOpenMPSupport();
	void IterativeNaiveAlgorithm();
	int measureTimeForAlgo();
	void closeFile();
};
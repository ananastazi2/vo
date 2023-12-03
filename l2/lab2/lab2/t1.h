#pragma once
#include <fstream>
using namespace std;

class FirstTask {
private:
	int n, m, k, maxValue;
	string path = "GeneratedMatrix.txt";
	ofstream fout;
public:
	FirstTask(int n, int m, int k, int maxValue);
	bool OpenFileForWriting();
	void IterativeNaiveAlgorithm();
	int measureTimeForAlgo();
	void closeFile();
};
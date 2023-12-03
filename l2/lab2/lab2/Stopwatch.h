#pragma once
#include <chrono>
using namespace std::chrono;

class Stopwatch {
private:
	time_point<steady_clock> time;
	bool isRunning = false;

public:
	void start();
	milliseconds stop();
};
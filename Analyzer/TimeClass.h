//Time class that currently only has timer functions. Used for calculate program execution time
#pragma once
#include <chrono> 
#include <iostream>
#include <fstream>
using namespace std;

class TimeClass {
public:
	void TimerStart();
    void TimerStop();
    double TimerResult();
private:
    chrono::high_resolution_clock::time_point TimeStart;
    chrono::high_resolution_clock::time_point TimeEnd;
};
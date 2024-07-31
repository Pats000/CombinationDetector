#include "TimeClass.h"
//Function to start timer
void TimeClass::TimerStart() {
	TimeStart = chrono::high_resolution_clock::now();
}
//Function to stop timer
void TimeClass::TimerStop() {
	TimeEnd = chrono::high_resolution_clock::now();
}
//Function that returns the time timer took.
double TimeClass::TimerResult(){
	chrono::duration<double> TimeTaken = TimeEnd - TimeStart;
	return TimeTaken.count();
}
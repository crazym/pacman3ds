/*
 * Timer.h
 *
 *  Created on: 2010-08-07
 *      Author: sid
 */

#ifndef TIMER_H_
#define TIMER_H_
#include <ctime>
#include <sstream>

using namespace std;

class Timer{


public:
	Timer(string);
	~Timer();

	void drawTimer();
	void startTimer();
	void stopTimer();
	int getTimeElapsed();
	int getTimeLeft();
	void startCountDown(int);
	string timer_string;
	bool timerIsOn;

private:
	string runTimeElapsed(time_t);
	string runTimeLeft(time_t);
	string runCountDown();
	time_t currentTime;
	time_t startTime;
	time_t countDownTo;
	string initTimerString;
};

#endif /* TIMER_H_ */

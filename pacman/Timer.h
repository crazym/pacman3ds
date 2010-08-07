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

	Timer();
	~Timer();

	void drawTimer();
	void startTimer();
	void stopTimer();
	string timer_string;

private:
	string runTimer(time_t);
	time_t currentTime;
	time_t startTime;
	bool timerIsOn;
};

#endif /* TIMER_H_ */

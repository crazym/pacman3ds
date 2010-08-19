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
	void drawLife(int);
	void startTimer();
	void stopTimer();
	int getTimeElapsed();
	int getTimeLeft();
	void startCountDown(int);
	string timer_string;
	bool timerIsOn;
	bool timerIsPaused;
	bool countDownIsOn;
	void pause();
	void resume();
	void drawGameOver(int);
	void drawScore(long int);

private:

	string runTime(time_t);
	string runCountDown();
	time_t currentTime;
	time_t startTime;
	time_t countDownTo;
	time_t pauseTime;
	string initTimerString;

};

#endif /* TIMER_H_ */

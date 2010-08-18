/*
 * Timer.cpp
 *
 *  Created on: 2010-08-07
 *      Author: sid
 */

#include "Timer.h"
#include "Common.h"
#include <ctime>
#include <iostream>
#include <sstream>

#include "stdio.h"
#include "string.h"
#include <GL/glut.h>

using namespace std;

void drawString(string);


Timer::Timer(string init){

	time(&currentTime);
	timerIsOn = false;
	countDownIsOn = false;
	initTimerString = init;
	timerIsPaused = 0;
	//l_string = ;

}

void Timer::startTimer(){

	timerIsOn = true;
	timerIsPaused = false;
	startTime = time(NULL);
	pauseTime = 0;
	cout << "starting timer .." << endl;

}

void Timer::startCountDown(int countDown){

	cout << "starting countdown .." << endl;
	countDownIsOn = true;
	//if(getTimeLeft()) countDown += getTimeLeft();
	
	//reset previous countdowns
	countDownTo = 0;
	countDownTo = time(NULL) + countDown;

}



string Timer::runCountDown(){

	time_t count = countDownTo - time(NULL);
	return runTime(count);

}


void Timer::drawTimer(){

		if(countDownIsOn){

			if(!timerIsPaused){
							
				timer_string = runCountDown();
				drawString(timer_string);
			}

			if(getTimeLeft() <= 0) countDownIsOn = false;
			
		

		}
		else if(timerIsOn){

			if(timerIsPaused){

			//display paused
				//drawString("paused");
				drawString(timer_string);
			}
			else{

				//get current time
				currentTime = time(NULL);

				//get timer string
				timer_string = Timer::runTime(currentTime - startTime);
				drawString(timer_string);
			}

		}
		else{
			
			timer_string = initTimerString;
			drawString(timer_string);
		}
}

void Timer::drawLife(int life)
{
	string l_string;
	stringstream out;
	out << "Life: " << life;
	l_string = out.str();
	
	drawString(l_string);
	//life=3;
}

void Timer::drawScore(long int score)
{
	string s;
	stringstream out;
	out << "Score: " << score;
	s = out.str();
	
	drawString(s);
}

void Timer::drawGameOver(int i){
	string s;
	string s1;
	string s2;
	stringstream out;

	if(i==0){
		out << "GAME OVER";
		s = out.str();
		drawString(s);
	}
	if(i==1){
		out << "PRESS 'm' key for Main Menu";
		s1 = out.str();
		drawString(s1);
	}
	if(i==2){
		out << "PRESS 'Esc' key to quit";
		s2 = out.str();
		drawString(s2);
	}
}


void Timer::stopTimer(){

	timerIsOn = false;
	drawTimer();


}

string Timer::runTime(time_t seconds){

	int years;
	int months;
	int days;
	int hours;
	int minutes;
	int secs;
	
	ostringstream timestamp;

		years = seconds/31556926;
		secs = seconds%31556926;

		months = secs/2629743;
		secs = secs%2629743;

		days = secs/86400;
		secs = secs%86400;

		hours = secs/3600;
		secs = secs%3600;

		minutes = secs/60;
		secs = secs%60;

		if(years){

			timestamp << years << " : ";
		}
		else if(months){

			timestamp << months << " : ";
		}
		else if(days){

			timestamp << days << " : ";
		}
		else if(hours){

			timestamp << hours << " : ";
		}
		else{

			timestamp << minutes << " : " << secs << endl;
		}

		//cout << timestamp.str();
		return timestamp.str();

}

int Timer::getTimeElapsed(){

	return time(NULL) - startTime;
}

int Timer::getTimeLeft(){

	return countDownTo - time(NULL);

}

Timer::~Timer(){}

void Timer::pause(){

	if(!timerIsPaused){

		timerIsPaused = 1;
		//store time difference
		currentTime = time(NULL);
		
	}
}

void Timer::resume(){

	if(timerIsPaused) timerIsPaused = 0;

	//calculate pause time
	pauseTime = time(NULL) - currentTime;
	
	//update start time to compensate for pause time
	startTime += pauseTime;

	//update countDownTo to compensate for pause time
	countDownTo += pauseTime;

}



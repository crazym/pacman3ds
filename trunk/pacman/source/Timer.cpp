/*
 * Timer.cpp
 *
 *  Created on: 2010-08-07
 *      Author: sid
 */

#include "Timer.h"
#include <ctime>
#include <iostream>
#include <sstream>

#include "stdio.h"
#include "string.h"
#include <GL/glut.h>

using namespace std;

void print_stroke_string(void* font, char* s);
void print_bitmap_string();
void drawString(string);

Timer::Timer(string init){

	time(&currentTime);
	timerIsOn = false;
	countDownIsOn = false;
	initTimerString = init;
	timerIsPaused = 0;

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
				drawString("paused");
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



//wrapper for drwaing string
//makes print_stroke_string easier to use
void drawString(string timeString){

		char * drawString;
		drawString = new char[timeString.length()+1];
		strcpy(drawString,timeString.c_str());

		print_stroke_string(GLUT_STROKE_ROMAN,drawString);
		//print_bitmap_string(GLUT_BITMAP_HELVETICA_18,drawString);

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


//functions lifed off the redbook.
void print_stroke_string(void* font, char* s){
   if (s && strlen(s)) {
      while (*s) {
         glutStrokeCharacter(font, *s);
         s++;
      }
   }
   glutPostRedisplay();
}

void print_bitmap_string (void* font, char *string)
{
	int x = 5;
	int y = 5;

	int len, i;
	glRasterPos2f(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++)
	{
	 glutBitmapCharacter(font, string[i]);
	}

	glutPostRedisplay();
}

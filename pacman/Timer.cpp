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

Timer::Timer(){

	time(&currentTime);
	timerIsOn = false;

}

void Timer::startTimer(){

	timerIsOn = true;
	startTime = time(NULL);
	cout << "starting timer .." << endl;

}

void print_stroke_string(void* font, char* s){
   if (s && strlen(s)) {
      while (*s) {
         glutStrokeCharacter(font, *s);
         s++;
      }
   }
   glutPostRedisplay();
}

void Timer::drawTimer(){

		char* timerstring;
		if(timerIsOn){

			//get current time
			currentTime = time(NULL);
			//get timer string
			timer_string = Timer::runTimer(currentTime - startTime);

			//copy timer_string into char array
			timerstring = new char[timer_string.length()+1];
			strcpy(timerstring,timer_string.c_str());

	//draw timer string
	print_stroke_string(GLUT_STROKE_ROMAN,timerstring);

	}
	else{

		timer_string = "PRESS START";
		timerstring = new char[timer_string.length()+1];
		strcpy(timerstring,timer_string.c_str());

		print_stroke_string(GLUT_STROKE_ROMAN,timerstring);
	}
}

void Timer::stopTimer(){

	timerIsOn = false;

}

string Timer::runTimer(time_t seconds){

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
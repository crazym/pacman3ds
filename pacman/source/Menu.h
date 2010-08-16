/*

Menu

*/

#ifndef _MENU_H_
#define _MENU_H_

#include <sstream>

using namespace std;

class Menu{

	public:

		Menu();
		~Menu();
	
		void printMenu(char);

	private:

		void print_bitmap_string (void* font, char *string);
		void print_stroke_string(void* font, char* s);
		void drawString(string timeString);
		ostringstream MenuString;
};
#endif

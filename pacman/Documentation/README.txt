README.txt for Pacman 3D project of COMP 371 Computer Graphics course.
Copyright 2010 Concordia University. All rights reserved.

By:	Carlos Pinto (Team Leader)
	ID: 9343911

	Bronson Zgeb
	ID: 9402268

	Andrew Wolczak
	ID: 9095543

	Allan Tran
	ID: 9099824

	Siddhartha Kattoju
	ID: 9209905

===========================================================

This README file contains the used keys and their functions in the game, 
the directory structure of the files of the program and 
brief compilation instructions for multiple platforms.

===========================================================
USED KEYS

-Function Keys
F1  : toggle between orthogonal and perspective mode of viewing.
F2  : toggle between continuous rotation about y-axis and stop rotation
F3  : zoom out
F4  : zoom in
F5  : Light 1 on/off
F6  : Light 2 on/off
F7  : Light 3 on/off
F8  : Light 4 on/off
F9  : All Lights on/off
F10: reset view in case your view parameters get out of control.
F11: Ambient Light on/off

-Arrow Keys
Up: rotate view about x-axis
Down: rotate view about  x-axis
Left: rotate about z-axis
Right: rotate about z-axis

-Others
[: roll left
]: roll right

W : move forward
S : move backward
A : strafe left
D : strafe right

, : lower camera
. : raise camera

1: Pacman cam
2: Ghost1 cam
3: Ghost2 cam
4: Ghost3 cam
5: Ghost4 cam
6: Light1 cam
7: Light2 cam
8: Light3 cam
9: Light4 cam
0: Initial Cam

ESC: Exit

============================================================
DIRECTORY STRUCTURE

**** NOTE ****** Directory structure is not yet in place.*******************

The directory structure of this program consists of two folders. All of the header and
source files are inside the Source folder and the textures files are inside the Data folder.

============================================================
COMPILATION INSTRUCTIONS

-Windows:
1) Open Visual C++.
2) Create a new C++ project of the type "Win32 Console Application".
3) Choose "Empty Project" and click "Finish".
4) Add source and header files into "Source Files" and "Header Files" folders respectively.
5) In Project menu, choose Properties.
6) Under Configuration Properties, select Linker --> Input.
7) In the Configuration dropdown, select All Configurations.
8) In the Additional Dependencies field, enter "glu32.lib opengl32.lib glut32.lib". Then click OK.
9) Build and run.

-Mac OS X:
1) Create a new cocoa application in Xcode.  
2) Add OpenGL and GLUT frameworks to the project.  
3) Remove the default main.m file.  
4) Add all the files in source to "Classes" group.  
5) Add all the files in data/textures to "Resources" group. 
6) Build and Run.

-Linux:
1) Open a terminal and navigate to the project directory.
2) Type "make" in the root project folder.  
3) The project builds into a build directory.  
4) Cd to the build directory.
5) Type "./pacman3d" to run the project.

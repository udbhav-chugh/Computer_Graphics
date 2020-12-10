Name: Udbhav Chugh
Roll Number: 170101081

Graphics Lab Assignment 3: Rendering Spheres.

Important features:
-main.cpp is the main file. It includes helper1.h and helper2.h which have helper functions.
- The code displays an enclosed room scene with a light source in the top right corner of the room(indicated by the yellowish orange spot).
- The shadows for all the spheres are visible based on the light coming from the ligh source.
- The leftmost sphere is the is the plastic sphere.
- The second sphere from the left is the textured sphere where a check-style texture is added to the sphere.
- The sphere which is a little above the rest and has whitish grey color is the glossy sphere with specular light and reflective surface, where you can see the reflection of all other spheres.
- Additionally the rightmost sphere has some glossiness and specular lighting without reflecting feature. For reflective surface see the sphere mentioned above.

Steps to run the code:

Compile:
g++ -std=c++11 main.cpp -lGL -lglut -lGLU

Execute:
./a.out

Contact if any issue faced in running the code.
udbha170123055@iitg.ac.in
8402028442


============================
============================
Note: There is another file try.cpp in optionaltry folder. It is not part of main evaluation.
There I was trying out displaying the optional glass sphere so the rightmost sphere shows some features of glass in that file. So for the additional part, you can look at that file. Rest of the code is similar to main but it doesnt have the glossy sphere with reflective surface. Instead I have tried getting glass like surface. For main evaluation, refer to main.cpp mentioned above.
For running file for optinal part, go to the optionaltry folder and run the below mentioned command.

Compile:
g++ -std=c++11 try.cpp -lGL -lglut -lGLU

Execute:
./a.out



=========================================
=========================================

Ensure that freeglut, and g++ (preferably 11 or 14 version) is already present in the Linux system or else the code will not compile.

To install freeglut or g++, use the following command:
sudo apt-get update -y
sudo apt-get install -y g++
sudo apt-get install -y freeglut3-dev

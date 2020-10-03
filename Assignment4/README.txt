Name: Udbhav Chugh
Roll Number: 170101081

Graphics Assignment 4: Rotate and zoom 3D model using the mouse (in C++ and OpenGL).

Important features:

- The code displays the 3D mesh of the object file House.obj present in the same folder.
- You can use scroll up and scroll down in mouse to zoom in and zoom out the object.
- You can hold down the left mouse button and drag the cursor in the direction you want to rotate. While dragging ensure to hold the left mouse button down.

Additional feature:
- You can use arrow keys (right, left, up and down keys) to rotate the object and view the 3D object from different angles.
- You can right click and a menu will be displayed. In that menu you can choose color of the house between the original color set, red color, green color or blue color. You can also exit using the menu.

A short demo video for reference:
https://drive.google.com/file/d/1GgbTueiuzPsKPtHqGGFD9_ZWbpq9jkEy/view?usp=sharing

About object file:
- The obj file contains v(Vertex), vn(Vertex Normal) and vt(vertex Texture) information along with the frame information.
- The code extracts vertex, vertext normal and vertex texture information from the obj file and then corresponds them to the frame information in the obj file. For displaying the image vertex and vertex normal are used.

Steps to run the code:

Compile:
g++ -std=c++11 main.cpp -lGL -lglut -lGLU

Execute:
./a.out

To compile one can also run the following command to compile using makefile:
make



=========================================
=========================================

Ensure that freeglut, and g++ (preferably 11 or 14 version) is already present in the Linux system or else the code will not compile.

To install freeglut or g++, use the following command:
sudo apt-get update -y
sudo apt-get install -y g++
sudo apt-get install -y freeglut3-dev

Name: Udbhav Chugh
Roll Number: 170101081

Graphics Assignment 1: Read and display a 3D mesh using C++ and OpenGL.

Important features:

- The code displays the 3D mesh of the object file House.obj present in the same folder.
- You can use arrow keys (right, left, up and down keys) to rotate the object and view the 3D object from different angles.

A short demo video for reference:
https://drive.google.com/file/d/1CbEpQBaDwbe_UHE4cZF8I2lodcUVg10Y/view?usp=sharing

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

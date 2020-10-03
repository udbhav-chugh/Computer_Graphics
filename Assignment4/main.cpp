#include <GL/glut.h>
#include <stdio.h>
#include<string.h>
#include<vector>
using namespace std;
#include "readobjFile.h"

GLfloat angleRight,angleDown;
GLfloat angleRightDifference, angleDownDifference;
GLfloat scale;
bool initial, isMouseDown;

//menu for viewing the house in different colors.
int displayMenu, mainMenu;
int colorSelected;



//update angles of object based on mouse movement
//zoom in and zoom out based on scroll direction
void mouseMovement(int button, int state, int x, int y){

	if (button == 3)
		if (state == GLUT_DOWN)  // Zoom-in
			if (scale < 0.3) 
				scale += 0.0005;
	if (button == 4)
		if (state == GLUT_DOWN)  // Zoom-out
			if (scale > 0.0001) 
				scale -= 0.0005;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){ //set right and down angle difference when left button is pressed 
		isMouseDown = true;
		angleRightDifference = x - angleRight;
		angleDownDifference = y - angleDown;
	}
	else{
		isMouseDown = false;
	}

	glutPostRedisplay();
}

//update right and down rotation coordinates based on mouse movement when left button is down
void mouseMotion(int x, int y)
{
	if (isMouseDown)
	{
		angleRight = x - angleRightDifference;
		angleDown = y - angleDownDifference;

		glutPostRedisplay();
	}
}

//update angles of object based on keyboard
void rotateObject(int key, int x, int y){

	if(key == GLUT_KEY_LEFT)
		angleRight-=1;
	else if(key == GLUT_KEY_RIGHT)
		angleRight+=1;
	else if(key == GLUT_KEY_UP)
		angleDown-=1; 
	else if(key == GLUT_KEY_DOWN)
		angleDown+=1;

	if(angleRight>360)
	  angleRight=0;
	if(angleDown>360)
	  angleDown=0;
	glutPostRedisplay();
}

//reshape object after rotation
void reshapeFunc(int width,int height){
    glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();  
	glViewport(0,0,width,height);
	gluPerspective (60, (GLfloat)width / (GLfloat)height, 1, 1000.0);
	glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();
}

//display menu to choose color
void makeDisplayMenu(int value) {
  colorSelected = value;
  glutPostRedisplay();
}
//menu to exit on choosing exit option
void makeMainMenu(int value) {
	switch(value) 
	{
		case 4: exit(0); break;
	}
}

//intiliasing menu to choose color or exit on right click
void initaliseMenu() {

  displayMenu = glutCreateMenu(makeDisplayMenu);
  glutAddMenuEntry("Original", 0);
  glutAddMenuEntry("Red", 1);
  glutAddMenuEntry("Green", 2);
  glutAddMenuEntry("Blue", 3);

  mainMenu = glutCreateMenu(makeMainMenu);
  glutAddSubMenu("Choose Color", displayMenu);
  glutAddMenuEntry("Exit", 4);
  glutAttachMenu(GLUT_RIGHT_BUTTON); 
}

void displayFunc(){
	if(initial != true){
	    initial = true;
    	initialiseObject();
 	}
 	GLfloat objColor[]={0.5f,0.5f,0.5f,1.f}; 
	GLfloat lightPosition[] = {0,0,1.0, 0.0};

	/* ==== Lighting ==== */
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);  
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objColor);
	switch(colorSelected)
	{
		case 0: glColor3f(0.3f, 0.7f, 0.5f);;break; //original color
		case 1: glColor3f(1.0f, 0.0f, 0.0f);break; //red color
		case 2: glColor3f(0.0f, 1.0f, 0.0f);break; //green color
		case 3: glColor3f(0.0f, 0.0f, 1.0f);break; //blue color

	}
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	/* ==== Lighting ==== */

	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);

	//Material information
	glEnable(GL_COLOR_MATERIAL);
	glClearColor (0.0,0.0,0.0,1.0); 
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(  0.0f, 0.2f, 5.0f,
	0.0f, 0.2f, 4.0f,
	0.0f, 0.2f, 0.0f);

	glPushMatrix();
	//rotate and scale around center(origin)
	glRotatef(angleRight,0,1,0);
	glRotatef(angleDown,1,0,0);
	glScalef(scale,scale,scale);
	glCallList(dataList);
	glPopMatrix();
	glutSwapBuffers();
}

int main(int argc, char** argv){
	
	//intiliase values
	scale = 0.03;
	angleRight = 0;
	angleDown = 0;
	angleRightDifference = 0;
	angleDownDifference = 0;
	initial = false;
	isMouseDown = false;
	
	//create window
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGBA);
	glutInitWindowSize(900,900);
	glutInitWindowPosition(50,50);
	glutCreateWindow("OBJ Loader");

	//add functions
	glutReshapeFunc(reshapeFunc);
	glutDisplayFunc(displayFunc);
	glutMouseFunc(mouseMovement);
	glutMotionFunc(mouseMotion);
	glutSpecialFunc(rotateObject);
	glEnable(GL_DEPTH_TEST);
	initaliseMenu();

	glutMainLoop();
}

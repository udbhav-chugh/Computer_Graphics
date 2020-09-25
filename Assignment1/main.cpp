#include <GL/glut.h>
#include <stdio.h>
#include<string.h>
#include<vector>
using namespace std;
#include "readobjFile.h"

GLfloat angleRight,angleUp;
bool initial;
double millisecondQueue,prevTime,fps,responseTime;

//update angles of object
void rotateObject(int key, int x, int y){

	if(key == GLUT_KEY_LEFT)
		angleRight-=1;
	else if(key == GLUT_KEY_RIGHT)
		angleRight+=1;
	else if(key == GLUT_KEY_UP)
		angleUp+=1; 
	else if(key == GLUT_KEY_DOWN)
		angleUp-=1;

	if(angleRight>360)
	  angleRight=0;
	if(angleUp>360)
	  angleUp=0;
}

//to move object according to updated angles
void redisplayLoop(){
    double currentTime = glutGet(GLUT_ELAPSED_TIME);
    double timeElapsedMs =(currentTime-prevTime);
    millisecondQueue += timeElapsedMs ;
    for(;millisecondQueue >= responseTime; millisecondQueue -= responseTime) 
    {
        glutPostRedisplay();
    }
    prevTime=currentTime;
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
	glScalef(0.03,0.03,0.03);
	glRotatef(angleRight,0,1,0);
	glRotatef(angleUp,1,0,0);
	glCallList(dataList);
	glPopMatrix();
	glutSwapBuffers();
}

int main(int argc, char** argv){
	
	//intiliase values
	millisecondQueue=0;
	prevTime=0;
	fps=60;
	angleRight=90;
	angleUp=0;
	responseTime=(1/fps)*1000;
	initial = false;
	
	//create window
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGBA);
	glutInitWindowSize(900,900);
	glutInitWindowPosition(50,50);
	glutCreateWindow("OBJ Loader");

	//add functions
	glutReshapeFunc(reshapeFunc);
	glutDisplayFunc(displayFunc);
	glutIdleFunc(redisplayLoop);
	glutSpecialFunc(rotateObject);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}

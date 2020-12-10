#include <GL/glut.h>
#include "helper2.h"

//plastic sphere helper
void sphere(void)
{
    glPushMatrix();
    glTranslatef(-100.f, -100.f, -400.f);
    glCallList(MAINSPHERE);
    glPopMatrix();
}

//textured sphere helper
void sphere2(void){
  glEnable(GL_TEXTURE_2D);

  glPushMatrix();
  glTranslatef(-40.f, -110.f, -350.f);

  GLUquadricObj *quadricObj = gluNewQuadric();
  glMatrixMode(GL_MODELVIEW);
  gluQuadricDrawStyle(quadricObj, GLU_FILL);
  glBindTexture(GL_TEXTURE_2D, textureMap);
  gluQuadricTexture(quadricObj, GL_TRUE);
  gluQuadricNormals(quadricObj, GLU_SMOOTH);
  gluSphere(quadricObj, 22, 150, 150);
  glPopMatrix();

  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}

//glossy sphere helper
void sphere3(void)
{
    glPushMatrix();
    glTranslatef(30.f, -100.f, -400.f);
    glCallList(MAINSPHERE);
    glPopMatrix();
}

//glass sphere helper
void sphere4(void)
{
    glPushMatrix();
    glTranslatef(80.f, -110.f, -350.f);
    glCallList(MAINSPHERE);
    glPopMatrix();
}


GLfloat leftwallshadow[4][4];
GLfloat floorshadow[4][4];
GLfloat lightSourcePosition[] = {90.f, 90.f, -320.f, 1.f};
void displayFunc(void){
   /* material properties for objects in scene */
    static GLfloat floorMat[] = {.5f, 1.f, .5f, 1.f};
    static GLfloat leftMat[] = {1.f, 1.f, 1.f, 1.f};
    static GLfloat rightMat[] = {1.f, 1.f, 1.f, 1.f};
    static GLfloat ceilMat[] = {.5f, 1.f, .5f, 1.f};
    static GLfloat backWallMat[] = {1.f, 1.f, 1.f, 1.f};

    static GLfloat sphere1Mat[] = {.8f, 0.f, 0.f, 1.f};
    static GLfloat sphere2Mat[] = {0.f, 0.f, 1.f, 1.f};
    static GLfloat sphere3Mat[] = {.3f, 1.f, .3f, 1.f};
    static GLfloat sphere4Mat[] = {.9f, 1.f, .9f, .2f};

    static GLfloat specularNoneMat[] = { 0.0, 0.0, 0.0, 0.0 };  
    static GLfloat shininessNoneMat[] = { 00.0 };

   	static GLfloat specularMat[] = { 1.0, 1.0, 1.0, 1.0 };  
    static GLfloat shininessMat[] = { 90.0 };

    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    /*
    ** Note: wall verticies are ordered so they are all front facing
    ** this lets me do back face culling to speed things up.
    */
 
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, floorMat);
        /* floor */
    /* make the floor textured */
    // glEnable(GL_TEXTURE_2D);
    /*
    ** Since we want to turn texturing on for floor only, we have to
    ** make floor a separate glBegin()/glEnd() sequence. You can't
    ** turn texturing on and off between begin and end calls
    */
    glBegin(GL_QUADS);
    glNormal3f(0.f, 1.f, 0.f);
    glVertex3f(-150.f, -150.f, -320.f);
    glVertex3f( 150.f, -150.f, -320.f);
    glVertex3f( 150.f, -150.f, -520.f);
    glVertex3f(-150.f, -150.f, -520.f);
    glEnd();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glColor3f(0.f, 0.f, 0.f); /* shadow color */
    glPushMatrix();
    glMultMatrixf((GLfloat *)floorshadow);
    sphere();
    glPopMatrix();

    glPushMatrix();
    glMultMatrixf((GLfloat *)floorshadow);
    sphere2();
    glPopMatrix();

    glPushMatrix();
    glMultMatrixf((GLfloat *)floorshadow);
    sphere3();
    glPopMatrix();

    glPushMatrix();
    glMultMatrixf((GLfloat *)floorshadow);
    sphere4();
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    /* walls */
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, leftMat);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 1, 0);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glBegin(GL_QUADS);
    /* left wall */
    glNormal3f(1.f, 0.f, 0.f);
    glVertex3f(-150.f, -150.f, -320.f);
    glVertex3f(-150.f, -150.f, -520.f);
    glVertex3f(-150.f,  150.f, -520.f);
    glVertex3f(-150.f,  150.f, -320.f);
    glEnd();
    glStencilFunc(GL_EQUAL, 1, 1);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glColor3f(0.f, 0.f, 0.f); /* shadow color */
    glDisable(GL_DEPTH_TEST);

    glPushMatrix();
    glMultMatrixf((GLfloat *)leftwallshadow);
    sphere();
    glPopMatrix();

    glPushMatrix();
    glMultMatrixf((GLfloat *)leftwallshadow);
    sphere2();
    glPopMatrix();
    
    glPushMatrix();
    glMultMatrixf((GLfloat *)leftwallshadow);
    sphere3();
    glPopMatrix();
    
    glPushMatrix();
    glMultMatrixf((GLfloat *)leftwallshadow);
    sphere4();
    glPopMatrix();
    
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rightMat);
    glBegin(GL_QUADS);
    /* right wall */
    glNormal3f(-1.f, 0.f, 0.f);
    glVertex3f( 150.f, -150.f, -320.f);
    glVertex3f( 150.f,  150.f, -320.f);
    glVertex3f( 150.f,  150.f, -520.f);
    glVertex3f( 150.f, -150.f, -520.f);
    /* ceiling */
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ceilMat);
    glNormal3f(0.f, -1.f, 0.f);
    glVertex3f(-150.f,  150.f, -320.f);
    glVertex3f(-150.f,  150.f, -520.f);
    glVertex3f( 150.f,  150.f, -520.f);
    glVertex3f( 150.f,  150.f, -320.f);
    /* back wall */
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, backWallMat);
    glNormal3f(0.f, 0.f, 1.f);
    glVertex3f(-150.f, -150.f, -520.f);
    glVertex3f( 150.f, -150.f, -520.f);
    glVertex3f( 150.f,  150.f, -520.f);
    glVertex3f(-150.f,  150.f, -520.f);
    glEnd();
    glPushMatrix();
    glTranslatef(lightSourcePosition[point[0]], lightSourcePosition[point[1]], lightSourcePosition[point[2]]);
    glDisable(GL_LIGHTING);
    glColor3f(1.f, .8f, .4f);
    glCallList(LIGHTSOURCE);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_SPECULAR, specularNoneMat);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininessNoneMat);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sphere1Mat);
    sphere();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sphere2Mat);
    sphere2();

    glMaterialfv(GL_FRONT, GL_SPECULAR, specularMat);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininessMat);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sphere3Mat);
    sphere3();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );

    glMaterialfv(GL_FRONT, GL_SPECULAR, specularMat);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininessMat);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sphere4Mat);
    sphere4();

    glDisable( GL_BLEND );

    glutSwapBuffers();
}

/* Parse arguments, and set up interface between OpenGL and window system */
int main(int argc, char *argv[])
{
	GLUquadricObj *sphere;
	GLfloat plane[4];
	GLfloat vertex0[3], vertex1[3], vertex2[3];
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(50,50);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL|GLUT_DOUBLE);
	(void)glutCreateWindow("Lab Assignment 3");
	glutDisplayFunc(displayFunc);
	/* draw a perspective scene */
	glMatrixMode(GL_PROJECTION);
	glFrustum(-150., 150., -150., 150., 320., 640.); 
	glMatrixMode(GL_MODELVIEW);
	/* turn on features */
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	getTexture();

	/* make shadow matricies */
	/* 3 points on floor */
	vertex0[point[0]] = -150.f; vertex0[point[1]] = -150.f; vertex0[point[2]] = -320.f;
	vertex1[point[0]] =  150.f; vertex1[point[1]] = -150.f; vertex1[point[2]] = -320.f;
	vertex2[point[0]] =  150.f; vertex2[point[1]] = -150.f; vertex2[point[2]] = -520.f;

	findplane(plane, vertex0, vertex1, vertex2);
	shadowMatrix(floorshadow, plane, lightSourcePosition);
	/* 3 points on left wall */
	vertex0[point[0]] = -150.f; vertex0[point[1]] = -150.f; vertex0[point[2]] = -320.f;
	vertex1[point[0]] = -150.f; vertex1[point[1]] = -150.f; vertex1[point[2]] = -520.f;
	vertex2[point[0]] = -150.f; vertex2[point[1]] =  150.f; vertex2[point[2]] = -520.f;
	findplane(plane, vertex0, vertex1, vertex2);
	shadowMatrix(leftwallshadow, plane, lightSourcePosition);
	/* place light 0 in the right place */
	glLightfv(GL_LIGHT0, GL_POSITION, lightSourcePosition);
	/* remove back faces to speed things up */
	glCullFace(GL_BACK);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glNewList(MAINSPHERE, GL_COMPILE);
	sphere = gluNewQuadric();
	gluSphere(sphere, 22.f, 150, 150);
	gluDeleteQuadric(sphere);
	glEndList();
	glNewList(LIGHTSOURCE, GL_COMPILE);
	sphere = gluNewQuadric();
	gluSphere(sphere, 3.f, 150, 150);

	gluDeleteQuadric(sphere);
	glEndList();
	glEndList();
	glNewList(GROUND, GL_COMPILE);
	glEndList();
	glNewList(LEFTWALL, GL_COMPILE);
	glEndList();
	glutMainLoop();
}

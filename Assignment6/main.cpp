#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;
#include "helper1.h"
#include "helper2.h"

GLuint helpVar = 0;

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
  glTranslatef(-30.f, -100.f, -350.f);

  GLUquadricObj *quadricObj = gluNewQuadric();
  glMatrixMode(GL_MODELVIEW);
  gluQuadricDrawStyle(quadricObj, GLU_FILL);
  glBindTexture(GL_TEXTURE_2D, textureMap);
  gluQuadricTexture(quadricObj, GL_TRUE);
  gluQuadricNormals(quadricObj, GLU_SMOOTH);
  gluSphere(quadricObj, 28, 150, 150);
  glPopMatrix();

  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}

//glossy sphere helper
void sphere3(void)
{
    glPushMatrix();
    glTranslatef(80.f, -100.f, -370.f);    
    glCallList(MAINSPHERE);
    glPopMatrix();
}

//glossy sphere reflector
void sphere4(void)
{
    glPushMatrix();
    glTranslatef(30.f, -55.f, -390.f);
    glCallList(MAINSPHERE);
    glPopMatrix();
}

GLfloat leftwallshadow[4][4];
GLfloat floorshadow[4][4];
GLfloat lightSourcePosition[] = {90.f, 90.f, -320.f, 1.f};
//main opengl display function
void displayFunc(void){
    int i;
    float x, y;
    renderSpheres(spheresVec);
    std::vector< unsigned char > buffer;
    buffer.reserve( 480 * 480 * 3 );
    for( size_t y = 0; y < 480; ++y ){
        for( size_t x = 0; x < 480; ++x ){
            size_t i = (480-y) * 480 + (480-x);
            buffer.push_back( (unsigned char)( std::min(double(1), image[i].x) * 255.0 ) );
            buffer.push_back( (unsigned char)( std::min(double(1), image[i].y) * 255.0 ) );
            buffer.push_back( (unsigned char)( std::min(double(1), image[i].z) * 255.0 ) );
        }
    }
    //clear pixels
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION ); 
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity(); 

    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, helpVar );
    glTexSubImage2D(GL_TEXTURE_2D, 0,0, 0,480, 480,GL_RGB,GL_UNSIGNED_BYTE,&buffer[0]);

    //material properties
    static GLfloat floorMat[] = {1.f, 1.f, 1.f, 1.f};
    static GLfloat leftMat[] = {1.f, 1.f, 1.f, 1.f};
    static GLfloat rightMat[] = {1.f, 1.f, 1.f, 1.f};
    static GLfloat ceilMat[] = {1.f, 1.f, 1.f, 1.f};
    static GLfloat backWallMat[] = {1.f, 1.f, 1.f, 1.f};

    static GLfloat sphere1Mat[] = {.8f, 0.f, 0.f, 1.f};
    static GLfloat sphere2Mat[] = {0.f, 0.f, 1.f, 1.f};
    static GLfloat sphere3Mat[] = {.3f, 1.f, .3f, 1.f};
    static GLfloat sphere4Mat[] = {1.f, 1.f, 1.f, .0f};

    static GLfloat specularNoneMat[] = { 0.0, 0.0, 0.0, 0.0 };  
    static GLfloat shininessNoneMat[] = { 00.0 };

    static GLfloat specularMat[] = { 1.0, 1.0, 1.0, 1.0 };  
    static GLfloat shininessMat[] = { 90.0 };

    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, backWallMat);
    //back wall
    glBegin(GL_QUADS);
    glNormal3f(0.f, 0.f, 1.f);
    glTexCoord2i(0, 0);
    glVertex3f(-150.f, -150.f, -520.f);
    glTexCoord2i(1, 0);
    glVertex3f( 150.f, -150.f, -520.f);
    glTexCoord2i(1, 1);
    glVertex3f( 150.f,  150.f, -520.f);
    glTexCoord2i(0, 1);
    glVertex3f(-150.f,  150.f, -520.f);
    glEnd();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, floorMat);
    // floor
    glBegin(GL_QUADS);
    glNormal3f(0.f, 1.f, 0.f);
    glVertex3f(-150.f, -150.f, -320.f);
    glVertex3f( 150.f, -150.f, -320.f);
    glVertex3f( 150.f, -150.f, -520.f);
    glVertex3f(-150.f, -150.f, -520.f);
    glEnd();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glColor3f(0.f, 0.f, 0.f); //shadow for floor
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
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, leftMat);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 1, 0);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glBegin(GL_QUADS);

    // left wall
    glNormal3f(1.f, 0.f, 0.f);
    glVertex3f(-150.f, -150.f, -320.f);
    glVertex3f(-150.f, -150.f, -520.f);
    glVertex3f(-150.f,  150.f, -520.f);
    glVertex3f(-150.f,  150.f, -320.f);
    glEnd();
    glStencilFunc(GL_EQUAL, 1, 1);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glColor3f(0.f, 0.f, 0.f); //shadow for left wall
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
    // right wall
    glNormal3f(-1.f, 0.f, 0.f);
    glVertex3f( 150.f, -150.f, -320.f);
    glVertex3f( 150.f,  150.f, -320.f);
    glVertex3f( 150.f,  150.f, -520.f);
    glVertex3f( 150.f, -150.f, -520.f);
    // roof 
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ceilMat);
    glNormal3f(0.f, -1.f, 0.f);
    glVertex3f(-150.f,  150.f, -320.f);
    glVertex3f(-150.f,  150.f, -520.f);
    glVertex3f( 150.f,  150.f, -520.f);
    glVertex3f( 150.f,  150.f, -320.f);
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

void reflectionHelp(){
    glGenTextures( 1, &helpVar );
    glBindTexture( GL_TEXTURE_2D, helpVar );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
    glTexImage2D( GL_TEXTURE_2D, 0, 3, 480, 480, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL );    
}

int main(int argc, char *argv[]){
    GLUquadricObj *sphere;
    GLfloat plane[4];
    GLfloat vertex0[3], vertex1[3], vertex2[3];
    glutInit(&argc, argv);
    glutInitWindowSize(800,800);
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

    // make shadow matricies
    // 3 points on floor
    vertex0[point[0]] = -150.f; vertex0[point[1]] = -150.f; vertex0[point[2]] = -320.f;
    vertex1[point[0]] =  150.f; vertex1[point[1]] = -150.f; vertex1[point[2]] = -320.f;
    vertex2[point[0]] =  150.f; vertex2[point[1]] = -150.f; vertex2[point[2]] = -520.f;

    findplane(plane, vertex0, vertex1, vertex2);
    shadowMatrix(floorshadow, plane, lightSourcePosition);
    // 3 points on left wall
    vertex0[point[0]] = -150.f; vertex0[point[1]] = -150.f; vertex0[point[2]] = -320.f;
    vertex1[point[0]] = -150.f; vertex1[point[1]] = -150.f; vertex1[point[2]] = -520.f;
    vertex2[point[0]] = -150.f; vertex2[point[1]] =  150.f; vertex2[point[2]] = -520.f;
    findplane(plane, vertex0, vertex1, vertex2);
    shadowMatrix(leftwallshadow, plane, lightSourcePosition);
    // place light 0 in the right place
    glLightfv(GL_LIGHT0, GL_POSITION, lightSourcePosition);

    //for reflecing sphere
    spheresVec.push_back(new SphereClass(helpClass(3.0, -2.95, -13), 0.8, helpClass(1.0, 0.0, 0.0), 0, 0));
    spheresVec.push_back(new SphereClass(helpClass(1.1, -3.3, -13), 0.8, helpClass(0.00, 0.0, 1.0), 0, 0)); 
    spheresVec.push_back(new SphereClass(helpClass(-2.6, -3.3, -13), 0.8, helpClass(0.3, 1.0, 0.3), 0, 0));

    spheresVec.push_back(new SphereClass(helpClass(-1.0, -1.5, -14), 1, helpClass(0.5, 0.5, 0.5), 1.0, 0.8, 0.5));
    spheresVec.push_back(new SphereClass(helpClass(-10, 11, 0), 3, helpClass(0), 0, 0, helpClass(3)));

    glCullFace(GL_BACK);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glNewList(MAINSPHERE, GL_COMPILE);
    sphere = gluNewQuadric();
    gluSphere(sphere, 30.f, 150, 150);
    gluDeleteQuadric(sphere);
    glEndList();
    glNewList(LIGHTSOURCE, GL_COMPILE);
    sphere = gluNewQuadric();
    gluSphere(sphere, 3.f, 20, 20);

    gluDeleteQuadric(sphere);
    glEndList();
    glEndList();
    glNewList(GROUND, GL_COMPILE);
    glEndList();
    glNewList(LEFTWALL, GL_COMPILE);
    glEndList();
    reflectionHelp();
    glutMainLoop();
}

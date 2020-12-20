

#include "glut.h"
#include <iostream>
#include <gl/GL.h>

GLfloat rotate_x=0;
GLfloat rotate_y=0;
double asp = 1;
double dim = 3.0;
int fov = 55;
double th = 0.0;
double ph = 0.0;

#define PI 3.141592653
#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))




void init() {
	// Set initial OpenGL states
}

void project() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(fov, asp, dim/4, dim*4); // aperture, aspect, near, far

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}
void drawCubeLocation(GLfloat xcenter, GLfloat ycenter, GLfloat size, GLfloat zpos) { 

	glBegin(GL_POLYGON); //front face

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(xcenter - size, ycenter + size, zpos - size); //top left

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(xcenter - size, ycenter - size, zpos - size); //bottom left
	
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(xcenter + size, ycenter - size, zpos - size); //bottom right

	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(xcenter + size, ycenter + size, zpos - size); //top right

	glEnd();

	glBegin(GL_POLYGON);//back face
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(xcenter + size, ycenter + size, zpos + size); //top right
	glVertex3f(xcenter + size, ycenter - size, zpos + size); //bottom right
	glVertex3f(xcenter - size, ycenter - size, zpos + size); //bottom left
	glVertex3f(xcenter - size, ycenter + size, zpos + size); //top left
	glEnd();


	glBegin(GL_POLYGON); //left face
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(xcenter - size, ycenter - size, zpos - size); //bottom left
	glVertex3f(xcenter - size, ycenter + size, zpos - size); //top left
	glVertex3f(xcenter - size, ycenter + size, zpos + size); //top left
	glVertex3f(xcenter - size, ycenter - size, zpos + size); //bottom left
	glEnd();

	glBegin(GL_POLYGON);//right face
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(xcenter + size, ycenter + size, zpos - size); //top right
	glVertex3f(xcenter + size, ycenter - size, zpos - size); //bottom right
	glVertex3f(xcenter + size, ycenter - size, zpos + size); //bottom right
	glVertex3f(xcenter + size, ycenter + size, zpos + size); //top right
	glEnd();

	glBegin(GL_POLYGON);//top face
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(xcenter + size, ycenter + size, zpos - size); //top right
	glVertex3f(xcenter + size, ycenter + size, zpos + size); //top right
	glVertex3f(xcenter - size, ycenter + size, zpos + size); //top left
	glVertex3f(xcenter - size, ycenter + size, zpos - size); //top left
	glEnd();

	glBegin(GL_POLYGON);//bottom face
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(xcenter + size, ycenter - size, zpos - size); //bottom right
	glVertex3f(xcenter - size, ycenter - size, zpos - size); //bottom left
	glVertex3f(xcenter - size, ycenter - size, zpos + size); //bottom left
	glVertex3f(xcenter + size, ycenter - size, zpos + size); //bottom right
	glEnd();

	glFlush();
	glutSwapBuffers();
}
void drawCube() {
	glBegin(GL_POLYGON);

	glColor3f(1.0, 0.0, 0.0);   
	glVertex3f(0.5, -0.5, -0.5);      // P1 is red

	glColor3f(0.0, 1.0, 0.0);     
	glVertex3f(0.5, 0.5, -0.5);      // P2 is green

	glColor3f(0.0, 0.0, 1.0);    
	glVertex3f(-0.5, 0.5, -0.5);      // P3 is blue

	glColor3f(1.0, 0.0, 1.0);     
	glVertex3f(-0.5, -0.5, -0.5);      // P4 is purple

	glEnd();

	// White side - BACK
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	// Purple side - RIGHT
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();

	// Green side - LEFT
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	// Blue side - TOP
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	// Red side - BOTTOM
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	//draw and swap buffers
	glFlush();
	glutSwapBuffers();

}
// display function
void display() {
	// Clear the window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//glShadeModel(GL_FLAT);
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);


	glLoadIdentity();
	
	

	double Ex = -2.0 * dim * Sin(th) * Cos(ph);
	double Ey = 2.0 * dim * Sin(ph);
	double Ez = 2.0 * dim * Cos(th) * Cos(ph);
	gluLookAt(Ex, Ey, Ez, 0, 0, 0, 0, Cos(ph), 0);
	drawCubeLocation(0.0, 0.0, 0.2, 0.0);

	
	//glRotatef(rotate_x, 1.0, 0.0, 0.0);
	//glRotatef(rotate_y, 0.0, 1.0, 0.0);
	
	rotate_x = 0;
	rotate_y = 0;
	//drawCube();
}
/*
Function invoked when an event on a regular keys occur.
*/
void keyboard(unsigned char k, int x, int y)
{
	// Close application if ESC is pressed 

	if (k == 27)
	{
		exit(0);
	}

	printf("\nchar: %u, x: %d, y: %d\n", k, x, y);
	if (k == 119) {
		printf("w was pressed");
		th += 0.5;
		
	}
	else if (k == 115) {
		ph += 0.5;
		
	}
	glutPostRedisplay();
}
/*
Mouse Handler
*/
void mouseClick(int button, int mode, int x, int y) {
	// event happens once on pushing the button and once more when releasing it
	// button identifies what you clicked, mode if its down or up
}
void mouseMotion(int x, int y) {
	// called when the mouse moves
	// active motion means a button is down, passive means it is up
}
void resize(int width, int height) {
	//this is called on window resize
	//params are window width and window height
	int min = width;
	if (height < width) {
		min = height;
	}
	glViewport(0, 0, min, min); //keeps viewport a square
	asp = (height > 0) ? (double)width / height : 1;
	project();
	glutPostRedisplay();
}

/*
The main function.
*/
int main(int argc, char** argv)
{
	// Initialize the GLUT window
	glutInit(&argc, argv);
	glViewport(0, 0, 600, 600);

	glutInitWindowSize(600, 800);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("project3");
	glEnable(GL_DEPTH_TEST);


	glutDisplayFunc(display);
	glutMouseFunc(mouseClick);
	glutReshapeFunc(resize);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);


	glutMainLoop();
	return 0;
}
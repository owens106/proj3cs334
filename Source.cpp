

#include "glut.h"
#include <iostream>
#include <gl/GL.h>

GLfloat rotate_x=0;
GLfloat rotate_y=0;

void init() {
	// Set initial OpenGL states
}
void drawCube() {
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);     
	glVertex3f(0.0, -0.5, -0.5); // P1 is red
	
	glColor3f(0.0, 1.0, 0.0); 
	glVertex3f(0.0, 0.5, -0.5); // P2 is green
	
	glColor3f(0.0, 0.0, 1.0);     
	glVertex3f(-1.0, 0.5, -0.5);  // P3 is blue
	
	glColor3f(1.0, 0.0, 1.0);     
	glVertex3f(-1.0, -0.5, -0.5);      // P4 is purple

	glEnd();

	// White side - BACK
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(0.0, -0.5, 0.5);
	glVertex3f(0.0, 0.5, 0.5);
	glVertex3f(-1.0, 0.5, 0.5);
	glVertex3f(-1.0, -0.5, 0.5);
	glEnd();

	// Purple side - RIGHT
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(0.0, -0.5, -0.5);
	glVertex3f(0.0, 0.5, -0.5);
	glVertex3f(0.0, 0.5, 0.5);
	glVertex3f(0.0, -0.5, 0.5);
	glEnd();

	// Green side - LEFT
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-1.0, -0.5, 0.5);
	glVertex3f(-1.0, 0.5, 0.5);
	glVertex3f(-1.0, 0.5, -0.5);
	glVertex3f(-1.0, -0.5, -0.5);
	glEnd();

	// Blue side - TOP
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.5, 0.5);
	glVertex3f(0.0, 0.5, -0.5);
	glVertex3f(-1.0, 0.5, -0.5);
	glVertex3f(-1.0, 0.5, 0.5);
	glEnd();

	// Red side - BOTTOM
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, -0.5, -0.5);
	glVertex3f(0.0, -0.5, 0.5);
	glVertex3f(-1.0, -0.5, 0.5);
	glVertex3f(-1.0, -0.5, -0.5);
	glEnd();



	//cube2
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);     
	glVertex3f(1.0, 0.0, -0.0);      // P1 is red

	glColor3f(0.0, 1.0, 0.0);     
	glVertex3f(1.0, 1.0, -0.0);      // P2 is green

	glColor3f(0.0, 0.0, 1.0);     
	glVertex3f(0.0, 1.0, -0.0);      // P3 is blue

	glColor3f(1.0, 0.0, 1.0);     
	glVertex3f(0.0, 0.0, -0.0);      // P4 is purple

	glEnd();

	// White side - BACK
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, -0.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(-0.0, 1.0, 1.0);
	glVertex3f(-0.0, -0.0, 1.0);
	glEnd();

	// Purple side - RIGHT
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(1.0, -0.0, -0.0);
	glVertex3f(1.0, 1.0, -0.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, -0.0, 1.0);
	glEnd();

	// Green side - LEFT
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-0.0, -0.0, 1.0);
	glVertex3f(-0.0, 1.0, 1.0);
	glVertex3f(-0.0, 1.0, -0.0);
	glVertex3f(-0.0, -0.0, -0.0);
	glEnd();

	// Blue side - TOP
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, -0.0);
	glVertex3f(-0.0, 1.0, -0.0);
	glVertex3f(-0.0, 1.0, 1.0);
	glEnd();

	// Red side - BOTTOM
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, -0.0, -0.0);
	glVertex3f(1.0, -0.0, 1.0);
	glVertex3f(-0.0, -0.0, 1.0);
	glVertex3f(-0.0, -0.0, -0.0);
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



	
	drawCube();

	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45, 1.0, 0.3, 100.01); // aperture, aspect, near, far

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	*/
	
	
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	
	rotate_x = 0;
	rotate_y = 0;
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
		rotate_x += 0.5;
		
	}
	else if (k == 115) {
		rotate_y += 0.5;
		
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
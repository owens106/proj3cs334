/*
	Hello Triangle, OpenGL 2 level
	No shaders
*/

#include "glut.h"
#include <iostream>
#include <gl/GL.h>
void init() {
	// Set initial OpenGL states

}
// set up vertex data 
float vertices[] = {
	0.0f, 0.0f, 0.0f, //origin
	1.0f, 0.0f, 0.0f, // XaxisRight vertex
	 0.0f, 1.0f, 0.0f, // YaxisPositive vertex
	 -1.0f,  -1.0f, 0.0f  // bottomLeft vertex
};
float colors[] = {
  1.0f, 0.5f, 0.2f,
  1.0f, 0.5f, 0.2f,
  1.0f, 0.5f, 0.2f
};
// display function
void display() {
	// Clear the window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	// Draw the triangle
	glShadeModel(GL_FLAT);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	//glVertexPointer(3, GL_FLOAT, 0, vertices);
	//glColorPointer(3, GL_FLOAT, 0, colors);

	glBegin(GL_LINES); //line 0,0 to 1,0
	glColor3ub(255, 0, 0); //red
	glVertex2f(0.0, 0.0);
	glVertex2f(1.0, 0.0);
	glEnd();

	glBegin(GL_LINES); //line 0,0 to 1,0
	glColor3ub(0, 255, 0); //blue
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 1.0);
	glEnd();

	glBegin(GL_LINES); //line 0,0 to 1,0
	glColor3ub(255, 255, 0); //yellow
	glVertex2f(0.0, 0.0);
	glVertex2f(-1.0, -1.0);
	glEnd();


	//glDrawArrays(GL_LINES, 0, 4); // solid triangle

	  // Swap buffers for animation
	glutSwapBuffers();
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
}

/*
The main function.
*/
int main(int argc, char** argv)
{
	// Initialize the GLUT window
	glutInit(&argc, argv);
	glViewport(0, 0, 300, 300);

	glutInitWindowSize(600, 800);
	//glutInitWindowPosition(300, 300);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("project3");

	glutDisplayFunc(display);
	glutMouseFunc(mouseClick);
	glutReshapeFunc(resize);
	glutMotionFunc(mouseMotion);

	glutMainLoop();
	return 0;
}
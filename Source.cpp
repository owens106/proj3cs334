

#include "glut.h"
#include <iostream>
#include <gl/GL.h>

GLfloat rotate_x=0;
GLfloat rotate_y=0;
double asp = 1;
double dim = 3.0;
int fov = 45;
double th = 0.0;
double ph = 0.0;

double xpos = 0.0;
double ypos = 0.0;
double zpos = 0.0;

#define PI 3.1415926535897932384626433832795
#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))
double zoomfactor = 1.0;

double lmb[4] = { 0, 0, 0, 0 };

BOOLEAN Lclick = false;
BOOLEAN ShiftLclick = false;



void init() {
	// Set initial OpenGL states
}
void project() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double windowHeight = glutGet(GLUT_SCREEN_HEIGHT);
	double windowWidth = glutGet(GLUT_SCREEN_WIDTH);

	gluPerspective(fov * zoomfactor, asp, dim / 4, dim * 4); // aperture, aspect, near, far


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
void resize(int width, int height) {
	asp = (height > 0) ? (double)width / height : 1;
	printf("\nasp:%f", asp);

	//this is called on window resize
	//params are window width and window height
	int min = width;
	if (height < width) {
		min = height;
	}
	printf("\n width: %d, height: %d, min: %d",width,height,min);
	glViewport(0, 0, min, min); //keeps viewport a square
	project();
	glutPostRedisplay();
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

	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 1.0, 0.0);

	glVertex3f(0, 0, 0);
	glVertex3f(xcenter - size, ycenter + size, zpos + size); //top left
	glVertex3f(xcenter - size+0.02, ycenter + size, zpos + size); //top left

	glVertex3f(0, 0, 0);
	glVertex3f(xcenter - size, ycenter - size, zpos + size); //bottom left
	glVertex3f(xcenter - size+.02, ycenter - size, zpos + size); //bottom left

	glVertex3f(0, 0, 0);
	glVertex3f(xcenter + size, ycenter - size, zpos + size); //bottom right
	glVertex3f(xcenter + size+.02, ycenter - size, zpos + size); //bottom right

	glVertex3f(0, 0, 0);
	glVertex3f(xcenter + size, ycenter + size, zpos + size); //top right
	glVertex3f(xcenter + size+0.02, ycenter + size, zpos + size); //top right




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
}
// display function
void display() {
	// Clear the window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	
	double Ex = 1.0 * dim * Sin(th) * Cos(ph);
	double Ey = 1.0 * dim * Sin(ph);
	double Ez = -1.0 * dim * Cos(th) * Cos(ph);
	gluLookAt(Ex, Ey, Ez, xpos, ypos, zpos, 0, Cos(ph), 0);


	drawCubeLocation(-0.0f, -0.0f, 0.1f, -0.0f);
	drawCubeLocation(-0.6f, -0.6f, 0.1f, -0.4f);
	drawCubeLocation(0.6f, 0.6f, 0.1f, 0.4f);
	drawCubeLocation(0.6f, -0.6f, 0.1f, 0.2f);
	drawCubeLocation(-0.6f, 0.6f, 0.1f, -0.2f);

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

	printf("\nchar: %u, x: %d, y: %d\n", k, x, y);
	if (k == 119) {
		printf("w was pressed");
		th += 0.5;
		
	}
	else if (k == 115) {
		ph += 0.5;
		
	}
	glutPostRedisplay();
	project();
}
/*
Mouse Handler
*/
void mouseClick(int button, int mode, int x, int y) {
	//button 0 is Lclick
	//mode = 0 for down 1 for up
	// event happens once on pushing the button and once more when releasing it
	// button identifies what you clicked, mode if its down or up
	double windowHeight = glutGet(GLUT_SCREEN_HEIGHT);
	double windowWidth = glutGet(GLUT_SCREEN_WIDTH);

	printf("button: %d  mode: %d\n",button,mode);
	if (button == 0 && mode == 0) {//Lclick pushed down
		Lclick = true;
		lmb[0] = x;
		lmb[1] = y;
	}
	if(button == 0 && mode == 1 ){//Left click unclicked
		//Lclick = false;
		lmb[2] = x;
		lmb[3] = y;

	}
	for (int i = 0; i < 4; i++) {
		printf(" %f: ", lmb[i]);
	}
	printf("\n");

	double xchange = (lmb[2] - lmb[0]) / windowWidth; // x change relative to window
	double ychange = (lmb[3] - lmb[1]) / windowHeight; //y change relative to window

	int z = glutGetModifiers();
	if (z == 1 && Lclick && mode == 1) {//shift Lclick released
		printf("shift L click pressed\n");
		//translation
		Lclick = false;
		
		xpos += xchange;
		ypos += ychange;
		project();
	}
	else if (z == 2 && Lclick && mode == 1) {
		printf("ctrl L click pressed\n");
		zoomfactor -=0.1;
		if (zoomfactor < 0.0) {
			zoomfactor = 1;
		}
		Lclick = false;
		project();
	}
	else if (z == 0 && Lclick && mode == 1) {
		//Left click released, no special input
		th += (xchange* 100);
		ph += (ychange * 100);
		project();
	}
}
void mouseMotion(int x, int y) {
	// called when the mouse moves
	// active motion means a button is down, passive means it is up
}

/*
The main function.
*/
int main(int argc, char** argv)
{
	// Initialize the GLUT window
	glutInit(&argc, argv);
	glViewport(0, 0, 600, 600);

	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("project3");
	glEnable(GL_DEPTH_TEST);


	glutDisplayFunc(display);
	glutMouseFunc(mouseClick);
	glutReshapeFunc(resize);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);

	gluPerspective(fov, asp, dim / 4, dim * 4); // aperture, aspect, near, far

	glutMainLoop();
	return 0;
	
}
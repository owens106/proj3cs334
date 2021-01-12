


#include "glut.h"
#include "glui.h"
#include <iostream>
#include <gl/GL.h>


GLfloat rotate_x=0;
GLfloat rotate_y=0;
double asp = 1;
double dim = 3.0;
int fov = 30;
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
double lmDrag[2] = { 0,0 };

int menu;
int submenu_id;
BOOLEAN Lclick = false;
BOOLEAN ShiftLclick = false;

int horizon;
int segments;
int main_window;
int listboxID=30;
float spinnerFloat=1.0;
int infinityLines = 1;

//GLUI VARS
GLUI_Spinner* segment_spinner;
GLUI_Listbox* listbox;


void init() {
	// Set initial OpenGL states
}
void project() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double windowHeight = glutGet(GLUT_SCREEN_HEIGHT);
	double windowWidth = glutGet(GLUT_SCREEN_WIDTH);

	gluPerspective(fov * spinnerFloat, asp, dim / 4, dim * 400); // aperture, aspect, near, far


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
void resize(int width, int height) {
	asp = (height > 0) ? (double)width / height : 1;

	//this is called on window resize
	//params are window width and window height
	int min = width;
	if (height < width) {
		min = height;
	}
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

	/*glBegin(GL_TRIANGLES);
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
	*/



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



	//begin infinity Lines
	if (infinityLines) {
		glColor3f(0.0, 1.0, 0.1);
		glBegin(GL_POLYGON);
		glVertex3f(xcenter + size, ycenter + size, zpos - size); //top right
		glVertex3f(xcenter + size, ycenter + size, zpos + size + 100); //top right
		glVertex3f(xcenter + size + 0.01, ycenter + size, zpos + size + 100); //top right
		glVertex3f(xcenter + size + 0.01, ycenter + size, zpos - size); //top right
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(xcenter - size, ycenter + size, zpos - size); //top right
		glVertex3f(xcenter - size, ycenter + size, zpos + size + 100); //top right
		glVertex3f(xcenter - size + 0.01, ycenter + size, zpos + size + 100); //top right
		glVertex3f(xcenter - size + 0.01, ycenter + size, zpos - size); //top right
		glEnd();



		glBegin(GL_POLYGON);
		glVertex3f(xcenter + size, ycenter - size, zpos - size); //top right
		glVertex3f(xcenter + size, ycenter - size, zpos + size + 100); //top right
		glVertex3f(xcenter + size, ycenter - size + 0.01, zpos + size + 100); //top right
		glVertex3f(xcenter + size, ycenter - size + 0.01, zpos - size); //top right
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(xcenter - size, ycenter - size, zpos - size); //top right
		glVertex3f(xcenter - size, ycenter - size, zpos + size + 100); //top right
		glVertex3f(xcenter - size, ycenter - size + 0.01, zpos + size + 100); //top right
		glVertex3f(xcenter - size, ycenter - size + 0.01, zpos - size); //top right
		glEnd();
	}

	glFlush();
}
// display function
void display() {
	// Clear the window
	if (listboxID != 0) {
		fov = listboxID;
		project();
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	
	double Ex = 1.0 * dim * Sin(th) * Cos(ph);
	double Ey = 1.0 * dim * Sin(ph);
	double Ez = -1.0 * dim * Cos(th) * Cos(ph);
	//gluLookAt(Ex, Ey, Ez, xpos, ypos, zpos, 0, Cos(ph), 0);
	gluLookAt(Ex, Ey, Ez, 0, 0, zpos, 0, Cos(ph), 0);


	drawCubeLocation(-0.0f + xpos, -0.0f +ypos, 0.1f, -0.0f);
	drawCubeLocation(-0.6f + xpos, -0.6f + ypos, 0.1f, -0.4f);
	drawCubeLocation(0.6f + xpos, 0.6f + ypos, 0.1f, 0.4f);
	drawCubeLocation(0.6f + xpos, -0.6f + ypos, 0.1f, 0.2f);
	drawCubeLocation(-0.6f + xpos, 0.6f + ypos, 0.1f, -0.2f);

	if (horizon) {
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex3f(-100, 0.0, 100);
		glVertex3f(-100, 0.1, 100);
		glVertex3f(100, 0.1, 100);
		glVertex3f(100, 0.0, 100);
		glEnd();


		glBegin(GL_POLYGON);
		glVertex3f(-100, 0.0, -100);
		glVertex3f(-100, 0.1, -100);
		glVertex3f(100, 0.1, -100);
		glVertex3f(100, 0.0, -100);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(-100, 0.0, 100);
		glVertex3f(-100, 0.1, 100);
		glVertex3f(-100, 0.1, -100);
		glVertex3f(-100, 0.0, -100);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(100, 0.0, 100);
		glVertex3f(100, 0.1, 100);
		glVertex3f(100, 0.1, -100);
		glVertex3f(100, 0.0, -100);
		glEnd();

	}

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

	if (k == 119) {
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

	if (button == 0 && mode == 0) {//Lclick pushed down
		Lclick = true;
		lmb[0] = x;
		lmb[1] = y;
		lmDrag[0] = x;
		lmDrag[1] = y;
	}
	if(button == 0 && mode == 1 ){//Left click unclicked
		//Lclick = false;
		lmb[2] = x;
		lmb[3] = y;

	}

	double xchange = (lmb[2] - lmb[0]) / windowWidth; // x change relative to window
	double ychange = (lmb[3] - lmb[1]) / windowHeight; //y change relative to window

	int z = glutGetModifiers();
	if (z == 1 && Lclick && mode == 1) {//shift Lclick released
		//translation
		Lclick = false;
		
		xpos += xchange;
		ypos += ychange;
		project();
	}
	else if (z == 2 && Lclick && mode == 1) {
		zoomfactor -=0.1;
		if (zoomfactor < 0.0) {
			zoomfactor = 1;
		}
		Lclick = false;
		project();
	}
	else if (z == 0 && Lclick && mode == 1) {
		//Left click released, no special input
		Lclick = false;
		//th += (xchange* 100);
		//ph += (ychange * 100);
		//project();
	}
}
void mouseMotion(int x, int y) {
	// called when the mouse moves
	// active motion means a button is down, passive means it is up
	double windowHeight = glutGet(GLUT_SCREEN_HEIGHT);
	double windowWidth = glutGet(GLUT_SCREEN_WIDTH);

	GLfloat xdiff = (lmDrag[0] - (GLfloat)x)/windowWidth;
	GLfloat ydiff = (lmDrag[1] - (GLfloat)y)/windowHeight;

	int z = glutGetModifiers();
	if (Lclick && z == 0) {
		lmDrag[0] = x;
		lmDrag[1] = y;
		th += xdiff*150;
		ph += ydiff*150;

	}
	project();

}

/*
The main function.
*/

void handleMenu(int choice) {

	switch (choice) {
	case 5:
		fov = 30;
		break;
	case 6:
		fov = 45;
		break;
	case 7:
		fov = 60;
		break;
	case 8:
		fov = 75;
		break;
	case 1:
		exit(0);
		break;
	case 2:
		zoomfactor = 1.0;
		ph = 0;
		th = 0;
		fov = 55;
		xpos = 0;
		ypos = 0;
		break;
	case 3:
		horizon = !horizon;
		break;
	}

	project();
	glutPostRedisplay();
}

void buttonPush(int val) {
	switch (val)
	{
	case (1):
		xpos -= 0.1;
		break;
	case (2):
		xpos += 0.1;
		break;
	case(3):
		ypos += 0.1;
		break;
	case(4):
		ypos -= 0.1;
		break;
	case(5):
		//reset
		zoomfactor = 1.0;
		ph = 0;
		th = 0;
		fov = 30;
		xpos = 0;
		ypos = 0;
		segment_spinner->set_float_val(1.0);
		listbox->set_int_val(30);
		break;
		
	
	}
	project();
}


void createMenu() {
	submenu_id = glutCreateMenu(handleMenu);
	glutAddMenuEntry("30", 5);
	glutAddMenuEntry("45", 6);
	glutAddMenuEntry("60", 7);
	glutAddMenuEntry("75", 8);     
	
	menu = glutCreateMenu(handleMenu);
	glutAddMenuEntry("Exit", 1);
	glutAddMenuEntry("reset", 2);
	glutAddMenuEntry("show Horizon", 3);
	glutAddMenuEntry("Show Perspectve", 4);

	glutAddSubMenu("set Aperture", submenu_id);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}


void myGlutIdle(void)
{
	/* According to the GLUT specification, the current window is
	   undefined during an idle callback.  So we need to explicitly change
	   it if necessary */
	if (glutGetWindow() != main_window)
		glutSetWindow(main_window);

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	// Initialize the GLUT window
	glutInit(&argc, argv);
	glViewport(0, 0, 600, 600);

	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	main_window = glutCreateWindow("project3");
	glEnable(GL_DEPTH_TEST);


	glutDisplayFunc(display);
	glutMouseFunc(mouseClick);
	glutReshapeFunc(resize);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);

	gluPerspective(fov, asp, dim / 4, dim * 400); // aperture, aspect, near, far
	createMenu();

	GLUI* glui = GLUI_Master.create_glui("GLUI",0,900,00);

	glui->add_checkbox("Horizon", &horizon);
	glui->add_checkbox("Extended Edges", &infinityLines);


	//GLUI_Spinner* segment_spinner =  //Can be used for T in Program 5
	//	glui->add_spinner("Segments:", GLUI_SPINNER_INT, &segments);
	//segment_spinner->set_int_limits(3, 60);

	glui->set_main_gfx_window(main_window);


	segment_spinner =  //Can be used for T in Program 5
		glui->add_spinner("Zoom Level:", GLUI_SPINNER_FLOAT, &spinnerFloat);
	segment_spinner->set_int_limits(0.0,1.5);

	listbox = glui->add_listbox("Aperture Value",&listboxID);
	listbox->add_item(30, "30");
	listbox->add_item(45, "45");
	listbox->add_item(60, "60");
	listbox->add_item(75, "75");


	glui->add_separator();

	GLUI_Panel* obj_panel = glui->add_panel("Translation");

	glui->add_button("Translate Right", 1, buttonPush);
	glui->add_button("Translate Left", 2, buttonPush);
	glui->add_button("Translate Up", 3, buttonPush);
	glui->add_button("Translate Down", 4, buttonPush);

	glui->add_separator();

	glui->add_button("Reset", 5, buttonPush);
	glui->add_button("Quit", 0, (GLUI_Update_CB)exit);


	//GLUI_RadioGroup* group1 = glui->add_radiogroup_to_panel(obj_panel);
	//glui->add_radiobutton_to_group(group1, "Option 1");
	//glui->add_radiobutton_to_group(group1, "Option 2");

	/* We register the idle callback with GLUI, *not* with GLUT */
	GLUI_Master.set_glutIdleFunc(myGlutIdle);
	GLUI_Master.set_glutReshapeFunc(resize);

	glutMainLoop();
	return 0;
	
}



#include "glut.h"
#include "glui.h"
#include <iostream>
#include <gl/GL.h>
#include <vector>

using std::vector;

GLfloat rotate_x=0;
GLfloat rotate_y=0;
double asp = 1;
double dim = 3.0;
int fov = 30;
double th = 0.0;
double ph = 0.0;


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

BOOLEAN someSelection = false; //represents if any point is currently picked
int selectedIndex = -1;

//GLUI VARS
GLUI_Spinner* segment_spinner;
GLUI_Listbox* listbox;



class Point {
public:
	float xcenter = 0.0;
	float ycenter = 0.0;
	float zcenter = 0.0;
	BOOLEAN selected = false;
	float anglex = 0.0;
	float angley = 0.0;
	float size = 0.1;

};

vector<Point> Points;
Point p0, p1, p2, p3, p4;


void init() {
	// Set initial OpenGL states
}
void reset() {
	Points.clear();
	//init cube points
	p0.xcenter = 0.0;
	p0.ycenter = 0.0;
	p0.zcenter = 0.0;

	p1.xcenter = -0.6;
	p1.ycenter = -0.6;
	p1.zcenter = -0.4;

	p2.xcenter = 0.6;
	p2.ycenter = 0.6;
	p2.zcenter = 0.4;

	p3.xcenter = 0.6;
	p3.ycenter = -0.6;
	p3.zcenter = 0.2;

	p4.xcenter = -0.6;
	p4.ycenter = 0.6;
	p4.zcenter = -0.2;

	Points.push_back(p0);
	Points.push_back(p2);
	Points.push_back(p4);
	Points.push_back(p1);
	Points.push_back(p3);
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

	//glColor3f(1.0, 0.0, 0.0);
	glVertex3f(xcenter - size, ycenter + size, zpos - size); //top left

	//glColor3f(0.0, 1.0, 0.0);
	glVertex3f(xcenter - size, ycenter - size, zpos - size); //bottom left
	
	//glColor3f(0.0, 0.0, 1.0);
	glVertex3f(xcenter + size, ycenter - size, zpos - size); //bottom right

	//glColor3f(1.0, 0.0, 1.0);
	glVertex3f(xcenter + size, ycenter + size, zpos - size); //top right

	glEnd();

	glBegin(GL_POLYGON);//back face
	//glColor3f(1.0, 1.0, 1.0);
	glVertex3f(xcenter + size, ycenter + size, zpos + size); //top right
	glVertex3f(xcenter + size, ycenter - size, zpos + size); //bottom right
	glVertex3f(xcenter - size, ycenter - size, zpos + size); //bottom left
	glVertex3f(xcenter - size, ycenter + size, zpos + size); //top left
	glEnd();

	glEnd();


	glBegin(GL_POLYGON); //left face
	//glColor3f(0.0, 1.0, 0.0);
	glVertex3f(xcenter - size, ycenter - size, zpos - size); //bottom left
	glVertex3f(xcenter - size, ycenter + size, zpos - size); //top left
	glVertex3f(xcenter - size, ycenter + size, zpos + size); //top left
	glVertex3f(xcenter - size, ycenter - size, zpos + size); //bottom left
	glEnd();

	

	glBegin(GL_POLYGON);//right face
	//glColor3f(1.0, 0.0, 1.0);
	glVertex3f(xcenter + size, ycenter + size, zpos - size); //top right
	glVertex3f(xcenter + size, ycenter - size, zpos - size); //bottom right
	glVertex3f(xcenter + size, ycenter - size, zpos + size); //bottom right
	glVertex3f(xcenter + size, ycenter + size, zpos + size); //top right
	glEnd();

	glBegin(GL_POLYGON);//top face
	//glColor3f(0.0, 0.0, 1.0);
	glVertex3f(xcenter + size, ycenter + size, zpos - size); //top right
	glVertex3f(xcenter + size, ycenter + size, zpos + size); //top right
	glVertex3f(xcenter - size, ycenter + size, zpos + size); //top left
	glVertex3f(xcenter - size, ycenter + size, zpos - size); //top left
	glEnd();

	glBegin(GL_POLYGON);//bottom face
	//glColor3f(1.0, 0.0, 0.0);
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

	gluLookAt(Ex, Ey, Ez, 0, 0, zpos, 0, Cos(ph), 0);



	for (int inc = 0; inc < Points.size(); inc++) {
		float x = Points.at(inc).xcenter;
		float y = Points.at(inc).ycenter;
		float z = Points.at(inc).zcenter;
		float size = Points.at(inc).size;

		if (Points.at(inc).selected) {
			glColor3f(1.0, 0.0, 0.0);
		}
		else {
			glColor3f(0.0, 0.0, 1.0);
		}
		glPushMatrix();
		glRotatef(Points.at(inc).anglex, 1.0, 0.0, 0.0);
		glRotatef(Points.at(inc).angley, 0.0, 1.0, 0.0);

		drawCubeLocation(x, y, size, z);
		glPopMatrix();
	}



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

	printf("%u\n", k);
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
		//selection
		Lclick = false;
		float localx = 2.0f * ((GLfloat)x) / (GLfloat)(glutGet(GLUT_WINDOW_WIDTH)) - 1.0f; //convert to same scale as points
		float localy = -1 * (2.0f * ((GLfloat)y) / (GLfloat)(glutGet(GLUT_WINDOW_HEIGHT)) - 1.0f);
		//localx = localx * -1.0


		printf("%f  %f\n", localx, localy);
		int index = 0;
		for (int i = 0; i < Points.size(); i++) {
			if ((abs(Points.at(i).xcenter - localx)) < 0.1 && (abs(Points.at(i).ycenter - localy) < 0.1) ){
				if (Points.at(i).selected == true) {
					//if current selected point is already selected, toggle off
					//therefore no selected point remains
					someSelection = false;
					
				}
				else {
					someSelection = true;
				}
				Points.at(i).selected = !Points.at(i).selected;
				index = i;
				selectedIndex = i;
				break;
			}
		}
		for (int j = 0; j < Points.size(); j++) {
			if (j == index) {
				continue;
			}
			Points.at(j).selected = false;//toggle all other selections
		}


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
	if (Lclick && z == 0 && someSelection == false) {
		lmDrag[0] = x;
		lmDrag[1] = y;
		th += xdiff*150;
		ph += ydiff*150;

	}
	else if((Lclick && z == 0) && (someSelection)) {
		printf("inside rotaion for selection\n");
		Points.at(selectedIndex).anglex -= ydiff;
		Points.at(selectedIndex).angley += xdiff;

	}

	glutPostRedisplay();

}

/*
The main function.
*/



void buttonPush(int val) {
	printf("someSelection Value: %d\n", someSelection);
	if (someSelection) {
		//aka local mode
		switch (val)
		{
		case (1):
			Points.at(selectedIndex).xcenter-= 0.1;
			break;
		case (2):
			Points.at(selectedIndex).xcenter += 0.1;
			break;
		case(3):
			Points.at(selectedIndex).ycenter += 0.1;
			break;
		case(4):
			Points.at(selectedIndex).ycenter -= 0.1;
			break;
		}
	}
	else {
		//non local
		switch (val)
		{
		case (1):
			for (int i = 0; i < Points.size(); i++) {
				Points.at(i).xcenter -= 0.1;
			}
			break;
		case (2):
			for (int i = 0; i < Points.size(); i++) {
				Points.at(i).xcenter += 0.1;
			}
			break;
		case(3):
			for (int i = 0; i < Points.size(); i++) {
				Points.at(i).ycenter += 0.1;
			}
			break;
		case(4):
			for (int i = 0; i < Points.size(); i++) {
				Points.at(i).ycenter -= 0.1;
			}
			break;
		}
	}
	
	if (val == 5) {
		//reset
		zoomfactor = 1.0;
		ph = 0;
		th = 0;
		fov = 30;
		segment_spinner->set_float_val(1.0);
		listbox->set_int_val(30);
		someSelection = false;
		reset();
	}
		
	
	
	project();
}

void cubeSelector(int val) {
	if (val == 1) {
		selectedIndex += 1;
		if (selectedIndex == 5) {
			selectedIndex = 0;
		}
		someSelection = true;
	}
	else if (val == 2) {
		//prev
		selectedIndex -= 1;
		if (selectedIndex == -1) {
			selectedIndex = 4;
		}
		someSelection = true;
	}

	else if (val == 3) {
		//select none
		someSelection = false;
	}

	for (int i = 0; i < Points.size(); i++) {
		Points.at(i).selected = false;
	}
	if (someSelection) {
		Points.at(selectedIndex).selected = true;
	}

	project();
}

void cubeScaler(int val) {
	if (someSelection == false) {
		return;
	}
	if (val == 1) {
		Points.at(selectedIndex).size += 0.01;
	}
	else if (val == 2) {
		Points.at(selectedIndex).size -= 0.01;
		if (Points.at(selectedIndex).size <= 0.0) {
			Points.at(selectedIndex).size = 0.01;
		}
	}
	project();
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
	reset();
	


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

	GLUI* glui = GLUI_Master.create_glui("GLUI",0,900,00);

	glui->add_checkbox("Horizon", &horizon);
	glui->add_checkbox("Extended Edges", &infinityLines);


	//GLUI_Spinner* segment_spinner =  //Can be used for T in Program 5
	//	glui->add_spinner("Segments:", GLUI_SPINNER_INT, &segments);
	//segment_spinner->set_int_limits(3, 60);

	glui->set_main_gfx_window(main_window);


	segment_spinner =  //Can be used for T in Program 5
		glui->add_spinner("Zoom Level:", GLUI_SPINNER_FLOAT, &spinnerFloat);
	segment_spinner->set_float_limits(0.0,1.5);

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

	glui->add_column();
	glui->add_panel("Cube selector");
	glui->add_button("Select Next", 1, cubeSelector);
	glui->add_button("Select Prev", 2, cubeSelector);
	glui->add_button("Select None", 3, cubeSelector);

	glui->add_separator();
	glui->add_button("scale selected Up", 1, cubeScaler);
	glui->add_button("scale selected Down", 2, cubeScaler);



	


	//GLUI_RadioGroup* group1 = glui->add_radiogroup_to_panel(obj_panel);
	//glui->add_radiobutton_to_group(group1, "Option 1");
	//glui->add_radiobutton_to_group(group1, "Option 2");

	/* We register the idle callback with GLUI, *not* with GLUT */
	GLUI_Master.set_glutIdleFunc(myGlutIdle);
	GLUI_Master.set_glutReshapeFunc(resize);

	glutMainLoop();
	return 0;
	
}
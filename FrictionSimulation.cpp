#include <string>
#include "FrictionSimulation.h"
#include "glut.h"


//Box(int id, double x, double y, double w, double h, double vx, double vy, double ax, double ay, double d,
//	double red, double green, double blue, double mass, double time, bool graivtyon, bool frictionon, bool displaymass);
FrictionSimulation::FrictionSimulation(int screenx, int screeny) {
	mScreen_x = screenx;
	mScreen_y = screeny;
	//tilted
	//Box b1(1, 550, 450, 20, 20, 0, 0, 0, 0, 45, .2, .7, .3, 25, 0, true, true, false);
	Box b1(1, 50, 500/2, 20, 20, 2, 0, 0, 0, 0, .2, .7, .3, 25, 0, false, true, false);

	mBoxes.push_back(b1);
}


vector<Box> FrictionSimulation::getBoxes() {
	return mBoxes;
}

void FrictionSimulation::DrawGround() {
	// Tilted
	/*glColor3d(.8, .8, .8);
	glBegin(GL_POLYGON);
	glVertex2d(700, 0);
	glVertex2d(0, 0);
	glVertex2d(0, 450);
	glVertex2d(700, 100);
	glEnd();*/

	glColor3d(.7, .7, .7);
	glBegin(GL_QUADS);
	glVertex2d(0, 0);
	glVertex2d(mScreen_x, 0);
	glVertex2d(mScreen_x, mScreen_y / 2);
	glVertex2d(0, mScreen_y / 2);
	glEnd();
}

vector<Box> FrictionSimulation::Reset() {
	vector<Box> newBoxes;
	//Box b1(1, 550, 450, 20, 20, 0, 0, 0, 0, 45, .2, .7, .3, 25, 0, true, true, false);
	Box b1(1, 50, 500 / 2, 20, 20, 2, 0, 0, 0, 0, .2, .7, .3, 25, 0, false, true, false);
	newBoxes.push_back(b1);
	return newBoxes;
}

void DrawTextFS(double x, double y, const char* string)
{
	void* font = GLUT_BITMAP_9_BY_15;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	int len, i;
	glRasterPos2d(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}

	glDisable(GL_BLEND);
}

void FrictionSimulation::DrawScale() {
	glColor3d(0, 0, 0);
	for (int i = 0; i < mScreen_x; i += 50) {
		std::string str = to_string(i / 50);
		char buffer[50];
		strcpy_s(buffer, str.c_str());
		DrawTextFS(i, 0, "|");
		DrawTextFS(i, 15, buffer);
	}
	for (int i = 1; i < mScreen_x; i += 50) {
		std::string str = to_string(i / 50);
		char buffer[50];
		strcpy_s(buffer, str.c_str());
		DrawTextFS(0, i + 5, "_");
		DrawTextFS(15, i, buffer);
	}
}

void FrictionSimulation::CalculateFriction(vector<Box>& b, double time){
	// y direction: Σfy = 0;
	// n_force - mass * g = 0
	// n_force = mass * g
	double n_force = b[0].getmMass() * -9.8;
}
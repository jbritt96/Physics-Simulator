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
	Box b1snap(1, 50, 500 / 2, 20, 20, 2, 0, 0, 0, 0, 0, 0, 1, 25, 0, false, true, false);

	mBoxes.push_back(b1);
	mSnapshots.push_back(b1snap);
}

vector<Box> FrictionSimulation::Reset() {
	vector<Box> newBoxes;
	vector<Box> newSnapshots;
	//Box b1(1, 550, 450, 20, 20, 0, 0, 0, 0, 45, .2, .7, .3, 25, 0, true, true, false);
	Box b1(1, 50, 500 / 2, 20, 20, 2, 0, 0, 0, 0, .2, .7, .3, 25, 0, false, true, false);
	Box b1snap(1, 50, 500 / 2, 20, 20, 2, 0, 0, 0, 0, 0, 0, 1, 25, 0, false, true, false);

	newBoxes.push_back(b1);
	newSnapshots.push_back(b1snap);
	mSnapshots = newSnapshots;
	return newBoxes;
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

void FrictionSimulation::Trace(double time, vector<Box>& b) {
	if (mSnapshots.size() - 1 < (int)time * 2) {
		for (int i = 0; i < mBoxes.size(); i++) {
			int id = b[i].getmID();
			double x = b[i].getmX();
			double y = b[i].getmY();
			double vx = b[i].getmVx();
			double vy = b[i].getmVy();
			double w = b[i].getmW();
			double h = b[i].getmH();
			double d = b[i].getmD();
			double red = b[i].getmRed();
			double green = b[i].getmGreen();
			double blue = b[i].getmBlue();
			double mass = b[i].getmMass();

			mSnapshots.push_back(Box(id, x, y, w, h, vx, vy, 0, 0, d, 0, 0, 1, mass, time, false, false, false));
		}
	}



	for (int i = 0; i < mSnapshots.size() - 1; i++) {
		glColor3d(0, 0, 0);
		glBegin(GL_LINE_STRIP);
		glVertex2d(mSnapshots[i].getmX() + (mSnapshots[i].getmW() / 2), mSnapshots[i].getmY() + (mSnapshots[i].getmH() / 2));
		glVertex2d(mSnapshots[i + 1].getmX() + (mSnapshots[i + 1].getmW() / 2), mSnapshots[i + 1].getmY() + (mSnapshots[i + 1].getmH() / 2));
		glEnd();
	}

	for (int i = 0; i < mSnapshots.size(); i++) {
		mSnapshots[i].Draw();
	}
}

void FrictionSimulation::DisplayTraceInformation(int i) {
	double time = mSnapshots[i].getmTime();
	double xpos = mSnapshots[i].getmX() / 50;
	double ypos = mSnapshots[i].getmY() / 50;
	double xvel = mSnapshots[i].getmVx() / 50;
	double yvel = mSnapshots[i].getmVy() / 50;

	glColor3d(.8, .8, .8);
	glBegin(GL_QUADS);
	glVertex2d(240, 45);
	glVertex2d(240, 130);
	glVertex2d(430, 130);
	glVertex2d(430, 45);
	glEnd();


	char buffer[50];
	glColor3d(0, 0, 0);
	// text for time
	DrawTextFS(304, 115, "time:");
	std::string str = to_string(time);
	strcpy_s(buffer, str.c_str());
	DrawTextFS(350, 115, buffer);

	// text for x pos
	DrawTextFS(250, 100, "x position:");
	str = to_string(xpos);
	strcpy_s(buffer, str.c_str());
	DrawTextFS(350, 100, buffer);

	// text for y pos
	DrawTextFS(250, 85, "y position:");
	str = to_string(ypos);
	strcpy_s(buffer, str.c_str());
	DrawTextFS(350, 85, buffer);

	// text for x vel
	DrawTextFS(250, 70, "x velocity:");
	str = to_string(xvel);
	strcpy_s(buffer, str.c_str());
	DrawTextFS(350, 70, buffer);

	// text for y vel
	DrawTextFS(250, 55, "y velocity:");
	str = to_string(yvel);
	strcpy_s(buffer, str.c_str());
	DrawTextFS(350, 55, buffer);
}

vector<Box> FrictionSimulation::getSnapshots() {
	return mSnapshots;
}
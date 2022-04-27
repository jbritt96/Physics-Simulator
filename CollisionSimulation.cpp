#include <iostream>
#include "CollisionSimulation.h"
#include "glut.h"


//Box(int id, double x, double y, double w, double h, double vx, double vy, double ax, double ay, double d,
//	double red, double green, double blue, double mass, double time, bool graivtyon, bool frictionon, bool displaymass);
CollisionSimulation::CollisionSimulation(int screen_x, int screen_y) {
	mScreen_x = screen_x;
	mScreen_y = screen_y;
	
	// CREATE BOXES HERE
	Box box1(1, 50, 500 / 2, 20, 20, 1, 0, 0, 0, 0, 1, 0, 0, 10, 0, false, false, true);
	Box box2(2, 550, 500 / 2, 100, 100, -2, 0, 0, 0, 0, 0, 0, 1, 40, 0, false, false, true);
	Box box3(3, 350, 500 / 2, 40, 40, -.5, 0, 0, 0, 0, 0, 1, 0, 15, 0, false, false, true);
	mBoxes.push_back(box1);
	mBoxes.push_back(box2);
	mBoxes.push_back(box3);

	//Box box1(1, 550, 500 / 2, 100, 100, -2, 0, 0, 0, 0, 0, 0, 1, 40, 0, false, false, true);
	//Box box2(2, 50, 500 / 2, 100, 100, 2, 0, 0, 0, 0, 1, 0, 0, 40, 0, false, false, true);
	//mBoxes.push_back(box1);
	//mBoxes.push_back(box2);
}

vector<Box> CollisionSimulation::Reset() {
	vector<Box> newBoxes;
	Box box1(1, 50, 500 / 2, 20, 20, 1, 0, 0, 0, 0, 1, 0, 0, 10, 0, false, false, true);
	Box box2(2, 550, 500 / 2, 100, 100, -2, 0, 0, 0, 0, 0, 0, 1, 40, 0, false, false, true);
	Box box3(3, 350, 500 / 2, 40, 40, -.5, 0, 0, 0, 0, 0, 1, 0, 15, 0, false, false, true);

	//Box box1(1, 550, 500 / 2, 100, 100, -2, 0, 0, 0, 0, 0, 0, 1, 40, 0, false, false, true);
	//Box box2(2, 50, 500 / 2, 100, 100, 2, 0, 0, 0, 0, 1, 0, 0, 40, 0, false, false, true);
	newBoxes.push_back(box1);
	newBoxes.push_back(box2);
	newBoxes.push_back(box3);
	return newBoxes;
}

vector<Box> CollisionSimulation::getBoxes() {
	return mBoxes;
}


//equation found here https://en.wikipedia.org/wiki/Elastic_collision
void CollisionSimulation::calculateCollision(vector<Box>& b) {
	for (int i = 0; i < b.size(); i++) {
		for (int j = 0; j < b.size(); j++) {
			if (i != j) {
				double nextXi = b[i].getmX() + b[i].getmVx();
				double nextXj = b[j].getmX() + b[j].getmVx();
				if (!(nextXi + b[i].getmW() < nextXj || nextXi > nextXj + b[j].getmW())) {
					double totalM = b[i].getmMass() + b[j].getmMass();
					// calculate v1 for b1
					double newv1 = ((b[i].getmMass() - b[j].getmMass()) / totalM) * b[i].getmVx();
					newv1 += ((2 * b[j].getmMass()) / totalM) * b[j].getmVx();

					// calculate v2 for b2
					double newv2 = ((2 * b[i].getmMass()) / totalM) * b[i].getmVx();
					newv2 += ((b[j].getmMass() - b[i].getmMass()) / totalM) * b[j].getmVx();


					b[i].setmVx(newv1);
					b[j].setmVx(newv2);
				}
			}
		}
	}
}

void CollisionSimulation::DrawGround() {
	glColor3d(.7, .7, .7);
	glBegin(GL_QUADS);
	glVertex2d(0, 0);
	glVertex2d(mScreen_x, 0);
	glVertex2d(mScreen_x, mScreen_y / 2);
	glVertex2d(0, mScreen_y / 2);
	glEnd();
}

void DrawTextCS(double x, double y, const char* string)
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

void CollisionSimulation::DrawScale() {
	glColor3d(0, 0, 0);
	for (int i = 0; i < mScreen_x; i += 50) {
		std::string str = to_string(i/50);
		char buffer[50];
		strcpy_s(buffer, str.c_str());
		DrawTextCS(i, 0, "|");
		DrawTextCS(i, 15, buffer);
	}
	for (int i = 1; i < mScreen_x; i += 50) {
		std::string str = to_string(i / 50);
		char buffer[50];
		strcpy_s(buffer, str.c_str());
		DrawTextCS(0, i + 5, "_");
		DrawTextCS(15, i, buffer);
	}
}

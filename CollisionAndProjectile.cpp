#include <iostream>
#include <string>
#include "CollisionAndProjectile.h"


// Box(int id, double x, double y, double w, double h, double vx, double vy, double ax, double ay, double d, double red, double green, double blue, double mass, bool graivtyon, bool frictionon)
CollisionAndProjectile::CollisionAndProjectile(int screen_x, int screen_y) {
	mScreen_x = screen_x;
	mScreen_y = screen_y;
	Box b1(1, 50, 0, 20, 20,
		50, 175, 0, -9.8,
		0, 1, 0, 0, 10, 0,
		true, false, false);

	Box b2(2, 500, 1, 20, 20,
		-50, -175, 0, -9.8,
		0, 0, 0, 0, 10, 0,
		true, false, false);

	Box b1snap(1, 50, 0, 20, 20,
		50, 175, 0, -9.8,
		0, 0, 0, 1, 10, 0,
		true, false, false);

	mBoxes.push_back(b1);
	mBoxes.push_back(b2);
	mSnapshots.push_back(b1snap);
}


vector<Box> CollisionAndProjectile::getBoxes() {
	return mBoxes;
}

vector<Box> CollisionAndProjectile::getSnapshots() {
	return mSnapshots;
}

vector<Box> CollisionAndProjectile::Reset() {
	vector<Box> newBoxes;
	vector<Box> newSnapshots;
	Box b1(1, 50, 0, 20, 20,
		50, 175, 0, -9.8,
		0, 1, 0, 0, 10, 0,
		true, false, false);

	Box b1snap(1, 50, 0, 20, 20,
		50, 175, 0, -9.8,
		0, 0, 0, 1, 10, 0,
		true, false, false);

	newBoxes.push_back(b1);
	newSnapshots.push_back(b1snap);
	mSnapshots = newSnapshots;

	return newBoxes;
}


void CollisionAndProjectile::calculateProjectile(vector<Box>& b, double time) {
	if (b[0].getmY() >= 0) {
		for (int i = 0; i < b.size(); i++) {
			static double x0 = b[i].getmX0();
			static double xv0 = b[i].getmVx0();
			double xv = b[i].getmVx();
			double xa = b[i].mAx;

			// calculate x position
			//double newx = x0 + (xv0 * time) + pow(.5 * xa * time, 2);

			// double newx = x0 + (xv * time) * 200;
			double newx = x0 + (xv0 * time) + (.5 * xa * pow(time * 2, 2));
			b[i].setmX(newx);

			static double y0 = b[i].getmY0();
			static double yv0 = b[i].getmVy0();
			double yv = b[i].getmVy();
			double ya = b[i].mAy;

			// calculate x position
			//double newx = x0 + (xv0 * time) + pow(.5 * xa * time, 2);

			//double newy = y0 + (yv * time) * 100;
			double newy = y0 + (yv0 * time) + (.5 * ya * pow(time * 2, 2));
			b[i].setmY(newy);

			double newvx = xv0 + (xa * time * 2);
			double newvy = yv0 + (ya * time * 2);
			b[i].setmVx(newvx);
			b[i].setmVy(newvy);
		}
	}
}

void CollisionAndProjectile::calculateCollision(vector<Box>& b) {
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



void DrawTextCPM(double x, double y, const char* string)
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

void CollisionAndProjectile::DrawScale() {
	glColor3d(0, 0, 0);
	for (int i = 0; i < mScreen_x; i += 50) {
		std::string str = to_string(i / 50);
		char buffer[50];
		strcpy_s(buffer, str.c_str());
		DrawTextCPM(i, 0, "|");
		DrawTextCPM(i, 15, buffer);
	}
	for (int i = 1; i < mScreen_x; i += 50) {
		std::string str = to_string(i / 50);
		char buffer[50];
		strcpy_s(buffer, str.c_str());
		DrawTextCPM(0, i + 5, "_");
		DrawTextCPM(15, i, buffer);
	}
}


// Box(int id, double x, double y, double w, double h, double vx, double vy, double ax, double ay, double d, double red, double green, double blue, double mass, bool graivtyon, bool frictionon)
void CollisionAndProjectile::Trace(double time, vector<Box>& b) {
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

void CollisionAndProjectile::DisplayTraceInformation(int i) {
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
	DrawTextCPM(304, 115, "time:");
	std::string str = to_string(time);
	strcpy_s(buffer, str.c_str());
	DrawTextCPM(350, 115, buffer);

	// text for x pos
	DrawTextCPM(250, 100, "x position:");
	str = to_string(xpos);
	strcpy_s(buffer, str.c_str());
	DrawTextCPM(350, 100, buffer);

	// text for y pos
	DrawTextCPM(250, 85, "y position:");
	str = to_string(ypos);
	strcpy_s(buffer, str.c_str());
	DrawTextCPM(350, 85, buffer);

	// text for x vel
	DrawTextCPM(250, 70, "x velocity:");
	str = to_string(xvel);
	strcpy_s(buffer, str.c_str());
	DrawTextCPM(350, 70, buffer);

	// text for y vel
	DrawTextCPM(250, 55, "y velocity:");
	str = to_string(yvel);
	strcpy_s(buffer, str.c_str());
	DrawTextCPM(350, 55, buffer);
}
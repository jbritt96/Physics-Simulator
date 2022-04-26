#include <iostream>
#include <string>
#include "Box.h"
#include "glut.h"

Box::Box(int id, double x, double y, double w, double h, double vx, double vy, double ax, double ay, double d,
		double red, double green, double blue, double mass, double time, bool graivtyon, bool frictionon, bool displaymass) {
	mID = id;
	mX = x;
	mY = y;
	mW = w;
	mH = h;
	mVx = vx;
	mVy = vy;
	mD = d;
	mRed = red;
	mGreen = green;
	mBlue = blue;
	mMass = mass;
	mTime = time;

	mGravityOn = graivtyon;
	mFrictionOn = frictionon;
	mDisplayMass = displaymass;

	mX0 = x;
	mY0 = y;
	mVx0 = vx;
	mVy0 = vy;
	mAx = ax;
	mAy = ay;
}

void DrawTextB(double x, double y, const char* string)
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

void Box::Draw() {
	glColor3d(mRed, mGreen, mBlue);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslated(mX, mY, 0);
	glRotated(mD, 0, 0, 1);
	glBegin(GL_QUADS);
	glVertex2d(0, 0);
	glVertex2d(mW, 0);
	glVertex2d(mW, mH);
	glVertex2d(0, mH);
	
	glEnd();
	glPopMatrix();
	

	if (mDisplayMass) {
		int intmass = (int)mMass;
		std::string str = to_string(intmass);
		char buffer[50];
		strcpy_s(buffer, str.c_str());
		glColor3d(-mRed, -mGreen, -mBlue);
		DrawTextB(mX, mY, buffer);
	}

}

void Box::Update(int screen_x, int screen_y) {
	if (mGravityOn) {
		const double G = .03;
		mVy -= G;
	}

	if (mFrictionOn) {
		const double FRICTION = .997;
		mVx *= FRICTION;
		mVy *= FRICTION;
	}

	if (mX + mVx < 0 || mX + mW + mVx > screen_x) {
		mVx = -mVx;
	}

	if (mY + mVy < 0 || mY + mH + mVy > screen_y) {
		mVy = -mVy;
	}


	mX += mVx;
	mY += mVy;
}



double Box::getmX() {
	return mX;
}
void Box::setmX(double x) {
	mX = x;
}
double Box::getmY() {
	return mY;
}
void Box::setmY(double y) {
	mY = y;
}
double Box::getmVx() {
	return mVx;
}
void Box::setmVx(double vx) {
	mVx = vx;
}
double Box::getmVy() {
	return mVy;
}
void Box::setmVy(double vy) {
	mVy = vy;
}
double Box::getmMass() {
	return mMass;
}
double Box::getmW() {
	return mW;
}
double Box::getmH() {
	return mH;
}

double Box::getmD() {
	return mD;
}

void Box::setmD(double d) {
	mD = d;
}

double Box::getmX0() {
	return mX0;
}

double Box::getmY0() {
	return mY0;
}

double Box::getmVx0() {
	return mVx0;
}

double Box::getmVy0() {
	return mVy0;
}

double Box::getmRed() {
	return mRed;
}
double Box::getmGreen() {
	return mGreen;
}
double Box::getmBlue() {
	return mBlue;
}

int Box::getmID() {
	return mID;
}

double Box::getmTime() {
	return mTime;
}
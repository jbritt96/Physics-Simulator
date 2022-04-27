#pragma once
#include <vector>
#include "glut.h"

using namespace std;

class Box {
public:
	Box(int id, double x, double y, double w, double h, double vx, double vy, double ax, double ay, double d, 
		double red, double green, double blue, double mass, double time, bool graivtyon, bool frictionon, bool displaymass);
	void Draw();
	void Update(int screen_x, int screen_y);
	
	double getmX();
	double getmY();
	double getmVx();
	double getmVy();
	double getmMass();
	double getmW();
	double getmH();
	double getmD();
	double getmX0();
	double getmY0();
	double getmVx0();
	double getmVy0();
	double getmTime();
	double getmRed();
	double getmGreen();
	double getmBlue();
	int getmID();

	void setmX(double x);
	void setmY(double y);
	void setmVx(double vx);
	void setmVy(double vy);
	void setmD(double d);

	double mAx; // x accel
	double mAy; // y accel
private:
	int mID;
	double mX;  // x pos
	double mX0; // initial x pos
	double mY;  // y pos
	double mY0; // initial y pos
	double mW;  // width of box
	double mH;  // height of box
	double mVx; // x vel
	double mVx0; // initial x vel
	double mVy; // y vel
	double mVy0; // initial y vel
	double mD;  // degree of rotation
	double mTime; // Only used for Trace function
	
	double mRed;
	double mGreen;
	double mBlue;
	double mMass;
	bool mGravityOn;
	bool mFrictionOn;
	bool mDisplayMass;
};
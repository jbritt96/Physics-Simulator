#pragma once

#include <vector>
#include "Box.h"

using namespace std;


class ProjectileMotionSimulation {
public:
	ProjectileMotionSimulation(int screen_x, int screen_y);
	void calculateProjectile(vector<Box>& b, double time);
	vector<Box> getBoxes();
	vector<Box> getSnapshots();
	vector<Box> Reset();
	void DrawScale();
	void Trace(double time, vector<Box>& b);
	void DisplayTraceInformation(int i);
private:
	vector<Box> mBoxes;
	vector<Box> mSnapshots;
	int mScreen_x;
	int mScreen_y;
};
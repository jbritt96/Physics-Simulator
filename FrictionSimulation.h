#pragma once
#include "Box.h"

class FrictionSimulation {
public:
	FrictionSimulation(int screenx, int screeny);
	void CalculateFriction(vector<Box>& b, double time);
	vector<Box> getBoxes();
	void DrawGround();
	vector<Box> Reset();
	void DrawScale();
private:
	vector<Box> mBoxes;
	int mScreen_x;
	int mScreen_y;
};
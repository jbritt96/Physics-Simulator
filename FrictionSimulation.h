#pragma once
#include "Box.h"

class FrictionSimulation {
public:
	FrictionSimulation(int screenx, int screeny);
	vector<Box> getBoxes();
	void DrawGround();
	vector<Box> Reset();
	void DrawScale();
	void Trace(double time, vector<Box>& b);
	void DisplayTraceInformation(int i);
	vector<Box> getSnapshots();
private:
	vector<Box> mBoxes;
	vector<Box> mSnapshots;
	int mScreen_x;
	int mScreen_y;
};
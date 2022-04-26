#include <string>
#include <vector>
#include "Box.h"

using namespace std;


class CollisionSimulation {
public:
	CollisionSimulation(int screen_x, int screen_y);

	//equation found here https://en.wikipedia.org/wiki/Elastic_collision
	void calculateCollision(vector<Box> &b);
	vector<Box> getBoxes();
	vector<Box> Reset();
	void DrawGround();
	void DrawScale();
private:
	vector<Box> mBoxes;
	int mScreen_x;
	int mScreen_y;
};

#include <cmath>
#include <cstring>
#include <iostream>
#include "glut.h"
#include "Box.h"
#include "CollisionSimulation.h"
#include "ProjectileMotion.h"
#include "FrictionSimulation.h"

double screen_x = 700;
double screen_y = 500;


// 0 = collision; 1 = projectile motion; 2 = friction
int SIMULATION_CHOICE = 0; 
bool DRAW_SCALE = true;
clock_t start_time = clock();

// 0 = collision
CollisionSimulation CS(screen_x, screen_y);
vector<Box> COLLISION_BOXES = CS.getBoxes();

// 1 = projectile motion
ProjectileMotionSimulation PS(screen_x, screen_y);
vector<Box> PROJECTILE_BOXES = PS.getBoxes();
bool DRAW_TRACE = true;
bool DISPLAY_TRACE_INFO = false;
int snapshotIndex = 0; // Will be set if mouse is over trace snapshot

// 2 = friction
FrictionSimulation FS(screen_x, screen_y);
vector<Box> FRICTION_BOXES = FS.getBoxes();


double GetTime()
{
	// static clock_t start_time = clock();
	clock_t current_time = clock();
	double total_time = double(current_time - start_time) / CLOCKS_PER_SEC;
	return total_time;
}

void display(void)
{
	double t = GetTime();
	glClear(GL_COLOR_BUFFER_BIT);

	if (SIMULATION_CHOICE == 0) {
		CS.calculateCollision(COLLISION_BOXES);
		for (unsigned int i = 0; i < COLLISION_BOXES.size(); i++) {
			COLLISION_BOXES[i].Draw();
		}
		for (unsigned int i = 0; i < COLLISION_BOXES.size(); i++) {
			COLLISION_BOXES[i].Update(screen_x, screen_y);
		}
		CS.DrawGround();
		if (DRAW_SCALE) {
			CS.DrawScale();
		}
	}

	if (SIMULATION_CHOICE == 1) {
		PS.calculateProjectile(PROJECTILE_BOXES, t);
		if (DRAW_SCALE) {
			PS.DrawScale();
		}
		if (DRAW_TRACE) {
			PS.Trace(t, PROJECTILE_BOXES);
			if (DISPLAY_TRACE_INFO) {
				if (snapshotIndex != -1){
					PS.DisplayTraceInformation(snapshotIndex);
				}
			}
		}
		for (unsigned int i = 0; i < PROJECTILE_BOXES.size(); i++) {
			PROJECTILE_BOXES[i].Draw();
		}
	}

	if (SIMULATION_CHOICE == 2) {
		for (unsigned int i = 0; i < FRICTION_BOXES.size(); i++) {
			FRICTION_BOXES[i].Update(screen_x, screen_y);
		}
		FS.DrawGround();
		if (DRAW_SCALE) {
			FS.DrawScale();
		}
		
		if (DRAW_TRACE) {
			FS.Trace(t, FRICTION_BOXES);
			if (DISPLAY_TRACE_INFO) {
				if (snapshotIndex != -1) {
					FS.DisplayTraceInformation(snapshotIndex);
				}
			}
		}
		for (unsigned int i = 0; i < FRICTION_BOXES.size(); i++) {
			FRICTION_BOXES[i].Draw();
		}
	}
	glutSwapBuffers();
	glutPostRedisplay();
}


void keyboard(unsigned char c, int x, int y)
{
	switch (c) 
	{
		case 27:
			exit(0);
			break;
		case 'a':
			snapshotIndex = -1;
			SIMULATION_CHOICE = 0;
			break;
		case 's':
			snapshotIndex = -1;
			SIMULATION_CHOICE = 1;
			break;
		case 'd':
			snapshotIndex = -1;
			SIMULATION_CHOICE = 2;
			break;
		case 'r':
			if (SIMULATION_CHOICE == 0) {
				COLLISION_BOXES = CS.Reset();
			} else if (SIMULATION_CHOICE == 1) {
				PROJECTILE_BOXES = PS.Reset();
				start_time = clock();
			} else if (SIMULATION_CHOICE == 2) {
				FRICTION_BOXES = FS.Reset();
			}
			break;
		case 'z':
			if (DRAW_SCALE){
				DRAW_SCALE = false;
			}
			else {
				DRAW_SCALE = true;
			}
			break;
		case 'x':
			if (DRAW_TRACE && (SIMULATION_CHOICE == 1 || SIMULATION_CHOICE == 2)) {
				DRAW_TRACE = false;
			}
			else {
				DRAW_TRACE = true;
			}
			break;
		default:
			return;
	}

	glutPostRedisplay();
}


void reshape(int w, int h)
{
	screen_x = w;
	screen_y = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);

}

void mousemotion(int x, int y) {
	if (SIMULATION_CHOICE == 1){
		vector<Box> snapshots = PS.getSnapshots();
		bool foundBox = false;
		for (int i = 0; i < snapshots.size(); i++){
			if (snapshots[i].getmX() < x && snapshots[i].getmX() + snapshots[i].getmW() > x && snapshots[i].getmY() < screen_y - y && snapshots[i].getmY() + snapshots[i].getmH() > screen_y - y) {
				snapshotIndex = i;
				foundBox = true;
				DISPLAY_TRACE_INFO = true;
				break;
			}
		}
		if (!foundBox) {
		snapshotIndex = -1;
		}
	}
	if (SIMULATION_CHOICE == 2) {
		vector<Box> snapshots = FS.getSnapshots();
		bool foundBox = false;
		for (int i = 0; i < snapshots.size(); i++) {
			if (snapshots[i].getmX() < x && snapshots[i].getmX() + snapshots[i].getmW() > x && snapshots[i].getmY() < screen_y - y && snapshots[i].getmY() + snapshots[i].getmH() > screen_y - y) {
				snapshotIndex = i;
				foundBox = true;
				DISPLAY_TRACE_INFO = true;
				break;
			}
		}
		if (!foundBox) {
			snapshotIndex = -1;
		}
	}
}

int main(int argc, char **argv)
{
	cout << "Hotkeys:" << endl
		<< "a: Elastic collisions, s: Projectile Motion, d: Friction (not fully implemented)" << endl
		<< "r: reset currently selected simulation" << endl
		<< "z: Toggle scale, x: Toggle snapshots";

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screen_x, screen_y);
	glutInitWindowPosition(50, 50);

	int fullscreen = 0;
	if (fullscreen) 
	{
		glutGameModeString("800x600:32");
		glutEnterGameMode();
	} 
	else 
	{
		glutCreateWindow("Simulator");
	}

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
;
	glutPassiveMotionFunc(mousemotion);

	glColor3d(0,0,0); // forground color
	glClearColor(1, 1, 1, 0); // background color


	glutMainLoop();

	return 0;
}

// Lab 4, terrain generation

#ifdef __APPLE__
	#include <OpenGL/gl3.h>
	// Linking hint for Lightweight IDE
	// uses framework Cocoa
#endif

#include "../common/Linux/MicroGlut.h"
#include "../common/GL_utilities.h"
#include "../common/loadobj.h"
#include "../common/VectorUtils3.h"
#include "../common/LoadTGA.h"
#include "../common/simplefont.h"
#include "../common/simplefont.h"

#include <math.h>
#include <stdlib.h>
#include "src/sphere.h"
#include "src/ground.h"

mat4 projectionMatrix;
Sphere player, sphere1;
// Reference to shader program
GLuint program;
GLuint tex0;
Ground ground;//ground


void init(void)
{
	// GL inits
	glClearColor(0.2,0.2,0.5,0);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	printError("GL inits");

	projectionMatrix = frustum(-0.1, 0.1, -0.1, 0.1, 0.2, 50.0);


	// Load and compile shader
	program = loadShaders("shader/shader.vert", "shader/shader.frag");
	glUseProgram(program);
	printError("init shader");

	glUniformMatrix4fv(glGetUniformLocation(program, "projMatrix"), 1, GL_TRUE, projectionMatrix.m);


	//load model
	ground.init();

	player.init(0);
	sphere1.init(1);
	sphere1.setPosition(-3.0,1.0,0.0);
	sfMakeRasterFont(); // init font

}

// angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f,z=8.0f,y=3.0f;

float deltaAngle = 0.0f;
int xOrigin = -1;

void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
		}
		else  {// state = GLUT_DOWN
			xOrigin = x;
		}
	}
}
void mouseMove(int x, int y) {

	// this will only be true when the left button is down
	if (xOrigin >= 0) {

		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;

		// update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}
}



void keyboard(unsigned char key,  int xx, int yy) {

	float fraction = 0.1f;
	float velocity = 0.5f;

	switch (key) {
		case 'i' :
			player.moveForward();
			break;
		case 'j' :
			player.moveLeft();
			break;
		case 'l' :
			player.moveRight();
			break;
		case 'k' :
			player.moveBack();
			break;
		case 'a' :
			angle -= 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case 'd' :
			angle += 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case 'w' :
			x += lx * fraction;
			z += lz * fraction;
			break;
		case 's' :
			x -= lx * fraction;
			z -= lz * fraction;
			break;
		case 'z' :
			y+=0.01;
			break;
		case 'x' :
			y-=0.01;
			break;
		case 'q' :
			exit(1);
			break;
	}
}

int score=0;

void display_score(){
	char outString[28]; // enough to hold all numbers up to 64-bits and "Score: "
	const char * a;
    a = "Score: ";
	sprintf(outString,"%s%d",a,score);
	sfDrawString(20, 20, outString);

}
float x_obj1=0.0f,x_obj2=5.0f, z_obj1=0.0f,z_obj2=5.0f;
bool collision_state=false;
void display(void)
{
	// clear the screen

	printError("pre display");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	

	glUseProgram(program);

	// Build matrix
	mat4 total=lookAt(x, y, z,
		x+lx, y,  z+lz,
		0.0f, 1.0f,  0.0f);
	glUniformMatrix4fv(glGetUniformLocation(program, "mdlMatrix"), 1, GL_TRUE, total.m);

	//draw model

	ground.draw(total,program);
	display_score();
	player.draw(total,program);
	sphere1.draw(total,program);
	if(!collision_state && player.collision(sphere1)){
		printf("colision\n");
		score++;
		collision_state=true;
	}
	if(collision_state && !player.collision(sphere1)){
		printf("no colision\n");
		collision_state=false;
	}
	
	

	printError("post display ");
	glutSwapBuffers();
}

void timer(int i){
	glutTimerFunc(20, &timer, i);
	glutPostRedisplay();
}


int main(int argc, char **argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH |  GLUT_RGB);
	glutInitContextVersion(3, 2);
	glutInitWindowSize (600, 600);
	glutCreateWindow ("TSBK07 project");
	glutDisplayFunc(display);
	init ();
	glutTimerFunc(20, &timer, 0);

	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
	glutKeyboardFunc(keyboard);
	
	glutMainLoop();
	exit(0);
}

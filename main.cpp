#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

float pi = 3.1416;
int sides = 120;//higher->smoother circle max = 360
int deg = 0;//used for sin() cos() calculations
float deg_inc = 360/sides;//degree increment: kinuha ko lang ung degree ng each "slice" nung circle when divided by n amount of sides

//radius of circles
GLfloat r_sun = 0.15f;
GLfloat r_earth = 0.08f;
GLfloat r_moon = 0.02f;

//starting position sa x axis
//none for sun kase nasa gitna sya
GLfloat x_earth = -0.5f;
GLfloat x_moon = -0.7f;

//used para hindi "stretched" yung maging output
//basically i t-times lang naten all y-values by the aspect ratio(1920/1080) of most screens
float ratio = 1.78f;// 1920/1080;
float r = 1.78f;
	
using namespace std;
void display();
void keyControls(unsigned char key, int x, int y);
void mouseControls(int button, int state, int x, int y);
void setColor(int r, int g, int b);

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutCreateWindow("");
	glutFullScreen();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyControls);
	glutMouseFunc(mouseControls);
	glutMainLoop();
}
 
void display(){
  //will be converted into VBO by assigning the for loop calculations to a vertex array rather than passing to glVertex()
  //for now glVertex muna for simplicity kase design phase pa lang naman
	glClear(GL_COLOR_BUFFER_BIT);
  
  //sun
	glBegin(GL_POLYGON);
	setColor(252, 242, 202);//sariling func para i c-copy paste ko lng ung rgb from a color picker tool
	for(int i = 0; i < sides; i++){
    //x = radius * cos(radians);   y = radius * sin(radians);   radians = (deg * pi)/180
		glVertex2f((r_sun * cos(deg * pi / 180)), (ratio * r_sun * sin(deg * pi / 180)));

    //increase degree para sa next iter
		deg += deg_inc;
	}
	deg = 0;//reset degree for next circle
	glEnd();

  //earth
	glBegin(GL_POLYGON);
	setColor(43, 100, 117);
	for(int i = 0; i < sides; i++){
		glVertex2f((r_earth * cos(deg * pi / 180)) + x_earth, (ratio * r_earth * sin(deg * pi / 180)));

		deg += deg_inc;
	}
	deg = 0;
	glEnd();

  //moon
	glBegin(GL_POLYGON);
	setColor(55, 64, 64);
	for(int i = 0; i < sides; i++){
		glVertex2f((r_moon * cos(deg * pi / 180)) + x_moon, (ratio * r_moon * sin(deg * pi / 180)));

		deg += deg_inc;
	}
	deg = 0;
	glEnd();

  // BIG STARS
		glPointSize(5.0);
		glBegin(GL_POINTS); 
		
			glColor3f(1.0, 1.0, 1.0);
			glVertex2f(0.21*r, 0.20*r);
			glVertex2f(0.20*r, -0.24*r);
			glVertex2f(-0.28*r, 0.19*r);
			glVertex2f(-0.20*r, -0.20*r);
			glVertex2f(0.52*r, 0.5*r);
			glVertex2f(0.5*r, -0.54*r);
			glVertex2f(-0.54*r, 0.53*r);
			glVertex2f(-0.48*r, 0.0*r);
			glVertex2f(0.3*r, 0.5*r);
			glVertex2f(0.5*r, 0.3*r);
			glVertex2f(0.0*r, 0.3*r);
			glVertex2f(0.0*r, -0.3*r);
			glVertex2f(0.35*r, 0.0*r);
			glVertex2f(0.0*r, 0.0*r);
			glVertex2f(-0.19*r, -0.1*r);
			glVertex2f(-0.5*r, -0.5*r);
			glVertex2f(-0.35*r, -0.46*r);
			glVertex2f(0.3*r, -0.33*r);
			glVertex2f(0.1*r, -0.48*r);
			glVertex2f(-0.36*r, 0.43*r);
			glVertex2f(0.35*r, -0.21*r);
			glVertex2f(-0.35*r, -0.21*r);
			glVertex2f(-0.1*r, -0.53*r);
			glVertex2f(-0.05*r, 0.55*r);
		
		glEnd();
		
	// SMALL STARS
		glPointSize(2.0);
		glBegin(GL_POINTS); 
		
		glColor3f(1.0, 1.0, 1.0);
		
			glVertex2f(-0.1*r, 0.1*r);
			glVertex2f(0.1*r, 0.3*r);
			glVertex2f(0.0*r, 0.15*r);
			glVertex2f(0.15*r, 0.0*r);
			glVertex2f(-0.04*r, -0.1*r);
			glVertex2f(-0.47*r, -0.33*r);
			glVertex2f(-0.2*r, -0.4*r);
			glVertex2f(-0.3*r, 0.0*r);
			glVertex2f(-0.2*r, 0.4*r);
			glVertex2f(0.4*r, -0.4*r);
			glVertex2f(0.5*r, -0.1*r);
			glVertex2f(0.23*r, -0.36*r);
			glVertex2f(0.13*r, -0.24*r);
			glVertex2f(0.37*r, 0.31*r);
			glVertex2f(-0.4*r, 0.2*r);
			glVertex2f(-0.53*r, 0.13*r);
		
		glEnd();
	
	glFlush();
}

void setColor(int r, int g, int b){
	glColor3f((r/255.0f), (g/255.0f), (b/255.0f));
}

void keyControls(unsigned char key, int x, int y){
}

void mouseControls(int button, int state, int x, int y){
}

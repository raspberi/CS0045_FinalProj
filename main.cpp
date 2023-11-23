#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <stdio.h>
#include <cmath>

void displayObject();
void init();
void genVertices(GLfloat r, int deg, GLfloat startpos);
void genColors(float r, float g, float b, float r_bias, float g_bias, float b_bias);
void genStars();
void drawStars();
void drawText(const char* txt, int x, int y);
void keyControls(unsigned char key, int x, int y);
void animate(int value);

GLfloat PI = 3.1416;

GLfloat stars[36000];
GLfloat vertices[3630];
GLfloat normals[3630];
GLfloat colors[3630];
GLfloat opacity[600];
int vertices_count = 0;
int normals_count = 0;
int colors_count = 0;

GLfloat camX = 0;
GLfloat camY = 0;
GLfloat camZ = 2.3;
GLfloat camUp = 1.0;

GLfloat FPS = 60.0;
GLfloat YEAR_MS = 15000.0;
GLfloat DAY_MS = YEAR_MS/365.0;
GLfloat FRAME_MS = 1000/FPS;

GLfloat x_earthCore = 1.02;
GLfloat z_earthCore = 0;
GLfloat cos_merc = cos(FRAME_MS/(0.5 * 88 * DAY_MS));
GLfloat sin_merc = sin(FRAME_MS/(0.5 * 88 * DAY_MS));
GLfloat cos_venus = cos(FRAME_MS/(0.5 * 225 * DAY_MS));
GLfloat sin_venus = sin(FRAME_MS/(0.5 * 225 * DAY_MS));
GLfloat cos_earth = cos(FRAME_MS/(0.5 * 365 * DAY_MS));
GLfloat sin_earth = sin(FRAME_MS/(0.5 * 365 * DAY_MS));
GLfloat cos_moon = cos(FRAME_MS/(0.5 * 27.3 * DAY_MS));
GLfloat sin_moon = sin(FRAME_MS/(0.5 * 27.3 * DAY_MS));
GLfloat tempX_merc = 0;
GLfloat tempZ_merc = 0;
GLfloat tempX_venus = 0;
GLfloat tempZ_venus = 0;
GLfloat tempX_earthCore = 0;
GLfloat tempZ_earthCore = 0;
GLfloat tempX_earth = 0;
GLfloat tempZ_earth = 0;
GLfloat tempX_moon = 0;
GLfloat tempZ_moon = 0;
GLfloat tempX_normal = 0;
GLfloat tempZ_normal = 0;
GLfloat x_diff = 0;
GLfloat z_diff = 0;

GLuint VBOid;
GLfloat *mappedVertices = NULL;
bool isStarted = false;

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("");
	glutFullScreen();
	init();	
	glutDisplayFunc(displayObject);
	glutKeyboardFunc(keyControls);
	glutTimerFunc(FRAME_MS, animate, 0);

	glutMainLoop();
}
 
void init(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1920.0/1080.0, 1.0, 10.0);
	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
	
	
	genVertices(0.15f, 10, 0);
	genColors(255, 255, 255, 0.2, 0, -0.7);
	
	genVertices(0.02f, 10, 0.36);
	genColors(109, 121, 140, 0, 0, 0);
	
	genVertices(0.075f, 10, 0.6525);
	genColors(140, 115, 80, 0, -0.2, 0);
	
	genVertices(0.08f, 10, 1.1);
	genColors(43, 100, 117, -0.7, 0.3, 0.2);
	
	genVertices(0.02f, 10, 1.3);
	genColors(150, 150, 150, -0.2, -0.1, -0.1);
	genStars();
	
	glewInit();
	glGenBuffers(1, &VBOid);
	glBindBuffer(GL_ARRAY_BUFFER, VBOid);
	glBufferData(GL_ARRAY_BUFFER, (3630 + 3630 + 3630)*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, (3630)*sizeof(GLfloat), 3630*sizeof(GLfloat), normals);
	glBufferSubData(GL_ARRAY_BUFFER, (3630 + 3630)*sizeof(GLfloat), 3630*sizeof(GLfloat), colors);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glNormalPointer(GL_FLOAT, 0, (GLvoid*)((3630)*sizeof(GLfloat)));
	glColorPointer(3, GL_FLOAT, 0, (GLvoid*)((3630+3630)*sizeof(GLfloat)));
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void displayObject(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	gluLookAt(camX, camY, camZ,    0.0, 0.0, 0.0,    0.0, camUp, 0.0);

//	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
//	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
//	
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
//	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
//	
//	GLfloat pos[] = {0,0,0,0.5};
//	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	
	glEnableClientState(GL_VERTEX_ARRAY);
//	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 242);
	
	glDrawArrays(GL_TRIANGLE_STRIP, 242, 242);
	
	glDrawArrays(GL_TRIANGLE_STRIP, 484, 242);
	
	glDrawArrays(GL_TRIANGLE_STRIP, 726, 242);
	
	glDrawArrays(GL_TRIANGLE_STRIP, 968, 242);
	
	glDisableClientState(GL_VERTEX_ARRAY);
//	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	
	drawStars();
	
	if(!isStarted){
		const unsigned char msg[] = "Hold a/d: controls revolution speed\n\nPress w/s: move camera up/down\n\nPress e/q: zoom in/out";
		glColor3f(1, 1, 1);
		glRasterPos3f(-1.6, 0.82, 0);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, msg);
	}
	
	glFlush();
	glPopMatrix();
}

void genVertices(GLfloat r, int deg, GLfloat startpos){
	int sides = 10;
	
	for (int i = 0; i <= sides; i++) {
	    GLfloat vdeg = i * PI / sides;
	    GLfloat vsin = sin(vdeg);
	    GLfloat vcos = cos(vdeg);
	
	    for (int j = 0; j <= sides; j++) {
	      	GLfloat hdeg = j * 2 * PI / sides;
	      	GLfloat hsin = sin(hdeg);
	      	GLfloat hcos = cos(hdeg);
	
	      	GLfloat x = vsin * hcos;
	      	GLfloat y = vcos;
	      	GLfloat z = vsin * hsin;
	      
	      	vertices[vertices_count] = r * x + startpos;
	      	vertices[vertices_count + 1] = r * y;
		    vertices[vertices_count + 2] = r * z;	
	        normals[normals_count] = x;
	        normals[normals_count + 1] = y;
	        normals[normals_count + 2] = z;
	
	      	x = sin(vdeg + (PI / sides)) * hcos;
	      	y = cos(vdeg + (PI / sides));
	      	z = sin(vdeg + (PI / sides)) * hsin;
	      
	      	vertices[vertices_count + 3] = r * x + startpos;
	      	vertices[vertices_count + 4] = r * y;
		    vertices[vertices_count + 5] = r * z;
	        normals[normals_count + 3] = x;
	        normals[normals_count + 4] = y;
	        normals[normals_count + 5] = z;
			
			normals_count += 6;
			vertices_count += 6;
		}
	}
}

void genColors(float r, float g, float b, float r_bias, float g_bias, float b_bias){
	r /= 255.0;
	g /= 255.0;
	b /= 255.0;
	int colors_counted = colors_count;
	GLfloat rand_r = r * ((rand()%1001/3000.0) + 0.7);
	GLfloat rand_g = g * ((rand()%1001/3000.0) + 0.7);
	GLfloat rand_b = b * ((rand()%1001/3000.0) + 0.7);
	
	
	for(int i = colors_count; i < colors_counted + 726; i+=9){
		rand_r = r * ((rand()%1001/3000.0) + 0.7 + r_bias);
		rand_g = g * ((rand()%1001/3000.0) + 0.7 + g_bias);
		rand_b = b * ((rand()%1001/3000.0) + 0.7 + b_bias);
		
		colors[i] = rand_r;
		colors[i+1] = rand_g;
		colors[i+2] = rand_b;
		colors[i+3] = rand_r;
		colors[i+4] = rand_g;
		colors[i+5] = rand_b;
		colors[i+6] = rand_r;
		colors[i+7] = rand_g;
		colors[i+8] = rand_b;
			
		colors_count += 9;
	}
}

void genStars(){
	for(int i = 0; i < 12000; i+=3){
		int randX = rand();
		int randY = rand();
		
		stars[i] = (randX%2 == 0)? -((randX%1001)/400.0):(randX%1001)/400.0;
		stars[i+1] = (randY%2 == 0)? -((randY%1001)/750.0):(randY%1001)/750.0;
		stars[i+2] = -1;
		
		stars[12000+i] = (randX%2 == 0)? -((randX%1001)/250.0):(randX%1001)/250.0;
		stars[12000+i+1] = 1.3;
		stars[12000+i+2] = (randY%2 == 0)? -((randY%1001)/1000.0):(randY%1001)/1000.0;
		
		
		stars[24000+i] = (randX%2 == 0)? -((randX%1001)/250.0):(randX%1001)/250.0;
		stars[24000+i+1] = -1.3;
		stars[24000+i+2] = (randY%2 == 0)? -((randY%1001)/1000.0):(randY%1001)/1000.0;
	}
}

void drawStars(){
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBegin(GL_POINTS);
	for(int i = 0; i < 36000; i+=3){
		glColor4f(1, 1, 1, (rand()%101/400.0)+0.1);
		glVertex3f(stars[i], stars[i+1], stars[i+2]);
	};
	glEnd();
}

void keyControls(unsigned char key, int x, int y){
	GLfloat tempX = camX;
	GLfloat tempY = camY;
	GLfloat tempZ = camZ;
	GLfloat angle = 2*PI/180;
	GLfloat SIN = sin(angle);
	GLfloat COS = cos(angle);
	
	switch(key){
		case 'w':
			if(camZ > 0.3 || camY <= 0){
				angle = -2*PI/180;
				SIN = sin(angle);
				COS = cos(angle);
				camY = ((tempY * COS) - (tempZ*SIN));
				camZ = ((tempY * SIN) + (tempZ*COS));
			}
		break;
		case 's':
			if(camZ > 0.3 || camY >= 0){
				camY = ((tempY * COS) - (tempZ * SIN));
				camZ = ((tempY * SIN) + (tempZ * COS));
			}
		break;
		case 'a':
			YEAR_MS = YEAR_MS > 1000? YEAR_MS * 0.9: YEAR_MS;
			DAY_MS = YEAR_MS/365.0;
			cos_merc = cos(FRAME_MS/(0.5 * 88 * DAY_MS));
			sin_merc = sin(FRAME_MS/(0.5 * 88 * DAY_MS));
			cos_venus = cos(FRAME_MS/(0.5 * 225 * DAY_MS));
			sin_venus = sin(FRAME_MS/(0.5 * 225 * DAY_MS));
			cos_earth = cos(FRAME_MS/(0.5 * 365 * DAY_MS));
			sin_earth = sin(FRAME_MS/(0.5 * 365 * DAY_MS));
			cos_moon = cos(FRAME_MS/(0.5 * 27.3 * DAY_MS));
			sin_moon = sin(FRAME_MS/(0.5 * 27.3 * DAY_MS));
		break;
		case 'd':
			YEAR_MS *= 1.1;
			DAY_MS = YEAR_MS/365.0;
			cos_merc = cos(FRAME_MS/(0.5 * 88 * DAY_MS));
			sin_merc = sin(FRAME_MS/(0.5 * 88 * DAY_MS));
			cos_venus = cos(FRAME_MS/(0.5 * 225 * DAY_MS));
			sin_venus = sin(FRAME_MS/(0.5 * 225 * DAY_MS));
			cos_earth = cos(FRAME_MS/(0.5 * 365 * DAY_MS));
			sin_earth = sin(FRAME_MS/(0.5 * 365 * DAY_MS));
			cos_moon = cos(FRAME_MS/(0.5 * 27.3 * DAY_MS));
			sin_moon = sin(FRAME_MS/(0.5 * 27.3 * DAY_MS));
		break;
		case 'e':
			camX *= 0.95;
			camY *= 0.95;
			camZ *= 0.95;
		break;
		case 'q':
			camX *= 1.05;
			camY *= 1.05;
			camZ *= 1.05;
		break;
		case 27:
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDeleteBuffers(1, &VBOid);
			exit(0);
	}
	
	isStarted = true;
	glutPostRedisplay();
}

void animate(int value){
	mappedVertices = (GLfloat*) glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
	
	tempX_earthCore = x_earthCore;
	tempZ_earthCore = z_earthCore;
	x_earthCore = ((cos_earth * tempX_earthCore) + (sin_earth * tempZ_earthCore));
	z_earthCore = (cos_earth * tempZ_earthCore) - (sin_earth * tempX_earthCore);
	
	for(int i = 726; i < 1452; i+=3){
		tempX_merc = mappedVertices[i];
		tempZ_merc = mappedVertices[i+2]; 
		tempX_venus = mappedVertices[726+i];
		tempZ_venus = mappedVertices[726+i+2];
		tempX_earth = mappedVertices[1452+i];
		tempZ_earth = mappedVertices[1452+i+2];
		tempX_moon = mappedVertices[2178+i];
		tempZ_moon = mappedVertices[2178+i+2];
		
		x_diff = tempX_moon - x_earthCore;
		z_diff = tempZ_moon - z_earthCore;
		
		mappedVertices[i] = ((cos_merc * tempX_merc) + (sin_merc * tempZ_merc));
		mappedVertices[i+2] = (cos_merc * tempZ_merc) - (sin_merc * tempX_merc);
		mappedVertices[726+i] = ((cos_venus * tempX_venus) + (sin_venus * tempZ_venus));
		mappedVertices[726+i+2] = (cos_venus * tempZ_venus) - (sin_venus * tempX_venus);
		mappedVertices[1452+i] = ((cos_earth * tempX_earth) + (sin_earth * tempZ_earth));
		mappedVertices[1452+i+2] = (cos_earth * tempZ_earth) - (sin_earth * tempX_earth);
		mappedVertices[2178+i] = ((cos_moon * x_diff) + (sin_moon * z_diff)) + x_earthCore;
		mappedVertices[2178+i+2] = ((cos_moon * z_diff) - (sin_moon * x_diff)) + z_earthCore;
	}
	
//	for(int i = 4356; i < 5082; i+=3){
//		tempX_merc = mappedVertices[i];
//		tempZ_merc = mappedVertices[i+2]; 
//		tempX_venus = mappedVertices[726+i];
//		tempZ_venus = mappedVertices[726+i+2];
//		tempX_earth = mappedVertices[1452+i];
//		tempZ_earth = mappedVertices[1452+i+2];
//		tempX_moon = mappedVertices[2178+i];
//		tempZ_moon = mappedVertices[2178+i+2];
//		
//		x_diff = tempX_moon - x_earthCore;
//		z_diff = tempZ_moon - z_earthCore;
//		
//		mappedVertices[i] = ((cos_merc * tempX_merc) + (sin_merc * tempZ_merc));
//		mappedVertices[i+2] = (cos_merc * tempZ_merc) - (sin_merc * tempX_merc);
//		mappedVertices[726+i] = ((cos_venus * tempX_venus) + (sin_venus * tempZ_venus));
//		mappedVertices[726+i+2] = (cos_venus * tempZ_venus) - (sin_venus * tempX_venus);
//		mappedVertices[1452+i] = ((cos_earth * tempX_earth) + (sin_earth * tempZ_earth));
//		mappedVertices[1452+i+2] = (cos_earth * tempZ_earth) - (sin_earth * tempX_earth);
//		mappedVertices[2178+i] = (((cos_moon * x_diff) + (sin_moon * z_diff)) * height_ratio) + x_earthCore;
//		mappedVertices[2178+i+2] = ((cos_moon * z_diff) - (sin_moon * x_diff)) + z_earthCore;
//	}
	
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glutPostRedisplay();
	glutTimerFunc(FRAME_MS, animate, value+1);
}

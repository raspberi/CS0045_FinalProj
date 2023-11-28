#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath>

#define PI 3.14159265358979323846

void draw_solid_cylinder(GLfloat radius, GLfloat height, GLubyte R, GLubyte G, GLubyte B);
void draw_Astronaut();
void display();
void reshapeFunc(int x, int y);

GLfloat light_position[] = {5.0, 5.0, 5.0, 1.0};
GLfloat light_ambient[] = {0.2, 0.2, 0.2, 1.0};
GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};

GLfloat material_ambient[] = {0.8, 0.8, 0.8, 1.0};
GLfloat material_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat material_specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat material_shininess = 100.0;

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA);
    glutCreateWindow("");
    glutInitWindowSize(1920, 1080);
    glutDisplayFunc(display);
    glutReshapeFunc(reshapeFunc);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, material_shininess);

    glutMainLoop();
    return 0;
}

void draw_solid_cylinder(GLfloat radius, GLfloat height, GLubyte R, GLubyte G, GLubyte B) {
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    gluQuadricDrawStyle(quadratic, GLU_FILL);
    gluQuadricNormals(quadratic, GLU_SMOOTH);

    glColor3ub(R, G, B);
    gluCylinder(quadratic, radius, radius, height, 32, 32);

    // Draw the circle on top of the cylinder
    glPushMatrix();
    glTranslatef(0.0, 0.0, height);
    gluDisk(quadratic, 0.0, radius, 32, 32);
    glPopMatrix();

    gluDeleteQuadric(quadratic);
}

void draw_Astronaut() {
    // Draw spheres
    GLfloat orange_diffuse[] = {1.0, 0.5, 0.0, 1.0};  // Orange color
    glMaterialfv(GL_FRONT, GL_DIFFUSE, orange_diffuse);
    glPushMatrix();
    glTranslatef(-1.5, -0.3, 0.0);
    glutSolidSphere(0.33, 150, 150);
    glPopMatrix();

    GLfloat white_diffuse[] = {1.0, 1.0, 1.0, 1.0};  // White color
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white_diffuse);
    glPushMatrix();
    glTranslatef(-1.5, 0.0, 0.0);
    glutSolidSphere(0.44, 150, 150);
    glPopMatrix();

    GLfloat black_diffuse[] = {0.0, 0.0, 0.0, 1.0};  // Black color
    glMaterialfv(GL_FRONT, GL_DIFFUSE, black_diffuse);
    glPushMatrix();
    glTranslatef(-1.4, -0.02, 0.8);
    glutSolidSphere(0.28, 150, 150);
    glPopMatrix();

    // Body
    glPushMatrix();
    glTranslatef(-1.5, -1.1, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    GLfloat white_diffuse3[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white_diffuse3);
    draw_solid_cylinder(0.33, 0.66, 255, 255, 255);
    glPopMatrix();

    // Left leg
    glPushMatrix();
    glTranslatef(-1.72, -1.35, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    GLfloat white_diffuse1[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white_diffuse1);
    draw_solid_cylinder(0.11, 0.3, 255, 255, 255);
    glPopMatrix();

    // Right leg
    glPushMatrix();
    glTranslatef(-1.29, -1.35, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    GLfloat white_diffuse2[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white_diffuse2);
    draw_solid_cylinder(0.11, 0.3, 255, 255, 255);
    glPopMatrix();

    // Right arm
    glPushMatrix();
    glTranslatef(-0.9, -0.5, 0.0);
    glRotatef(-90, 0.0, 1.0, 0.0);
    GLfloat white_diffuse4[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white_diffuse4);
    draw_solid_cylinder(0.11, 0.4, 255, 255, 255);
    glPopMatrix();

    // Left arm
    glPushMatrix();
    glTranslatef(-1.8, -0.5, 0.0);
    glRotatef(-90, 0.4, 1.0, 0.0);
    GLfloat white_diffuse5[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white_diffuse5);
    draw_solid_cylinder(0.11, 0.4, 255, 255, 255);
    glPopMatrix();
}

void display() {
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, -15.0);

    draw_Astronaut();

    glutSwapBuffers();
}

void reshapeFunc(int x, int y) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, x, y);
}

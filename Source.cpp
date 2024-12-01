#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int MAX_DEPTH = 2; 
int NUM_SPOKES = 24; // Number of radial lines 
float angle = 0.0f; // Rotation angle

void drawFractalTriangle(double x1, double y1, double x2, double y2, double x3, double y3, int depth) {
    if (depth == 0) {
        glBegin(GL_TRIANGLES);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
        glVertex2d(x3, y3);
        glEnd();
        return;
    }
    //  midpoints  triangle
    double midX1 = (x1 + x2) / 2.0;
    double midY1 = (y1 + y2) / 2.0;
    double midX2 = (x2 + x3) / 2.0;
    double midY2 = (y2 + y3) / 2.0;
    double midX3 = (x3 + x1) / 2.0;
    double midY3 = (y3 + y1) / 2.0;

    // Recursively draw smaller triangles
    drawFractalTriangle(x1, y1, midX1, midY1, midX3, midY3, depth - 1);
    drawFractalTriangle(midX1, midY1, x2, y2, midX2, midY2, depth - 1);
    drawFractalTriangle(midX3, midY3, midX2, midY2, x3, y3, depth - 1);
}

void drawRadialFractal() {
    double radius = 0.15; 
    for (int i = 0; i < NUM_SPOKES; i++) {
        double angle1 = 2 * 3.14 * i / NUM_SPOKES;
        double angle2 = 2 * 3.14 * (i + 1) / NUM_SPOKES;
        double x1 = 0.0, y1 = 0.0; // Center of the pattern
        double x2 = radius * cos(angle1);
        double y2 = radius * sin(angle1);
        double x3 = radius * cos(angle2);
        double y3 = radius * sin(angle2);

        // fractal triangle between the spokes
        drawFractalTriangle(x1, y1, x2, y2, x3, y3, MAX_DEPTH);
    }
}

// dotted circle / orbits
void drawDottedCircle(float radius) {
    int numDots = 100; 
    float angleStep = 2.0f * 3.14 / numDots;

    glColor3f(1.0f, 1.0f, 1.0f); 

    glBegin(GL_POINTS); 
    for (int i = 0; i < numDots; i++) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        glVertex2f(x, y); 
    }
    glEnd();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT); 

    float maxRadius = 0.8f; 
    for (float radius = maxRadius; radius > 0.1f; radius -= 0.1f) {
        drawDottedCircle(radius);
    }

    //sun
   glPushMatrix(); 

    glColor3f(1.0f, 0.647f, 0.0f); 
    drawRadialFractal();
    glPopMatrix();
    glPushMatrix(); 

    glTranslatef(-0.6f, 0.0f, 0.0f); 
    glColor3f(0.0f, 1.0f, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f); 
    drawRadialFractal();
    glPopMatrix(); 

    // 2nd fractal
    glPushMatrix(); 
    glTranslatef(0.6f, -0.3f, 0.0f); 
    glColor3f(1.0f, 0.0f, 0.0f);
    glScalef(1.5f, 1.5f, 1.0f); 
    glRotatef(-angle, 0.0f, 0.0f, 1.0f); 
    drawRadialFractal();
    glPopMatrix(); 

    // 3rd fractal
    glPushMatrix();
    glTranslatef(0.0f, 0.8f, 0.0f); 
    glColor3f(0.6f, 0.3f, 0.0f); //brown
    glScalef(0.8f, 0.8f, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    drawRadialFractal();
    glPopMatrix(); 
    glPushMatrix(); 

    // 4th fractal
    glTranslatef(0.0f, -0.8f, 0.0f); 
    glColor3f(0.0f, 0.0f, 1.0f); //blue
    glScalef(0.6f, 0.6f, 1.0f); 
    glRotatef(-angle, 0.0f, 0.0f, 1.0f); 
    drawRadialFractal();
    glPopMatrix(); 

    // Add the 5th fractal
    glPushMatrix();
    glTranslatef(0.6f, 0.6f, 0.0f);  
    glColor3f(0.0f, 1.0f, 1.0f); 
    glScalef(0.4f, 0.4f, 1.0f);  
    glRotatef(angle, 0.0f, 0.0f, 1.0f);  
    drawRadialFractal();
    glPopMatrix();

    // Add the 6th fractal
    glPushMatrix();
    glTranslatef(-0.6f, 0.6f, 0.0f);  
    glColor3f(0.5f, 0.0f, 0.5f); 
    glScalef(1.2f, 1.2f, 1.0f);  
    glRotatef(-angle, 0.0f, 0.0f, 1.0f); 
    drawRadialFractal();
    glPopMatrix();

    // Add the 7th fractal
    glPushMatrix();
    glTranslatef(-0.6f, -0.6f, 0.0f);  
    glColor3f(0.13f, 0.55f, 0.13f);  
    glScalef(0.6f, 0.6f, 1.0f);  
    glRotatef(angle / 2, 0.0f, 0.0f, 1.0f); 
    drawRadialFractal();
    glPopMatrix();


    glutSwapBuffers();
}

// Reshape callback 
void reshape(int w, int h) {
    glViewport(0, 0, w, h);  
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  

    float aspectRatio = (float)w / (float)h;

    if (aspectRatio >= 1.0f) {
        gluOrtho2D(-aspectRatio, aspectRatio, -1.0, 1.0);  
    }
    else {  
        gluOrtho2D(-1.0, 1.0, -1.0 / aspectRatio, 1.0 / aspectRatio);  
    }
}

// fractals animation
void idle() {
    angle += 0.05f;  
    if (angle > 360.0f) {
        angle -= 360.0f;  
    }
    glutPostRedisplay();  // Redraw 
}

int main(int argc, char** argv) {
    srand(time(0));
    NUM_SPOKES = rand() % 20 + 10;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Fractal Patterns");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
    glEnable(GL_POINT_SMOOTH); 
    glPointSize(2.0f);
    glutMainLoop();

    return 0;
}

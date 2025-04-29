#include <GL/glut.h>
#include <cmath>

const float PI = 3.14159265;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    float centerX = 0.0f, centerY = 0.0f;
    float radius = 0.5f;
    int numSegments = 100;

    glColor3f(0.4f, 0.9f, 1.0f);  

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY);  

    for (int i = 0; i <= numSegments; i++) {
        float angle = 2 * PI * i / numSegments;
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);  
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Circle");
    glutInitWindowSize(600, 600);
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
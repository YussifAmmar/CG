#include <Windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <iostream>

GLuint texture;
float angleX = 0.0f, angleY = 0.0f; 
float camX = 0.0f, camY = 0.0f, camZ = 10.0f; 
bool rotate = true;


GLuint loadBMP(const char* filename) {
    FILE* file = NULL;
    fopen_s(&file, filename, "rb");
    if (!file) {
        printf("Error: Unable to open file %s\n", filename);
        return 0; 
    }

    
    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, file); 

 
    int width = *(int*)&header[18];
    int height = *(int*)&header[22];
    int imageSize = 3 * width * height; 

    unsigned char* data = new unsigned char[imageSize];  
    fread(data, sizeof(unsigned char), imageSize, file);
    fclose(file);

   
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);  //sends data to openGL

    delete[] data;  

    return textureID;
}


void init() {
    glEnable(GL_DEPTH_TEST);  
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
    texture = loadBMP("myimage.bmp");  
}

void drawCube() {
    glBindTexture(GL_TEXTURE_2D, texture);  

    glBegin(GL_QUADS);

    // Front face
    glTexCoord2f(0.0f, 0.0f);   // Take pixel from bottom-left of the texture. 
    glVertex3f(-1.0f, -1.0f, 1.0f);   // Draw at bottom-left-front point of cube.
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);

    // Back face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);

    // Top face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);

    // Bottom face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f);

    // Right face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);

    // Left face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();  //start fresh

    // Move the camera
    glTranslatef(camX, camY, -camZ);

    if (rotate) {
        glRotatef(angleX, 1.0f, 0.0f, 0.0f);  // Rotate around X-axis
        glRotatef(angleY, 0.0f, 1.0f, 0.0f);  // Rotate around Y-axis
    }

    drawCube();  

 glutSwapBuffers();  // Swap back and front buffers
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);   //draws within the entire window, even when it changes size.
    glMatrixMode(GL_PROJECTION);  //projection matrix controls how the 3D scene is mapped onto the 2D screen.
    glLoadIdentity();  //Resets the projection matrix
    gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 1.0f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
}
void update(int value) {
    angleX += 2.0f;  // Increment rotation angles
    angleY += 2.0f;
    if (angleX > 360.0f) angleX -= 360.0f;  // Keep angleX within[0, 360] degrees.
    if (angleY > 360.0f) angleY -= 360.0f;

 glutPostRedisplay();  // redraw the screen
    glutTimerFunc(16, update, 0);  // updating every 16 milliseconds
}

void handleKeypress(unsigned char key, int x, int y) {
    const float speed = 0.1f;

    if (key == 'w') {
        camZ -= speed;  // Move camera forward
    }
    if (key == 's') {
        camZ += speed;  // Move camera backward
    }
    if (key == 'a') {
        camX -= speed;  // Move camera left
    }
    if (key == 'd') {
        camX += speed;  // Move camera right
    }
    if (key == 'q') {
        camY += speed;  // Move camera up
    }
    if (key == 'e') {
        camY -= speed;  // Move camera down
    }
}
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        rotate = !rotate;  
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);  //initialize glut
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  //double buffering, RGB, depth buffering
    glutInitWindowSize(800, 600);
    glutCreateWindow("Interactive Rotating Cube");

    glEnable(GL_TEXTURE_2D);   //so texture (2d) can be mapped on 3d objects
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(handleKeypress);
    glutTimerFunc(25, update, 0);  //update rotation every 25ms
    glutMouseFunc(mouse);

    glutMainLoop(); //so program keeps running
    return 0;
}
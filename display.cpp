#include "display.h"

int width;
int height;

void init(int argc, char *argv[]){
    width = WinWidth;
    height = WinHeight;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Catmull-Clark Subdivision surface (by Chizhang)");
    initLights();
}

void initLights(){

}

void displayCallback(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
}

void reshape(int _width, int _height){
    width = _width;
    height = _height;
    GLfloat scale = GLfloat(width) / GLfloat(height);

    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glLoadIdentity();
    gluPerspective(60.0, (GLdouble)width / (GLdouble)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2, 2, 2, 0, 0, 0, 0, 1, 0);
}

void display(int argc, char *argv[]){
    init(argc, argv);
    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshape);
    
    glutMainLoop();
}
#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

#include "basic.h"
#include "ObjLoader.h"
#include "processor.h"


void display(int argc, char *argv[]);
void reshape(int _width, int _height);
void init(int argc, char *argv[]);
void initLights();
void displayCallback();
void keyboardCallback(unsigned char key, int x, int y);
void specialKeyCallback(int key, int x, int y);


#endif // !DISPLAY_H


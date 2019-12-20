#pragma once
#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H
#include "basic.h"
#include "DataStructure.h"

class Object {
public:
	Object(){}
	void initObject(const string &objName);
	int getWinWidth() { return winWidth; }
	int getWinHeight() { return winHeight; }
	void test();

private:
	int winWidth, winHeight;
	int level;
	bool loadObj(const string &objName);
	deque<Face *> fqueue;
	deque<Edge *> equeue;
	deque<Vertex *> vqueue;
};


#endif // !OBJ_LOADER_H
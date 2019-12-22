#pragma once
#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H
#include "basic.h"
#include "DataStructure.h"

class Object {
public:
	int fileType;
	Object(){}
	void initObject(const string &_objName,
		deque<Vertex *> &_vqueue,
		deque<Edge *> &_equeue,
		deque<Face *> &_fqueue);
	deque<Face *> getFqueue() { return fqueue; }
	deque<Edge *> getEqueue() { return equeue; }
	deque<Vertex *> getVqueue() { return vqueue; }
	void test();

private:
	string objName;
	bool loadObj(const string &objName);
	deque<Face *> fqueue;
	deque<Edge *> equeue;
	deque<Vertex *> vqueue;
};


#endif // !OBJ_LOADER_H
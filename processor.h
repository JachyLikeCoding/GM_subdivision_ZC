#pragma once
#include "ObjLoader.h"

Edge* getEdge(Edge &edge, deque<Edge *> &equeue);
Vertex* getVertex(Vertex &v, deque<Vertex *> &vqueue);

class SubdivisionProcessor {
public:
	Object obj;
	void initProcessor(Object &_obj);
	void subdivision(int level, deque<Vertex *> &vqueue, deque<Edge *> &equeue, deque<Face *> &fqueue);
	void subdivision3(int level, deque<Vertex *> &vqueue, deque<Edge *> &equeue, deque<Face *> &fqueue);
	void subdivision4(int level, deque<Vertex *> &vqueue, deque<Edge *> &equeue, deque<Face *> &fqueue);
};
#pragma once
#include "basic.h"
#include "DataStructure.h"
#include "ObjLoader.h"

Edge* getEdge(Edge &edge, deque<Edge *> &equeue);
Vertex* getVertex(Vertex &v, deque<Vertex *> &vqueue);

class SubdivisionProcessor {
public:
	Object obj;
	void initProcessor();
	//Edge* getEdge(Edge &edge, deque<Edge *> &equeue);
	//Vertex* getVertex(Vertex &v, deque<Vertex *> &vqueue);
	void subdivision(deque<Vertex *> vqueue, deque<Edge *> equeue, deque<Face *> fqueue);
};
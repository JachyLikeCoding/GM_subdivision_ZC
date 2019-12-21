#include "processor.h"

Edge* getEdge(Edge &edge, deque<Edge *> &equeue) {
	for (int i = 0; i < equeue.size(); i++) {
		if (edge == (*equeue[i])) {
			return equeue[i];
		}
	}
	return nullptr;
}

Vertex* getVertex(Vertex &v, deque<Vertex *> &vqueue) {
	for (int i = 0; i < vqueue.size(); i++) {
		if (v == (*vqueue[i])) {
			return vqueue[i];
		}
	}
	return nullptr;
}

void SubdivisionProcessor::initProcessor(Object & _obj)
{
	obj = _obj;
}

void SubdivisionProcessor::subdivision(int level, deque<Vertex *> &vqueue, deque<Edge *> &equeue, deque<Face *> &fqueue) {
	Face *currentface = fqueue.front();
	currentface->printfCenterV();
	int currentlevel = currentface->level;
	int nextlevel;
	while (currentface->level < level) {
		nextlevel = currentface->level + 1;
		if (currentface->level == 1) {
			cout << "debug here\n";
		}
		//face point * 1
		Vertex *facePoint = new Vertex(currentface->fCenterv, currentface->level + 1);
		//edge point * 4
		Vertex *edgePoint0 = new Vertex(currentface->fEdges[0]->calEdgePoint(), currentface->level + 1);
		Vertex *edgePoint1 = new Vertex(currentface->fEdges[1]->calEdgePoint(), currentface->level + 1);
		Vertex *edgePoint2 = new Vertex(currentface->fEdges[2]->calEdgePoint(), currentface->level + 1);
		Vertex *edgePoint3 = new Vertex(currentface->fEdges[3]->calEdgePoint(), currentface->level + 1);
		//vertex point * 4
		Vertex *vertexPointA = new Vertex(currentface->fVertices[0]->calVertexPoint(), currentface->level + 1);
		Vertex *vertexPointB = new Vertex(currentface->fVertices[1]->calVertexPoint(), currentface->level + 1);
		Vertex *vertexPointC = new Vertex(currentface->fVertices[2]->calVertexPoint(), currentface->level + 1);
		Vertex *vertexPointD = new Vertex(currentface->fVertices[3]->calVertexPoint(), currentface->level + 1);
		//add 4 new face
		fqueue.push_back(new Face(vertexPointA, edgePoint0, facePoint, edgePoint3, equeue, vqueue, currentface->level + 1));
		fqueue.push_back(new Face(vertexPointB, edgePoint1, facePoint, edgePoint0, equeue, vqueue, currentface->level + 1));
		fqueue.push_back(new Face(vertexPointC, edgePoint2, facePoint, edgePoint1, equeue, vqueue, currentface->level + 1));
		fqueue.push_back(new Face(vertexPointD, edgePoint3, facePoint, edgePoint2, equeue, vqueue, currentface->level + 1));

		fqueue.pop_front();
		currentface = fqueue.front();

		if (currentface->level > currentlevel)
		{
			while (vqueue.front()->level == currentlevel) {
				vqueue.pop_front();
			}

			while (equeue.front()->level == currentlevel) {
				equeue.pop_front();
			}
			currentlevel = currentface->level;
		}
	}
}
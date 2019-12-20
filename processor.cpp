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

void SubdivisionProcessor::subdivision(deque<Vertex *> vqueue, deque<Edge *> equeue, deque<Face *> fqueue) {
	Face *currentface = fqueue.front();
	//face point * 1
	Vertex *facePoint = new Vertex(currentface->fCenterv);
	//edge point * 4
	Vertex *edgePoint0 = new Vertex(currentface->fEdges[0]->calEdgePoint());
	Vertex *edgePoint1 = new Vertex(currentface->fEdges[1]->calEdgePoint());
	Vertex *edgePoint2 = new Vertex(currentface->fEdges[2]->calEdgePoint());
	Vertex *edgePoint3 = new Vertex(currentface->fEdges[3]->calEdgePoint());
	//vertex point * 4
	Vertex *vertexPointA = new Vertex(currentface->fVertices[0]->calVertexPoint());
	Vertex *vertexPointB = new Vertex(currentface->fVertices[1]->calVertexPoint());
	Vertex *vertexPointC = new Vertex(currentface->fVertices[2]->calVertexPoint());
	Vertex *vertexPointD = new Vertex(currentface->fVertices[3]->calVertexPoint());
	//add 4 new face
	fqueue.push_back(new Face(facePoint, edgePoint0, vertexPointA, edgePoint1, equeue, vqueue));
	fqueue.push_back(new Face(facePoint, edgePoint1, vertexPointB, edgePoint2, equeue, vqueue));
	fqueue.push_back(new Face(facePoint, edgePoint2, vertexPointC, edgePoint3, equeue, vqueue));
	fqueue.push_back(new Face(facePoint, edgePoint3, vertexPointD, edgePoint0, equeue, vqueue));

	fqueue.pop_front();
	currentface = fqueue.front();
}
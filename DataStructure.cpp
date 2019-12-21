#include "DataStructure.h"
#include "processor.h"
#define epsilon 1e-8

/*
vertex:
*/
bool Vertex::operator==(const Vertex &v){
    if(abs(v.coord.x - coord.x) < epsilon
        && abs(v.coord.y - coord.y) < epsilon
        && abs(v.coord.z - coord.z) < epsilon){
        return true;
    }
    return false;
}


Vec3f Vertex::calVertexPoint(){
    int n = vEdges.size();
	int m = vFaces.size();
	cout << "vEdges size: " << n << endl;
	cout << "vFaces size: " << m << endl;
	if (m != n) {
		cerr << "Wrong! Edge count is " << n << ", Face count is " << m << endl;
	}

    //Q:face point
    Vec3f facePoint;
    for(int i = 0; i < n; i++){
        facePoint += vFaces[i]->fCenterv;
    }
    facePoint /= GLfloat(n);

    //2R:edge points
    Vec3f edgePoint;
    for(int i = 0; i < n; i++){
        edgePoint += vEdges[i]->midv;
    }
    edgePoint /= GLfloat(n);

    //(N-3)P:origin points
    Vec3f P = coord;

    //new vertex:
    Vec3f newVertexPoint = (facePoint + 2 * edgePoint + float(n - 3) * P) / GLfloat(n);
	return newVertexPoint;
}


/*
Edge:
*/
Vec3f Edge::calEdgePoint()
{
	Vec3f edgePoint;
	for (int i = 0; i < eFaces.size(); i++) {
		edgePoint += eFaces[i]->fCenterv;
	}
	edgePoint += midv;
	return edgePoint;
}


bool Edge::operator==(const Edge &e)
{
    if((*eVertex[0]) == (*e.eVertex[0]) && (*eVertex[1]) == (*e.eVertex[1])){
        return true;
    }
	else if ((*eVertex[0]) == (*e.eVertex[1]) && (*eVertex[1]) == (*e.eVertex[0])) {
		return true;
	}
	else {
		return false;
	}
}


/*
Face:
*/
void Face::addEdge(Vertex &v1, Vertex &v2, deque<Edge *> &equeue) 
{
	Edge *newedge = nullptr;
	Edge *tmpe = getEdge(Edge(v1, v2, -1), equeue);
	if (tmpe != nullptr) {
		newedge = tmpe;
	}
	else {
		newedge = new Edge(v1, v2, level);
		equeue.push_back(newedge);
	}
	fEdges.push_back(newedge);
	newedge->eFaces.push_back(this);
}


void Face::addVertex(Vertex *&v, deque<Vertex*>& vqueue)
{
	/*Vertex *tmpv = nullptr;
	for (int i = 0; i < vqueue.size(); i++) {
		if (v == (vqueue[i])) {
			tmpv = vqueue[i];
		}
	}*/
	Vertex *tmpv = getVertex(*v, vqueue);
	//v is not in the vqueue
	if (tmpv == nullptr) {
		vqueue.push_back(v);
	}
	else {//v is in the vqueue
		v = tmpv;
	}
	fVertices.push_back(v);
	v->vFaces.push_back(this);
}


void Face::faceDisplay()
{
	glNormal3f(normal.x, normal.y, normal.z);
	for (int i = 0; i < fVertices.size(); i++) {
		Vec3f p = fVertices[i]->getCoord();
		glVertex3f(p[0], p[1], p[2]);
		cout << p[0] << ", " << p[1] << ", " << p[2] << endl;
	}
}


void Face::setNormal()
{
	Vec3f e1 = fVertices[0]->coord - fVertices[1]->coord;
	Vec3f e2 = fVertices[2]->coord - fVertices[1]->coord;
	normal = e1.crossProduct(e2);
	normal.normalize();
}
#pragma once
#include "basic.h"
#include "geometry.h"
class Face;
class Edge;
class Halfedge;

class Vertex{
public:
    int vertex_id;
    Vec3f coord;
    bool isNewVertex;
    vector<Edge *> vEdges;
    vector<Face *> vFaces;
    Vertex(Vec3f _coord){
        coord = _coord;
    }
    Vertex(GLfloat x, GLfloat y, GLfloat z){
        coord.x = x;
        coord.y = y;
        coord.z = z;
    }
    Vec3f getCoord(){return coord;}
    Vec3f calVertexPoint();
    bool operator==(const Vertex &v);
};



class Edge{
public:
    int edge_id;
    vector<Vertex *> eVertex;
    vector<Face *> eFaces;
    bool isNewEdge;	//if the edge is new or origin
    Vec3f midv;	//the midpoint of edge

    Edge(Vertex &sv, Vertex &ev){
        eVertex.push_back(&sv);
        eVertex.push_back(&ev);
        sv.vEdges.push_back(this);
        ev.vEdges.push_back(this);
        midv = (sv.coord + ev.coord) / 2;
    }

    Vec3f calEdgePoint();
	bool operator==(const Edge &e);
};



class Face{
public:
    int face_id;
    vector<Vertex *> fVertices;
    vector<Edge *> fEdges;
    Vec3f normal;
    Vec3f fCenterv;//the center point of the edge
    int type;// choose triangle mesh or quad mesh

    void addEdge(Vertex &v1, Vertex &v2, deque<Edge *> &equeue);
    void addVertex(Vertex &v, deque<Vertex *> &vqueue);

    //triangle face
    Face(Vertex *&v1, Vertex *&v2, Vertex *&v3, deque<Edge *> &equeue, deque<Vertex *> &vqueue){
        fCenterv = ((*v1).coord + (*v2).coord + (*v3).coord) / 3;
        addVertex(*v1, vqueue);
        addVertex(*v2, vqueue);
        addVertex(*v3, vqueue);
        addEdge(*v1, *v2, equeue);
        addEdge(*v2, *v3, equeue);
        addEdge(*v3, *v1, equeue);
		setNormal();
    }
    //quad face
    Face(Vertex *&v1, Vertex *&v2, Vertex *&v3, Vertex *&v4, deque<Edge *> &equeue, deque<Vertex *> &vqueue){
        fCenterv = ((*v1).coord + (*v2).coord + (*v3).coord + (*v4).coord) / 4;
        addVertex(*v1, vqueue);
        addVertex(*v2, vqueue);
        addVertex(*v3, vqueue);
        addVertex(*v4, vqueue);
        addEdge(*v1, *v2, equeue);
        addEdge(*v2, *v3, equeue);
        addEdge(*v3, *v4, equeue);
        addEdge(*v4, *v1, equeue);
		setNormal();
    }

	void faceDisplay();

private:
	void setNormal();
};



class HalfEdge{

};

#include "DataStructure.h"
#include "basic.h"
#define epsilon 1e-8

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

    //(N-3)S:P
    Vec3f P = coord;

    //new vertex:
    Vec3f vertexPoint = (facePoint + 2 * edgePoint + (n - 3) * P) / GLfloat(n);

}



bool Edge::operator==(const Edge &e){
    if((*eVertex[0]) == (*e.eVertex[0])
    && (*eVertex[1]) == (*e.eVertex[1]))
    {
        return true;
    }
    else if((*eVertex[0]) == (*e.eVertex[1])
    && (*eVertex[1]) == (*e.eVertex[0]))
    {
        return true;
    )
    else
        return false;
}





void Face::addEdge(Vertex &v1, Vertex &v2, deque<Edge *> &equeue){
    
}
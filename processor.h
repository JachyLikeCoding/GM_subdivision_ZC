#include "basic.h"
#include "DataStructure.h"

Edge* getEdge(Edge &edge, deque<Edge *> &equeue){
    for(int i = 0; i < equeue.size(); i++){
        if(edge == (*equeue[i])){
            return equeue[i];
        }
    }
    return nullptr;
}

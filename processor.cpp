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
	if (fqueue[0]->fVertices.size() == 3) {
		subdivision3(level, vqueue, equeue, fqueue);
	}
	if (fqueue[0]->fVertices.size() == 4) {
		subdivision4(level, vqueue, equeue, fqueue);
	}
}

void SubdivisionProcessor::subdivision4(int level, deque<Vertex *> &vqueue, deque<Edge *> &equeue, deque<Face *> &fqueue) {
	Face *currentface = fqueue.front();
	//just for debug:
	/*cout << "currentface->fVertices:\n";
	for (int i = 0; i < currentface->fVertices.size(); i++) {
		cout << currentface->fVertices[i]->coord[0] << ", " << currentface->fVertices[i]->coord[1]
			<< ", " << currentface->fVertices[i]->coord[2] << endl;
	}*/
	//currentface->printfCenterV();
	int currentlevel = currentface->level;
	int nextlevel;
	while (currentface->level < level) {
		nextlevel = currentface->level + 1;
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
		//just for debug:
		//cout << "facePoint : " << facePoint->coord[0] << ", " << facePoint->coord[1] << ", " << facePoint->coord[2] << endl;
		//cout << "edgePoint0 : " << edgePoint0->coord[0] << ", " << edgePoint0->coord[1] << ", " << edgePoint0->coord[2] << endl;
		//cout << "edgePoint1 : " << edgePoint1->coord[0] << ", " << edgePoint1->coord[1] << ", " << edgePoint1->coord[2] << endl;
		//cout << "edgePoint2 : " << edgePoint2->coord[0] << ", " << edgePoint2->coord[1] << ", " << edgePoint2->coord[2] << endl;
		//cout << "edgePoint3 : " << edgePoint3->coord[0] << ", " << edgePoint3->coord[1] << ", " << edgePoint3->coord[2] << endl;
		/*cout << "vertexPointA : " << vertexPointA->coord[0] << ", " << vertexPointA->coord[1] << ", " << vertexPointA->coord[2] << endl;
		cout << "vertexPointB : " << vertexPointB->coord[0] << ", " << vertexPointB->coord[1] << ", " << vertexPointB->coord[2] << endl;
		cout << "vertexPointC : " << vertexPointC->coord[0] << ", " << vertexPointC->coord[1] << ", " << vertexPointC->coord[2] << endl;
		cout << "vertexPointD : " << vertexPointD->coord[0] << ", " << vertexPointD->coord[1] << ", " << vertexPointD->coord[2] << endl;*/

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
	cout << "--------------------subdivision finished!!-------------------" << endl;
}


void SubdivisionProcessor::subdivision3(int level, deque<Vertex *> &vqueue, deque<Edge *> &equeue, deque<Face *> &fqueue) {
	Face *currentface = fqueue.front();
	int currentlevel = currentface->level;
	int nextlevel;
	while (currentface->level < level) {
		//step 1: 先从三角形细分成四边形
		if (currentface->level == 0) {
			nextlevel = currentface->level + 1;
			//face point * 1
			Vertex *facePoint = new Vertex(currentface->fCenterv, currentface->level + 1);

			//edge point * 3
			Vertex *edgePoint0 = new Vertex(currentface->fEdges[0]->calEdgePoint(), currentface->level + 1);
			Vertex *edgePoint1 = new Vertex(currentface->fEdges[1]->calEdgePoint(), currentface->level + 1);
			Vertex *edgePoint2 = new Vertex(currentface->fEdges[2]->calEdgePoint(), currentface->level + 1);

			//vertex point * 4
			Vertex *vertexPointA = new Vertex(currentface->fVertices[0]->calVertexPoint(), currentface->level + 1);
			Vertex *vertexPointB = new Vertex(currentface->fVertices[1]->calVertexPoint(), currentface->level + 1);
			Vertex *vertexPointC = new Vertex(currentface->fVertices[2]->calVertexPoint(), currentface->level + 1);

			//just for debug:
			//cout << "facePoint : " << facePoint->coord[0] << ", " << facePoint->coord[1] << ", " << facePoint->coord[2] << endl;
			//cout << "edgePoint0 : " << edgePoint0->coord[0] << ", " << edgePoint0->coord[1] << ", " << edgePoint0->coord[2] << endl;
			//cout << "edgePoint1 : " << edgePoint1->coord[0] << ", " << edgePoint1->coord[1] << ", " << edgePoint1->coord[2] << endl;
			//cout << "edgePoint2 : " << edgePoint2->coord[0] << ", " << edgePoint2->coord[1] << ", " << edgePoint2->coord[2] << endl;
			//cout << "edgePoint3 : " << edgePoint3->coord[0] << ", " << edgePoint3->coord[1] << ", " << edgePoint3->coord[2] << endl;
			/*cout << "vertexPointA : " << vertexPointA->coord[0] << ", " << vertexPointA->coord[1] << ", " << vertexPointA->coord[2] << endl;
			cout << "vertexPointB : " << vertexPointB->coord[0] << ", " << vertexPointB->coord[1] << ", " << vertexPointB->coord[2] << endl;
			cout << "vertexPointC : " << vertexPointC->coord[0] << ", " << vertexPointC->coord[1] << ", " << vertexPointC->coord[2] << endl;
			cout << "vertexPointD : " << vertexPointD->coord[0] << ", " << vertexPointD->coord[1] << ", " << vertexPointD->coord[2] << endl;*/

			//add 3 new face
			fqueue.push_back(new Face(vertexPointA, edgePoint0, facePoint, edgePoint2, equeue, vqueue, currentface->level + 1));
			fqueue.push_back(new Face(vertexPointB, edgePoint1, facePoint, edgePoint0, equeue, vqueue, currentface->level + 1));
			fqueue.push_back(new Face(vertexPointC, edgePoint2, facePoint, edgePoint1, equeue, vqueue, currentface->level + 1));

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
		//step 2: 后面的细分都是四边形细分了
		else {
			int currentlevel = currentface->level;
			int nextlevel;
			while (currentface->level < level) {
				nextlevel = currentface->level + 1;
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
	}
	cout << "--------------------subdivision finished!!-------------------" << endl;
}
#include "ObjLoader.h"

void Object::initObject(const string &objName) {
	bool flag = loadObj(objName);
	if (!flag) 
	{
		cerr << "ERROR: File loaded fail. Please check your file '" << objName << " '.\n";
	}
}


bool Object::loadObj(const string &objName) {
	fstream input;
	input.open(objName);

	if (!input.is_open()) {
		cerr << "Fail to open the input file ' " << objName << " '" << endl;
		return false;
	}
	
	string head;
	GLfloat x, y, z;

	while (input >> head) {
		if (input.eof())
			break;
		else {
			if (head == "v") {
				input >> x >> y >> z;
				vqueue.push_back(new Vertex(x,y,z));
			}
			else if (head == "f") {
				string::iterator iter;
				int vid[4];
				vector<string> tmps(4);
				input >> tmps[0] >> tmps[1] >> tmps[2] >> tmps[3];
				for (int i = 0; i < 4; i++) {
					iter = find(tmps[i].begin(), tmps[i].end(), '/');
					vid[i] = stoi(tmps[i].substr(0, iter - tmps[i].begin()));//注意obj文件里顶点序号从1或-1开始
					vid[i] > 0 ? (vid[i]--) : (vid[i] += vqueue.size());//这里把它统一成0,1,2,3序号
				}
				//TODO: find four points vid[0], vid[1], vid[2], vid[3]
				Face *f = new Face(vqueue[vid[0]], vqueue[vid[0]], vqueue[vid[0]], vqueue[vid[0]], equeue, vqueue);
				fqueue.push_back(f);
			}
			else
			{
				continue;
			}
		}
	}
	//just for debug:
	cout << vqueue.size() << endl;
	cout << fqueue.size() << endl;
	return true;
}



//just for debug
void Object::test() {
	//test vertices of face
	cout << "face count: " << fqueue.size() << endl;
	cout << "vertices count:" << vqueue.size() << endl;
	/*for (int i = 0; i < faces.size(); i++) {
		CalFaceEdges(i);
		cout << "[" << i << "]";
		for (int j = 0; j < faces[i].size(); j++) {
			cout << faces[i][j] << "\t";
		} 
		cout << endl;
	}*/
	//test edges of face:
	/*cout << edges.size() << endl;
	for (int i = 0; i < edges.size(); i++) {
		cout << "edge_polygon_id: " << edges[i].edge_polygon_id;
		cout << "\tedge_dy: " << edges[i].dy << endl;
	}*/
}

#include "ObjLoader.h"

void Object::initObject(const string &_objName, 
										deque<Vertex *> &_vqueue,
										deque<Edge *> &_equeue,
										deque<Face *> &_fqueue) {
	objName = _objName;
	fqueue = _fqueue;
	vqueue = _vqueue;
	equeue = _equeue;
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
	deque<Vertex *> tmpvqueue;
	while (input >> head) {
		if (input.eof())
			break;
		else {
			if (head == "v") {
				input >> x >> y >> z;
				tmpvqueue.push_back(new Vertex(x,y,z));
			}
			else if (head == "f") {
				string::iterator iter;
				int vid[4];
				vector<string> tmps(4);
				input >> tmps[0] >> tmps[1] >> tmps[2] >> tmps[3];
				for (int i = 0; i < 4; i++) {
					iter = find(tmps[i].begin(), tmps[i].end(), '/');
					vid[i] = stoi(tmps[i].substr(0, iter - tmps[i].begin()));//注意obj文件里顶点序号从1或-1开始
					vid[i] > 0 ? (vid[i]--) : (vid[i] += tmpvqueue.size());//这里把它统一成0,1,2,3序号
				}
				
				Face *f = new Face(tmpvqueue[vid[0]], tmpvqueue[vid[1]], tmpvqueue[vid[2]], tmpvqueue[vid[3]], equeue, vqueue);
				fqueue.push_back(f);
			}
			else
			{
				continue;
			}
		}
	}

	cout << "tmpvqueue count:" << tmpvqueue.size() << endl;
	return true;
}



//just for debug
void Object::test() {
	cout << "face count: " << fqueue.size() << endl;
	cout << "vertices count:" << vqueue.size() << endl;
	cout << "edges count:" << equeue.size() << endl;
	cout << endl;
}

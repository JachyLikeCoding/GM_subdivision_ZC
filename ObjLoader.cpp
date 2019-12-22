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
	ifstream file(objName);
	if (!file.is_open()) {
		cerr << "Fail to open the input file ' " << objName << " '" << endl;
		return false;
	}
	vqueue.clear();
	equeue.clear();
	fqueue.clear();
	string line;
	GLfloat x, y, z;
	deque<Vertex *> tmpvqueue;
	while(getline(file, line)){
		stringstream ss(line);
		string head;
		ss >> head;
		
		if (head == "v") {
			ss >> x >> y >> z;
			tmpvqueue.push_back(new Vertex(x,y,z));
		}
		else if (head == "f") {
			string::iterator iter;
			int vid[4];
			vector<string> tmps(4);
			ss >> tmps[0] >> tmps[1] >> tmps[2];

			if (ss >> tmps[3]) {//四边形面片
				fileType = 4;
			}
			else {//三角形面片
				fileType = 3;
			}

			for (int i = 0; i < fileType; i++) {
				iter = find(tmps[i].begin(), tmps[i].end(), '/');
				vid[i] = stoi(tmps[i].substr(0, iter - tmps[i].begin()));//注意obj文件里顶点序号从1或-1开始
				vid[i] > 0 ? (vid[i]--) : (vid[i] += tmpvqueue.size());//这里把它统一成0,1,2,3序号
			}

			if (fileType == 4) {
				Face *f = new Face(tmpvqueue[vid[0]], tmpvqueue[vid[1]], tmpvqueue[vid[2]], tmpvqueue[vid[3]], equeue, vqueue);
				fqueue.push_back(f);
			}
			else {
				Face *f = new Face(tmpvqueue[vid[0]], tmpvqueue[vid[1]], tmpvqueue[vid[2]], equeue, vqueue);
				fqueue.push_back(f);
			}
		}
		else
		{
			continue;
		}
	}
	file.close();
	cout << "tmpvqueue count:" << tmpvqueue.size() << endl;
	return true;
}


//just for debug
void Object::test() {
	cout << "obj file type: " << fileType << endl;
	cout << "face count: " << fqueue.size() << endl;
	cout << "vertices count:" << vqueue.size() << endl;
	cout << "edges count:" << equeue.size() << endl;
	cout << endl;
}

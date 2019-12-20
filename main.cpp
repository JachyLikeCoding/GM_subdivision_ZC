#include "basic.h"
#include "DataStructure.h"
#include "display.h"
#include "ObjLoader.h"
#include "processor.h"

deque<Face *> fqueue;
deque<Edge *> equeue;
deque<Vertex *> vqueue;

int main(int argc, char *argv[]){
	Object obj;
	string objPath = "Models/";
	string objName = objPath + "cube.obj";

	SubdivisionProcessor processor;
	obj.initObject(objName);

	display(argc, argv);
	system("pause");

    return 0;
}
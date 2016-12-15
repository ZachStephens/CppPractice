#include "Room.h"

Room::Room()
{
    //ctor
    n = NULL;
    e = NULL,
    s = NULL;
    w = NULL;
    ns = "";
    es = "";
    ss = "";
    ws = "";
    type = "regular";
}

Room::~Room()
{
    //dtor
}

void Room::openContainer(char* C){
	unsigned int i;
	for(i=0;i<containers.size();i++){
		if(!containers[i]->name.compare(C)){
			containers[i]->showContents();
			return;
		}
	}
	cout << "There is no " << C << endl;
}

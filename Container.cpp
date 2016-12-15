#include "Container.h"

Container::Container()
{
    //ctor
}

Container::~Container()
{
    //dtor
}

bool Container::DoesAccept(string item){
	unsigned int i =0;
	if(accepts.size()==0){
		return 1;
	}
	for(i=0;i<accepts.size();i++){
		if(!accepts[i].compare(item))
				return 1;
	}
	return 0;
}

Item* Container::searchItem(string Iname){
	unsigned int i = 0;
	for(i=0;i<items.size();i++){
		if(!items[i]->name.compare(Iname)){
			return items[i];
		}
	}
	return NULL;
}


void Container::showContents(void){
	if(items.size() == 0){
		cout << "Container: empty" << endl;
		return;
	}
	unsigned int i;
	cout << name << " contains: " << items[0]->name;
	items[0]->takeable = 1;
	for(i = 1;i<items.size();i++){
		cout << ", " << items[i]->name;
		items[i]->takeable = 1;
	}
	cout << endl;
}

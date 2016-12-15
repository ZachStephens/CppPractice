#include "Item.h"
#include<iostream>
using namespace std;

Item::Item()
{
    //ctor
}

Item::~Item()
{
    //dtor
}

void Item::getWriting(){
	if(!writing.compare(""))
		cout << "Nothing written" << endl;
	else
		cout << writing <<endl;
}

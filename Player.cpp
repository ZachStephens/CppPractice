#include "Player.h"
using namespace std;

Player::Player()
{
    //ctor
}

Player::~Player()
{
    //dtor
}



Item* Player::searchItem(const char* Iname){
	unsigned int i = 0;
	for(i=0;i<inventory.size();i++){
		if(!inventory[i]->name.compare(Iname)){
			return inventory[i];
		}
	}
	return NULL;
}



void Player::readItem(char* Iname){

	Item* Iptr = searchItem(Iname);
	if(Iptr == NULL){
		cout <<  "do not have "<< Iname <<endl;
		return;
	}
	Iptr->getWriting();
}
void Player::dropItem(char* Iname)
{
	unsigned int i = 0;
	Item* Iptr = NULL;
	for(i=0;i<inventory.size();i++){
		if(!inventory[i]->name.compare(Iname)){
			Iptr = inventory[i];
			inventory.erase(inventory.begin()+i);
			location->items.push_back(Iptr);
			return;
			}
	}
	cout <<"You do not have "<< Iname << endl;
}

void Player::showI(void){
        	if(inventory.size() == 0){
        		cout << "Inventory: empty" << endl;
        		return;
        	}
        	unsigned int i;
        	cout << inventory[0]->name;
        	for(i = 1;i<inventory.size();i++){
        		cout << ", " << inventory[i]->name;
        	}
        	cout << endl;
}

void Player::putItem(char* Iname,char* Cname){
	unsigned int i = 0;
	Item* Iptr = NULL;
	Container* destC = NULL;


	for(i=0;i<location->containers.size();i++){
		if(!location->containers[i]->name.compare(Cname)){
			destC = location->containers[i];
		}
	}

	if(destC == NULL){
		cout << Cname << "does not exist"<< endl;
		return;
	}

	if(!destC->DoesAccept(Iname)){
		cout << Cname<<" does not accept "<< Iname <<endl;
		return;
	}

	for(i=0;i<inventory.size();i++){
		if(!inventory[i]->name.compare(Iname)){
			Iptr = inventory[i];
			inventory.erase(inventory.begin()+i);
			destC->items.push_back(Iptr);
			cout << Iname<<" added to "<< Cname <<endl;
			return;
			}
	}
	cout <<"You do not have "<< Iname << endl;
	return;
}

void Player::takeItem(const char* Iname){
        	Item* Iptr = NULL;
        	unsigned int i;
        	unsigned int j;
        	unsigned int k;
        	//checks room for item and puts into inventory
        	for(j=0;j<location->items.size();j++){
        		if(!location->items[j]->name.compare(Iname)){
        			Iptr = location->items[j];
        			location->items.erase(location->items.begin()+j);
        			inventory.push_back(Iptr);
        			cout << Iname << " taken" <<endl;
        			return;
        		}
        	}
        	//checks containers of room for item and puts into inventory
        	for(i=0;i<location->containers.size();i++){
        		for(k=0;k<location->containers[i]->items.size();k++){
        			if(!location->containers[i]->items[k]->name.compare(Iname)){
        				if(location->containers[i]->items[k]->takeable == 1){
        				Iptr = location->containers[i]->items[k];
        				location->containers[i]->items.erase(location->containers[i]->items.begin()+k);
        				inventory.push_back(Iptr);
        				cout << Iname << " taken"<<endl;
						return;
        				}
        			}
        		}
        	}
        	//returns if item not found
        	cout << "There is no " << Iname << endl;
}


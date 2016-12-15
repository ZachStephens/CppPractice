#include "GameData.h"
#include "Room.h"
#include "Trigger.h"
#include <string>
#include <vector>


GameData::GameData()
{
    //ctor
}

GameData::~GameData()
{
    //dtor
}






void GameData::putItem(char* Iname,char* Cname){
	player->putItem(Iname,Cname);
	//cout<< "closet test" <<endl;
	triggersByObject(string(Iname));
}


void GameData::AnalyzeTrigger(Trigger* t){
	unsigned int i=0;
	if(ConditionResult(t->conditions[0])){
		if((t->permanent == false) && (t->triggered == true))
			return;
		else{
		for(i=0;i<t->prints.size();i++)
			cout <<  t->prints[i] <<endl;
		for(i=0;i<t->actions.size();i++)
			performAction(t->actions[i]);

		if(t->permanent == false)
			t->triggered = true;
		}
	}
}


void GameData::triggersByObject(string Oname){
	unsigned int i= 0;
	unsigned int j= 0;
	unsigned int k= 0;
	//room item
	//cout << Oname <<endl;
	for(i=0;i<CurrentLocation->items.size();i++){
		for(j=0;j<CurrentLocation->items[i]->triggers.size();j++){
			if(!Oname.compare(CurrentLocation->items[i]->triggers[j].conditions[0].object)){
				AnalyzeTrigger(&CurrentLocation->items[i]->triggers[j]);
				if(ConditionResult(CurrentLocation->items[i]->triggers[j].conditions[0])){
					if(CurrentLocation->items[i]->triggers[j].permanent == false)
						CurrentLocation->items[i]->triggers.erase(CurrentLocation->items[i]->triggers.begin()+j);
				}
			}
		}
	}


	//room creatures
	for(i=0;i<CurrentLocation->creatures.size();i++){
		//cout<< CurrentLocation->creatures[i]->name <<endl;
		for(j=0;j<CurrentLocation->creatures[i]->triggers.size();j++){
					if(!Oname.compare(CurrentLocation->creatures[i]->triggers[j].conditions[0].object)){
						AnalyzeTrigger(&CurrentLocation->creatures[i]->triggers[j]);
						if(ConditionResult(CurrentLocation->creatures[i]->triggers[j].conditions[0])){
							if(CurrentLocation->creatures[i]->triggers[j].permanent == false)
								CurrentLocation->creatures[i]->triggers.erase(CurrentLocation->creatures[i]->triggers.begin()+j);
						}
					}
			}

	}

	//room containers
	for(i=0;i<CurrentLocation->containers.size();i++){
		//check container triggers

		for(j=0;j<CurrentLocation->containers[i]->triggers.size();j++){
			if(!Oname.compare(CurrentLocation->containers[i]->triggers[j].conditions[0].object)){
				AnalyzeTrigger(&CurrentLocation->containers[i]->triggers[j]);
				if(ConditionResult(CurrentLocation->containers[i]->triggers[j].conditions[0])){
					if(CurrentLocation->containers[i]->triggers[j].permanent == false)
						CurrentLocation->containers[i]->triggers.erase(CurrentLocation->containers[i]->triggers.begin()+j);
				}
			}
		}

		//room containers/items
		for(k=0;k<CurrentLocation->containers[i]->items.size();k++){
			//check item triggers in container
			for(j=0;j<CurrentLocation->containers[i]->items[k]->triggers.size();j++){
				if(!Oname.compare(CurrentLocation->containers[i]->items[k]->triggers[j].conditions[0].object)){
					AnalyzeTrigger(&CurrentLocation->containers[i]->items[k]->triggers[j]);
					if(ConditionResult(CurrentLocation->containers[i]->items[k]->triggers[j].conditions[0])){
						if(CurrentLocation->containers[i]->items[k]->triggers[j].permanent == false)
							CurrentLocation->containers[i]->items[k]->triggers.erase(CurrentLocation->containers[i]->items[k]->triggers.begin()+j);
					}

				}
			}
		}

	}

}
void GameData::turnOn(char* Iname){
	Item* Iptr = player->searchItem(Iname);
	if(Iptr == NULL){
		cout <<  "do not have "<< Iname <<endl;
		return;
	}
	cout << Iptr->turnonprint << endl;
	performAction(Iptr->turnonaction);
}

void GameData::dropItem(char* Iname){
	player->dropItem(Iname);
	performAction(Iname);
}

void GameData::takeItem(const char* Iname){
	player->takeItem(Iname);
	triggersByObject(Iname);
}


void GameData::parseAction(vector<string> v)
{

	unsigned int i=0;
	unsigned int j=0;
	Item* iptr = NULL;

	//for(i=0;i<v.size();i++){
		//cout << v[i] << endl;
	//}
	if(!v[0].compare("Update")){
		for(i=0;i<CurrentLocation->containers.size();i++){
			if(!v[1].compare(CurrentLocation->containers[i]->name)){
				CurrentLocation->containers[i]->updateTo(v[3]);
				return;
			}
		}
		iptr = getRoomItem(v[1]);
		if(iptr==NULL){
			iptr = player->searchItem(v[1].c_str());
		}

		if(iptr==NULL){
			cout<<"parseaction update NULL 2" <<endl;
			return;
		}
		iptr->updateTo(v[3]);
		return;
	}else if(!v[0].compare("Game")){
		GameData::finished = 1;
		cout << "GAME OVER"<<endl;
		return;
	}
	else if(!v[0].compare("n")){
		CurrentLocation = CurrentLocation->n;
		player->location = CurrentLocation;
		return;
	}
	else if(!v[0].compare("s")){

			CurrentLocation = CurrentLocation->s;
			player->location = CurrentLocation;
			return;
	}
	else if(!v[0].compare("e")){
			CurrentLocation = CurrentLocation->e;
			player->location = CurrentLocation;
			return;
	}
	else if(!v[0].compare("w")){
			CurrentLocation = CurrentLocation->w;
			player->location = CurrentLocation;
			return;
	}else if (!v[0].compare("attack")){
		cout << "in attack" << endl;

		attacks(v[1],v[3]);
		//triggersByObject(v[1]);
		return;
	}else if (!v[0].compare("take")){
		takeItem(v[1].c_str());
		//triggersByObject(v[1]);
		return;
	}
	else if (!v[0].compare("Delete")){
		removeObjects(v[1]);
		//triggersByObject(v[1]);
		return;
	}else if (!v[0].compare("Add")){
		//cout << " IN add" << endl;
		for(i=0;i<rooms.size();i++){
			if(!rooms[i].name.compare(v[3])){
				for(j=0;j<creatures.size();i++){
					if(!creatures[j].name.compare(v[1])){
						rooms[i].creatures.push_back(&creatures[j]);
						triggersByObject(v[1]);
						return;
					}
				}

				for(j=0;j<items.size();i++){
					if(!items[j].name.compare(v[1])){
						rooms[i].items.push_back(&items[j]);
						triggersByObject(v[1]);
						return;
					}
				}
			}
		}

		for(i=0;i<CurrentLocation->containers.size();i++){
			if(!CurrentLocation->containers[i]->name.compare(v[3])){
				for(j=0;j<items.size();i++){
					if(!items[j].name.compare(v[1])){
						rooms[i].items.push_back(&items[j]);
						triggersByObject(v[1]);
						return;
					}
				}
			}
		}

	}
}

void GameData::performAction(string Aname){

		char *a= new char[Aname.length()+1];
		char* c;
		strcpy(a,Aname.c_str());
		unsigned int len;
		vector<string> v;
		if(strlen(a)== 0)
			return;
		unsigned int i=0;
		c=a;
		len = strlen(a);

		for(i=0;i<len;i++){
			if(a[i] == ' '){
				a[i]='\0';
				v.push_back(string(c));
				c = &a[i+1];
			}
		}
		v.push_back(c);
		delete [] a;



	    parseAction(v);

	    if(v.size()>1)
	    	triggersByObject(v[1]);//post command reaction

}

void GameData::attacks(string Crname,string Iname){
	//find creature
	unsigned int i = 0;
	unsigned int j = 0;
	Creature* Crptr = NULL;
	Item* iptr = NULL;

	iptr = player->searchItem(Iname.c_str());
	if(iptr == NULL){
		cout<< "you do not have a "<<Iname <<endl;
		return;
	}

	if(CurrentLocation->creatures.size()==0){
		cout<< "There isn't anything to attack" <<endl;
		return;
	}

	/*for(i=0;i<CurrentLocation->creatures.size();i++){
		cout <<  CurrentLocation->creatures[i]->name <<endl;
	}*/

	for(i=0;i<CurrentLocation->creatures.size();i++){
		//cout << "in creatures loop "<< endl;
			if(!CurrentLocation->creatures[i]->name.compare(Crname))
				Crptr = CurrentLocation->creatures[i];
		}
	if(Crptr == NULL){
		cout << "No "<<Crname<<" in here"<<endl;
		return;
	}

	//check condition
	for(i=0;i<Crptr->triggers.size();i++){
		if(Crptr->triggers[i].commands.size()>0){
			if(!Crptr->triggers[i].commands[0].compare("attack "+Crname+" with "+Iname)){
				if(ConditionResult(Crptr->triggers[i].conditions[0])){
					if(Crptr->triggers[i].triggered==false){
						Crptr->triggers[i].triggered = true;
						for(j=0;j<Crptr->triggers[i].prints.size();j++){
							cout << Crptr->triggers[i].prints[j] <<endl;
						}
						for(j=0;j<Crptr->triggers[i].actions.size();j++){
							//cout <<Crptr->triggers[i].actions.size()<<endl;
							performAction(Crptr->triggers[i].actions[j]);
						}
					}else{
						Crptr->triggers.erase(Crptr->triggers.begin()+i);
					}
				}
			}
		}
	}



	if(Crptr->IsWeakness(Iname)){
		if(ConditionResult(Crptr->attack.condition)){
			for(i=0;i<Crptr->attack.prints.size();i++){
				cout << Crptr->attack.prints[i] <<endl;
			}
			for(i=0;i<Crptr->attack.actions.size();i++){
				//cout<< i<< endl;
				performAction(Crptr->attack.actions[i]);
			}
		}
		else
			cout<<"Didn't quite work"<<endl;
	}
	else
		cout<<"Attack with "<<Iname<<" is ineffective"<<endl;


}


bool GameData::preCommandTrigger(char* command){
	//find triggers in room that correspond to command that negate trigger
	unsigned int i =0;
	unsigned int j = 0;
	for(i=0;i<CurrentLocation->triggers.size();i++){
		for(j=0;j<CurrentLocation->triggers[i].commands.size();j++){
			if(!CurrentLocation->triggers[i].commands[j].compare(command)){
				if(ConditionResult(CurrentLocation->triggers[i].conditions[0])){
					AnalyzeTrigger(&CurrentLocation->triggers[i]);
					if(CurrentLocation->triggers[i].permanent==false)
						CurrentLocation->triggers.erase(CurrentLocation->triggers.begin()+i);
					return 1;
				}
			}
		}
	}
	//cout << "No  Pre triggers found for command "<< command<<endl;

	return 0;
}



Item* GameData::getContainerItem(string Cname, string Iname){
	//return item if it is in the room
	Item* Iptr = NULL;
	unsigned int i;
	for(i=0;i<CurrentLocation->containers.size();i++){
		if(!Cname.compare(CurrentLocation->containers[i]->name)){
			Iptr = CurrentLocation->containers[i]->searchItem(Iname);
			if(Iptr != NULL)
				return Iptr;
		}
	}
	return NULL;
}

Item* GameData::getRoomItem(string Iname){
	Item* Iptr = NULL;
	unsigned int i;
	for(i=0;i<CurrentLocation->items.size();i++){
		if(!Iname.compare(CurrentLocation->items[i]->name)){
			Iptr = CurrentLocation->items[i];
			if(Iptr != NULL)
				return Iptr;
		}
	}
	//removeObjects(string object);
	return NULL;
}


GameObject* GameData::searchObjects(string object){
	GameObject* Gptr=NULL;
	unsigned int i = 0;
	Gptr = getRoomItem(object);
	if(Gptr != NULL)
		return Gptr;
	for(i=0;i<CurrentLocation->containers.size();i++){
		if(!CurrentLocation->containers[i]->name.compare(object))
			return CurrentLocation->containers[i];
	}
	for(i=0;i<CurrentLocation->creatures.size();i++){
		if(!CurrentLocation->creatures[i]->name.compare(object))
			return CurrentLocation->creatures[i];
	}
	return NULL;
}


void GameData::removeObjects(string object){
	unsigned int i = 0;
	for(i=0;i<player->inventory.size();i++){
		if(!player->inventory[i]->name.compare(object)){
			player->inventory.erase(player->inventory.begin()+i);
			return;
		}
	}

	for(i=0;i<CurrentLocation->containers.size();i++){
		if(!CurrentLocation->containers[i]->name.compare(object)){
			CurrentLocation->containers.erase(CurrentLocation->containers.begin()+i);
			return;
		}
	}
	for(i=0;i<CurrentLocation->creatures.size();i++){
		if(!CurrentLocation->creatures[i]->name.compare(object)){
			CurrentLocation->creatures.erase(CurrentLocation->creatures.begin()+i);
			return;
		}
	}
}





bool GameData::ConditionResult(Condition condition){
//trigger has only one condition
	string has = condition.has;
	string owner = condition.owner;
	string status = condition.status;
	string object = condition.object;
	GameObject* objectptr = NULL;

	if(status.empty()){//what is status intialized to???
		//owner has/does not have object?
		//inventory?
		if(!owner.compare("inventory"))
			objectptr = player->searchItem( object.c_str());
		else
			objectptr = getContainerItem(owner,object);
		//has = yes?
		if(!has.compare("yes")){
			if(objectptr == NULL)
				return 0;
			return 1;
		}
		else{
			if(objectptr == NULL)
				return 1;
			return 0;
		}
	}
	else{
		objectptr = player->searchItem(object.c_str());
		if(objectptr == NULL){
			objectptr = searchObjects(object);
		}
		if(objectptr == NULL)
			cout << "condition error could not find "<< object << endl;
		if(!objectptr->status.compare(status))
			return 1;
		return 0;
		//object.status == status?
	}

	//

	return 0;
}



void updatePointersC(Container* c, GameData* gdat)
{
    c->items.clear();
    for(unsigned int i=0; i<c->sitems.size(); i++){
        for(unsigned int j=0; j<gdat->items.size(); j++){
            if(gdat->items[j].name == c->sitems[i]){
                c->items.push_back(&gdat->items[j]);
                //std::cout<<"item: "<<gdat->items[j].name<<" added to container: "<<c->name<<std::endl;
            }
        }
    }
}

void updatePointersR(Room* r, GameData* gdat)
{
    r->containers.clear();
    for(unsigned int i=0; i<r->scontainers.size(); i++){
        for(unsigned int j=0; j<gdat->containers.size(); j++){
            if(gdat->containers[j].name == r->scontainers[i]){
                r->containers.push_back(&gdat->containers[j]);
                //std::cout<<"container: "<<gdat->containers[j].name<<" added to room: "<<r->name<<std::endl;
            }
        }
    }
    r->items.clear();
    for(unsigned int i=0; i<r->sitems.size(); i++){
        for(unsigned int j=0; j<gdat->items.size(); j++){
            if(gdat->items[j].name == r->sitems[i]){
                r->items.push_back(&gdat->items[j]);
                //std::cout<<"item: "<<gdat->items[j].name<<" added to room: "<<r->name<<std::endl;
            }
        }
    }
    r->creatures.clear();
    for(unsigned int i=0; i<r->screatures.size(); i++){
        for(unsigned int j=0; j<gdat->creatures.size(); j++){
            if(gdat->creatures[j].name == r->screatures[i]){
                r->creatures.push_back(&gdat->creatures[j]);
                //std::cout<<"creature: "<<gdat->creatures[j].name<<" added to room: "<<r->name<<std::endl;
            }
        }
    }
    for(unsigned int i=0; i<gdat->rooms.size(); i++){
        if(r->ns == gdat->rooms[i].name){
            r->n = &gdat->rooms[i]; //std::cout<<"added pointer to room "<<gdat->rooms[i].name<<" to room "<<r->name<<std::endl;
        }else if(r->es == gdat->rooms[i].name){
            r->e = &gdat->rooms[i]; //std::cout<<"added pointer to room "<<gdat->rooms[i].name<<" to room "<<r->name<<std::endl;
        }else if(r->ss == gdat->rooms[i].name){
            r->s = &gdat->rooms[i]; //std::cout<<"added pointer to room "<<gdat->rooms[i].name<<" to room "<<r->name<<std::endl;
        }else if(r->ws == gdat->rooms[i].name){
            r->w = &gdat->rooms[i]; //std::cout<<"added pointer to room "<<gdat->rooms[i].name<<" to room "<<r->name<<std::endl;
        }
    }
}

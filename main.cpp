
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "rapidxml-1.13/rapidxml.hpp"

#include "GameObject.h"
#include "Container.h"
#include "Room.h"
#include "Item.h"
#include "Creature.h"
#include "Player.h"
#include "Condition.h"
#include "Trigger.h"
#include "GameData.h"

using namespace std;
using namespace rapidxml;


Condition readInCondition(xml_node<> * Node)
{
    Condition myCondition;

    for (xml_node<>* nxtNode = Node->first_node(); nxtNode ; nxtNode = nxtNode->next_sibling()){
        //object-generic stuff
        if(!strcmp(nxtNode->name(),"has")){
            myCondition.has = nxtNode->value();
        }else if(!strcmp(nxtNode->name(),"owner")){
            myCondition.owner = nxtNode->value();
        }else if(!strcmp(nxtNode->name(),"status")){
            myCondition.status = nxtNode->value();
        }else if(!strcmp(nxtNode->name(),"object")){
            myCondition.object = nxtNode->value();
        }else{
            cout<<"Unknown condition attribute: "<<nxtNode->name()<<endl;
        }
    }

    return myCondition;
}

Trigger readInTrigger(xml_node<> * Node)
{
    Trigger myTrigger;
    for (xml_node<>* nxtNode = Node->first_node(); nxtNode ; nxtNode = nxtNode->next_sibling()){
        //object-generic stuff
        if(!strcmp(nxtNode->name(),"type")){
            if(!strcmp(nxtNode->value(),"single")){
                myTrigger.permanent = false;
            }else if(!strcmp(nxtNode->value(),"permanent")){
                myTrigger.permanent = true;
            }else{
                cout<<"Unknown value for triggers type: "<<nxtNode->value()<<endl;
            }
        }else if(!strcmp(nxtNode->name(),"command")){
            myTrigger.commands.push_back(nxtNode->value());
        }else if(!strcmp(nxtNode->name(),"print")){
            myTrigger.prints.push_back(nxtNode->value());
        }else if(!strcmp(nxtNode->name(),"action")){
            myTrigger.actions.push_back(nxtNode->value());
        }else if(!strcmp(nxtNode->name(),"condition")){
            myTrigger.conditions.push_back(readInCondition(nxtNode));
        }
        else{
            cout<<"Unknown trigger attribute: "<<nxtNode->name()<<endl;
        }
    }
    myTrigger.triggered = false;
    return myTrigger;
}

Room readInRoom(xml_node<> * Node)
{
    Room myRoom;
    for (xml_node<> * nxtNode = Node->first_node(); nxtNode ; nxtNode  = nxtNode ->next_sibling()){

        //object-generic stuff
        if(!strcmp(nxtNode->name(),"name")){
            myRoom.name = nxtNode->value();
        }else if(!strcmp(nxtNode->name(),"description")){
            myRoom.description = nxtNode->value();
        }else if(!strcmp(nxtNode->name(),"status")){
            myRoom.status = nxtNode->value();
        }else if(!strcmp(nxtNode->name(),"trigger")){
            myRoom.triggers.push_back(readInTrigger(nxtNode));
        }
        //room specific stuff
        else if(!strcmp(nxtNode->name(),"type")){
            myRoom.type = nxtNode->value();
        }else if(!strcmp(nxtNode->name(),"border")){
            //read in direction and name (its always those two)
                    xml_node<> * obj3Node = nxtNode->first_node();
                    int dir = 0;
                    string nxtroomname;
                    if(!strcmp(obj3Node->name(),"direction")){
                        if(!strcmp(obj3Node->value(),"north")){dir=1;}else if(!strcmp(obj3Node->value(),"east")){dir=2;}else if(!strcmp(obj3Node->value(),"south")){dir=3;}else if(!strcmp(obj3Node->value(),"west")){dir=4;}else{cout<<"invalid border direction: "<<obj3Node->value()<<endl;}
                    }else if(!strcmp(obj3Node->name(),"name")){
                        nxtroomname = obj3Node->value();
                    }else{cout<<"Unknown border attribute: "<<obj3Node->name()<<endl;}
                    obj3Node = obj3Node->next_sibling();
                    if(!strcmp(obj3Node->name(),"direction")){
                        if(!strcmp(obj3Node->value(),"north")){dir=1;}else if(!strcmp(obj3Node->value(),"east")){dir=2;}else if(!strcmp(obj3Node->value(),"south")){dir=3;}else if(!strcmp(obj3Node->value(),"west")){dir=4;}else{cout<<"invalid border direction: "<<obj3Node->value()<<endl;}
                    }else if(!strcmp(obj3Node->name(),"name")){
                        nxtroomname = obj3Node->value();
                    }else{cout<<"Unknown border attribute: "<<obj3Node->name()<<endl;}
                    if(dir==0){cout<<"No direction specified for room: "<<nxtroomname<<endl;}
                    else if(dir==1){myRoom.ns=nxtroomname;}else if(dir==2){myRoom.es=nxtroomname;}else if(dir==3){myRoom.ss=nxtroomname;}else if(dir==4){myRoom.ws=nxtroomname;}

        }else if(!strcmp(nxtNode->name(),"container")){
            myRoom.scontainers.push_back(nxtNode->value());
        }else if(!strcmp(nxtNode->name(),"item")){
            myRoom.sitems.push_back(nxtNode->value());
        }else if(!strcmp(nxtNode->name(),"creature")){
            myRoom.screatures.push_back(nxtNode->value());
        }
        else{
            cout<<"Unknown attribute: "<<nxtNode->name()<<" in room "<<myRoom.name<<endl;
        }

    }

    return myRoom;
}
Item readInItem(xml_node<> * Node)
{
    Item myItem;

    for (xml_node<>* nxtNode = Node->first_node(); nxtNode ; nxtNode = nxtNode->next_sibling()){
        //object-generic stuff
        if(!strcmp(nxtNode->name(),"name")){
            myItem.name = nxtNode->value();
        }else if(!strcmp(nxtNode->name(),"description")){
            myItem.description = nxtNode->value();
        }else if(!strcmp(nxtNode->name(),"status")){
            myItem.status = nxtNode->value();
        }else if(!strcmp(nxtNode->name(),"trigger")){
            myItem.triggers.push_back(readInTrigger(nxtNode));
        }
        //specific stuff
        else if(!strcmp(nxtNode->name(),"writing")){
            myItem.writing = nxtNode->value();
        }
        else if(!strcmp(nxtNode->name(),"turnon")){
            //get turn onprint and turnon action (its always those two)
            xml_node<>* thrdNode = nxtNode->first_node();
            if(!strcmp(thrdNode->name(),"print")){
                myItem.turnonprint = thrdNode->value();
            }else if(!strcmp(thrdNode->name(),"action")){
                myItem.turnonaction = thrdNode->value();
            }else{
                cout<<"Unknown turnon attribute: "<<thrdNode->name()<<endl;
            }
            thrdNode = thrdNode->next_sibling();
            if(!strcmp(thrdNode->name(),"print")){
                myItem.turnonprint = thrdNode->value();
            }else if(!strcmp(thrdNode->name(),"action")){
                myItem.turnonaction = thrdNode->value();
            }else{
                cout<<"Unknown turnon attribute: "<<thrdNode->name()<<endl;
            }
        }

        else{
            cout<<"Unknown Item attribute: "<<nxtNode->name()<<endl;
        }
    }

    return myItem;
}
Creature readInCreature(xml_node<> * Node)
{
    Creature myCreature;

    for (xml_node<>* nxtNode = Node->first_node(); nxtNode ; nxtNode = nxtNode->next_sibling()){
        //object-generic stuff
        if(!strcmp(nxtNode->name(),"name")){
            myCreature.name = nxtNode->value();
        }else if(!strcmp(nxtNode->name(),"description")){
            myCreature.description = nxtNode->value();
        }else if(!strcmp(nxtNode->name(),"status")){
            myCreature.status = nxtNode->value();
        }else if(!strcmp(nxtNode->name(),"trigger")){
            myCreature.triggers.push_back(readInTrigger(nxtNode));
        }
        //specific stuff
        else if(!strcmp(nxtNode->name(),"vulnerability")){
            myCreature.vulnerabilities.push_back(nxtNode->value());
        }
        else if(!strcmp(nxtNode->name(),"attack")){
            for (xml_node<>* thrdNode = nxtNode->first_node(); thrdNode ; thrdNode = thrdNode->next_sibling()){
                if(!strcmp(thrdNode->name(),"condition")){
                    myCreature.attack.condition = readInCondition(thrdNode);
                }else if(!strcmp(thrdNode->name(),"action")){
                    myCreature.attack.actions.push_back(thrdNode->value());
                }else if(!strcmp(thrdNode->name(),"print")){
                    myCreature.attack.prints.push_back(thrdNode->value());
                }else{
                    cout<<"Unknown attack attribute: "<<thrdNode->name()<<" for creature: "<<myCreature.name<<endl;
                }
            }
        }

        else{
            cout<<"Unknown Creature attribute: "<<nxtNode->name()<<endl;
        }
    }

    return myCreature;
}
Container readInContainer(xml_node<> * Node)
{
    Container myContainer;

    for (xml_node<>* nxtNode = Node->first_node(); nxtNode ; nxtNode = nxtNode->next_sibling()){
        //object-generic stuff
        if(!strcmp(nxtNode->name(),"name")){
            myContainer.name = nxtNode->value();
        }else if(!strcmp(nxtNode->name(),"description")){
            myContainer.description = nxtNode->value();
        }else if(!strcmp(nxtNode->name(),"status")){
            myContainer.status = nxtNode->value();
        }else if(!strcmp(nxtNode->name(),"trigger")){
            myContainer.triggers.push_back(readInTrigger(nxtNode));
        }
        //specific stuff
        else if(!strcmp(nxtNode->name(),"accept")){
            myContainer.accepts.push_back(nxtNode->value());
        }else if(!strcmp(nxtNode->name(),"item")){
            myContainer.sitems.push_back(nxtNode->value());
        }
        else{
            cout<<"Unknown Container attribute: "<<nxtNode->name()<<endl;
        }
    }
    unsigned int i;
    for(i=0;i<myContainer.items.size();i++){
    	myContainer.items[i]->takeable = 0;
    }

    return myContainer;
}




bool handleCommand(char** Cptr,Player* myPlayer,GameData* game)
{
	char b[40];
	char* a = b;
	char* c;
	cin.getline (a,40);
	unsigned int len;

	vector<char*> v;
	if(strlen(a)== 0)
		return 0;
	unsigned int i=0;
	c=a;

	len = strlen(a);
	for(i=0;i<len;i++){
		if(a[i] == ' '){

			a[i]='\0';
			v.push_back(c);
			c = &a[i+1];
		}
	}
	v.push_back(c);
	*Cptr = v[0];

	if(game->preCommandTrigger(v[0]))
		return 0;
	if(!strcmp(v[0],"n")){

		if(myPlayer->location->n != NULL){
			myPlayer->location=myPlayer->location->n;
		}
		else
			cout << "Cannot travel north" << endl;
		return 1;
	}
	else if(!strcmp(v[0],"s")){
		if(myPlayer->location->s != NULL)
			myPlayer->location=myPlayer->location->s;
		else
			cout << "Cannot travel south" << endl;
		return 1;
	}
	else if(!strcmp(v[0],"e")){
		if(myPlayer->location->e != NULL)
			myPlayer->location=myPlayer->location->e;
		else
			cout << "Cannot travel east" << endl;
		return 1;
	}

	else if(!strcmp(v[0],"w")){
		if(myPlayer->location->w != NULL)
			myPlayer->location=myPlayer->location->w;
		else
			cout << "Cannot travel west" << endl;
		return 1;
	}
	else if(!strcmp(v[0],"i")){
			myPlayer->showI();
			return 1;
		}
	else if(!strcmp(v[0],"take")){
		if(v.size()==2){
			game->takeItem(v[1]);
			return 1;
		}
		else{
			cout << "Take what??" << endl;
			return 1;
		}
	}
	else if(!strcmp(v[0],"open"))
	{
			if(v.size()==2){
				if(!strcmp(v[1],"exit")){
					if(!game->CurrentLocation->type.compare("exit")){
						cout << "GAME OVER" <<endl;
						game->finished =1;
						return 1;
					}else
						return 0;
				}
				else
					myPlayer->location->openContainer(v[1]);
			}
			return 0;
	}
	else if(!strcmp(v[0],"read")){
		if(v.size()==2)
			myPlayer->readItem(v[1]);
			else
				cout << "read what?"<< endl;
		return 1;
	}
	else if(!strcmp(v[0],"drop")){
		if(v.size()==2){
			game->dropItem(v[1]);
		}
		else
			cout << "drop what?" <<endl;
		return 1;

	}
	else if(!strcmp(v[0],"put")){
		if(v.size()==4){
			if(!strcmp(v[2],"in")){
				game->putItem(v[1],v[3]);
			}
			else
				return 0;
		}
		else
			cout << "put what?" << v.size() << endl;
		return 1;
	}
	else if(!strcmp(v[0],"turn")){
		if(!strcmp(v[1],"on")){
			game->turnOn(v[2]);
			return 1;
		}
	}
	else if(!strcmp(v[0],"attack")){
		if(v.size()==4){
			if(!strcmp(v[2],"with"))
				game->attacks(v[1],v[3]);
			else
				cout<< "how?"<<endl;
		}
		else
			cout <<"try [attack <creature> with <item>]"<<endl;
		return 1;
	}else if(!strcmp(v[0],"Game")){
		if(v.size()==2){
			if(!strcmp(v[1],"Over")){
				game->finished =1;
				return 1;
			}else
				return 0;
		}
	}else if(!strcmp(v[0],"Update")){
		if(v.size()==4){
			if(!strcmp(v[2],"to")){

				game->performAction(string(v[0])+" "+string(v[1])+" "+string(v[2])+" "+string(v[3]));
				return 1;
			}else
				return 0;
		}
	}

	cout << "I do not understand what to do" << endl;
	return 0;


}

void InputManager(Player* myPlayer,GameData* game){
	bool result;
	char* Cptr=NULL;
	result = handleCommand(&Cptr,myPlayer,game);
	//game->postCommandTrigger(Cptr);//  To check the triggers after the command has been issued
	return;
}



int main(int argc, char* args[])
{
    string filename;
    if(argc == 1){
        filename = "maps/creaturesample.xml";
    }
    else if(argc == 2){
        filename = args[1];
    }else{
        cout<<"ERROR: Please pass a map file as an argument!"<<endl;
        cout<<argc<<endl;
        return -1;
    }


    //create Player and Game Object
    Player myPlayer;
    GameData game;
    game.player = &myPlayer;


    //open file and parse it
    xml_document<> doc;
    ifstream file(filename.c_str());
    stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    string content(buffer.str());
    doc.parse<0>(&content[0]);


    //create gamedata from map
    xml_node<> *root_node = doc.first_node("map");
    for (xml_node<> * objectNode = root_node->first_node(); objectNode; objectNode = objectNode->next_sibling()){

        if(!strcmp(objectNode->name(),"room")){

            game.rooms.push_back(readInRoom(objectNode));

        }else if(!strcmp(objectNode->name(),"item")){

           game.items.push_back(readInItem(objectNode));

        }else if(!strcmp(objectNode->name(),"container")){

            game.containers.push_back(readInContainer(objectNode));

        }else if(!strcmp(objectNode->name(),"creature")){

            game.creatures.push_back(readInCreature(objectNode));

        }else{
            cout<<"EEROR: Unknown object type: "<<objectNode->name()<<endl;
        }

	}
	//everything is read in!
	//now go through all the objects and parse the strings to pointers (i.e. roomdirections, items, etc)




    for(unsigned int i=0; i<game.rooms.size(); i++){
        updatePointersR(&game.rooms[i], &game);
        if(game.rooms[i].name == "Entrance")
        	myPlayer.location = &game.rooms[i];

    }



    for(unsigned int i=0; i<game.containers.size(); i++){
        updatePointersC(&game.containers[i], &game);
    }


    ///game loop
   Room* previousRoom;
   game.finished = 0;
    while(!game.finished){
	   previousRoom = myPlayer.location;
	   cout<<myPlayer.location->name << endl << myPlayer.location->description <<endl;
	   game.CurrentLocation = myPlayer.location;

	   while(myPlayer.location == previousRoom)
	   {
		   InputManager(&myPlayer,&game);
		   if(game.finished)
			   return 0;
	   }
	 }

    cout << "finished";

    return 0;
}

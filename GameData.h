#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <string>
#include <vector>
#include <cstring>
#include "GameObject.h"
#include "Room.h"
#include "Container.h"
#include "Item.h"
#include "Creature.h"
#include "Player.h"

class GameData
{
    public:
        GameData();
        virtual ~GameData();

        std::vector<Room> rooms;
        std::vector<Container> containers;
        std::vector<Item> items;
        std::vector<Creature> creatures;
        Room* CurrentLocation;
        Player* player;
        void triggersByObject(string);
        int finished;
        void AnalyzeTrigger(Trigger*);
        bool preCommandTrigger(char*);
		bool ConditionResult(Condition);
		Item* getContainerItem(string, string);
		Item* getRoomItem(string);
		GameObject* searchObjects(string);
		void attacks(string,string);
		void performAction(string);
		void parseAction(vector<string>);
		void removeObjects(string);
		void turnOn(char*);
		void putItem(char*,char*);
		void dropItem(char*);
		void takeItem(const char*);

    protected:
    private:
};

void updatePointersC(Container *c, GameData *gdat);
void updatePointersR(Room *r, GameData *gdat);



#endif // GAMEDATA_H

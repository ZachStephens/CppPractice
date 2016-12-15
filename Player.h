#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Room.h"
#include "Item.h"



class Player
{
    public:
		Room* location;
		 std::vector<Item*> inventory;
        Player();
        virtual ~Player();
        void showI(void);
        void takeItem(const char*);
        void dropItem(char*);
        void putItem(char*,char*);
        void readItem(char*);

        Item* searchItem(const char*);
    protected:
    private:
};



#endif // PLAYER_H

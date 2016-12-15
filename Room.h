#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>

#include "GameObject.h"
#include "Container.h"
#include "Item.h"
#include "Creature.h"

#include <iostream>



class Room : public GameObject
{
    public:
        Room();
        virtual ~Room();

        std::string type;
        Room* n; std::string ns;
        Room* e; std::string es;
        Room* s; std::string ss;
        Room* w; std::string ws;

        std::vector<Container*> containers;
        std::vector<std::string> scontainers;
        std::vector<Item*> items;
        std::vector<std::string> sitems;
        std::vector<Creature*> creatures;
        std::vector<std::string> screatures;
        void openContainer(char*);



    protected:
    private:
};

#endif // ROOM_H

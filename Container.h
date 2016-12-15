#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include <vector>
#include <iostream>
#include "GameObject.h"
#include "Item.h"
using namespace std;


class Container : public GameObject
{
    public:
        Container();
        virtual ~Container();

        std::vector<std::string> accepts;
        std::vector<Item*> items;
        std::vector<std::string> sitems;

        void showContents(void);
        Item* searchItem(string);
        bool DoesAccept(string);

    protected:
    private:
};

#endif // CONTAINER_H

#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>

#include "GameObject.h"



class Item : public GameObject
{
    public:
        Item();
        virtual ~Item();



        std::string writing;
        std::string turnonprint;
        std::string turnonaction;
        int takeable;
        void getWriting(void);

    protected:
    private:
};

#endif // ITEM_H

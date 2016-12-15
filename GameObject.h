#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>

#include "Trigger.h"

class GameObject
{
    public:
        GameObject();
        virtual ~GameObject();

        std::string name;
        std::string description;
        std::string status;

        std::vector<Trigger> triggers;




        bool updateTo(std::string newStatus);
    protected:
    private:
};

#endif // GAMEOBJECT_H

#ifndef CREATURE_H
#define CREATURE_H


#include <vector>
#include <string>

#include "GameObject.h"
#include "Condition.h"

struct Attack
{
    Condition condition;
    std::vector<std::string> actions;
    std::vector<std::string> prints;
};


class Creature : public GameObject
{
    public:
        Creature();
        virtual ~Creature();
        std::vector<std::string> vulnerabilities;
        Attack attack;

        bool IsWeakness(std::string);

    protected:
    private:
};

#endif // CREATURE_H

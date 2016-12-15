#ifndef TRIGGER_H
#define TRIGGER_H

#include <string>
#include <vector>

#include "Condition.h"

class Trigger
{
    public:
        Trigger();
        virtual ~Trigger();

        bool permanent;
        std::vector<std::string> commands;
        std::vector<std::string> prints;
        std::vector<std::string> actions;
        std::vector<Condition> conditions;
        bool triggered;



    protected:
    private:
};

#endif // TRIGGER_H

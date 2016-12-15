#ifndef CONDITION_H
#define CONDITION_H

#include <string>
#include <vector>

class Condition
{
    public:
        Condition();
        virtual ~Condition();

        std::string has;
        std::string owner;
        std::string status;
        std::string object;



    protected:
    private:
};

#endif // CONDITION_H

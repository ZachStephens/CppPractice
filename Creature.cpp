#include "Creature.h"
#include <string>
#include <vector>

Creature::Creature()
{
    //ctor
}

Creature::~Creature()
{
    //dtor
}


bool Creature::IsWeakness(std::string weapon){
	unsigned int i=0;
	for(i=0;i<vulnerabilities.size();i++){
		if(!weapon.compare(vulnerabilities[i])){
			return 1;
		}
	}
	return 0;
}

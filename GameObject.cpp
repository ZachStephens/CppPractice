#include "GameObject.h"

GameObject::GameObject()
{
    //ctor
}

GameObject::~GameObject()
{
    //dtor
}

bool GameObject::updateTo(std::string newStatus){
    this->status = newStatus;
    return true;
}




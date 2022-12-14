#include "ECS.h"

void Entity::addGroup(Group mGroup) {
	groupBitSet[mGroup] = true;
	manager.AddToGroup(this, mGroup);
}

void Entity::setController(Controller *cont) {
    std::cout << "HERESET" << std::endl;
    controller = cont;
    controller->entity = this;
    controller->init();
    hasController = true;
}
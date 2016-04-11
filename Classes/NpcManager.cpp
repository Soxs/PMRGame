//
//  NpcManager.cpp
//  PMRGame
//
//  Created by Zakary Pacha on 09/04/2016.
//
//

#include "NpcManager.hpp"

using namespace cocos2d;

NpcManager::NpcManager() {
    structarray = new Vector<Entity*>;
    //Vector<BrokenStructure*> structarray (15);
}

Vector<Entity*>* NpcManager::getNpcs() {
    return structarray;
}

void NpcManager::addNpc(Entity* toadd) {
    structarray->pushBack(toadd);
}

void NpcManager::removeNpc(Entity* toRemove){

			structarray->eraseObject(toRemove);
			//toRemove->entityImage->removeFromParent();
}
void NpcManager::resetManager() {
    structarray->clear();
}
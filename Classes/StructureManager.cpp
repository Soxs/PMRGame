//
//  StructureManager.cpp
//  PMRGame
//
//  Created by Zakary Pacha on 13/02/2016.
//
//

#include "StructureManager.hpp"

using namespace cocos2d;

StructureManager::StructureManager() {
    structarray = new Vector<BrokenStructure*>;
    //Vector<BrokenStructure*> structarray (15);
}

void StructureManager::addStructure(BrokenStructure* toadd) {
    structarray->pushBack(toadd);
}

void StructureManager::resetManager() {
    structarray->clear();
}

bool StructureManager::containsStructure(int gid, Vec2 location) {
    for (BrokenStructure* e : *structarray) {
        if (e->getGID() == gid &&
            location.distance(e->location) == 0)
            return true;
    }
    return false;
}

Vector<BrokenStructure*>* StructureManager::getStructures() {
    return structarray;
}
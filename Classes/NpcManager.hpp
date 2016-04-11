//
//  NpcManager.hpp
//  PMRGame
//
//  Created by Zakary Pacha on 09/04/2016.
//
//

#ifndef NpcManager_hpp
#define NpcManager_hpp

#include <stdio.h>
#include "Entity.hpp"


class NpcManager {
public:
    NpcManager();
    void addNpc(Entity* structToAdd);
    void removeNpc(Entity* toRemove);
    void resetManager();
    cocos2d::Vector<Entity*>* getNpcs();
private:
    cocos2d::Vector<Entity*>* structarray;
};

#endif /* NpcManager_hpp */
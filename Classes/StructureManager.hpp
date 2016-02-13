//
//  StructureManager.hpp
//  PMRGame
//
//  Created by Zakary Pacha on 13/02/2016.
//
//

#ifndef StructureManager_hpp
#define StructureManager_hpp

#include <stdio.h>
#include "BrokenStructure.hpp"


class StructureManager {
public:
    StructureManager();
    void addStructure(BrokenStructure* structToAdd);
    void resetManager();
    bool containsStructure(int gid, cocos2d::Vec2 location);
private:
    cocos2d::Vector<BrokenStructure*>* structarray;
};

#endif /* StructureManager_hpp */

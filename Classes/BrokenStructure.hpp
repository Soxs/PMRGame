//
//  BrokenStructure.hpp
//  PMRGame
//
//  Created by Zakary Pacha on 13/02/2016.
//
//

#ifndef BrokenStructure_hpp
#define BrokenStructure_hpp

#include <stdio.h>
#include "Entity.hpp"

class BrokenStructure : public Entity {
public:
    BrokenStructure(int tileGID, cocos2d::Sprite* tileSprite, cocos2d::Vec2 location);
    int getGID();

private:
    int gid;
};

#endif /* BrokenStructure_hpp */

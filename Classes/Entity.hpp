//
//  Entity.hpp
//  PMRGame
//
//  Created by Zakary Pacha on 10/02/2016.
//
//

#ifndef Entity_hpp
#define Entity_hpp

#include <stdio.h>
#include "cocos2d.h"


class Entity {
    
public:
    Entity(cocos2d::Vec2 spawnLocation);
    
    cocos2d::CCSprite* entityImage;
    cocos2d::Vec2 location;
    
    void setSprite(cocos2d::CCSprite* newSprite);
    void setPosition(cocos2d::Vec2 newLocation);
};


#endif /* Entity_hpp */

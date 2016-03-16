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

//must extend Ref for use in Vector
class Entity : public cocos2d::Ref {
    
public:
    Entity(cocos2d::Vec2 spawnLocation);
    
    cocos2d::Sprite* entityImage;
    cocos2d::Vec2 location;
    
    void setSprite(cocos2d::Sprite* newSprite);
    void setPosition(cocos2d::Vec2 newLocation);
};


#endif /* Entity_hpp */

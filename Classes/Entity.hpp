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
#include "PathFinding.hpp"
//must extend Ref for use in Vector


using namespace cocos2d;

class Entity : public cocos2d::Ref {
    
public:
    Entity(cocos2d::Vec2 spawnLocation);
    bool isAlive;
    cocos2d::Sprite* entityImage;
    cocos2d::Vec2 location;
    vector<ASWaypoint*> Path;
    cocos2d::Vec2 targetPos;
    cocos2d::CCPoint tileCoordForPosition(cocos2d::CCPoint position);
    void setSprite(cocos2d::Sprite* newSprite);
    void setPosition(cocos2d::Vec2 newLocation);
    void update(float delta);
    void update(cocos2d::Vec2 targetPos, float delta);
    void walkTo(cocos2d::Vec2 newPos);
    void updatePosition(cocos2d::Vec2 newPos, bool tele);
};


#endif /* Entity_hpp */
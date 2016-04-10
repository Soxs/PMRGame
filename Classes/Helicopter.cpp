//
//  Helicopter.cpp
//  PMRGame
//
//  Created by Zakary Pacha on 10/04/2016.
//
//

#include "Helicopter.hpp"
#include "GameWorld.h"

Helicopter::Helicopter(cocos2d::Vec2 spawnLocation) : Entity(spawnLocation) {
    cocos2d::Sprite* sprite = new cocos2d::Sprite();
    sprite->initWithFile("crowd.png");
    sprite->setPosition(spawnLocation);
    setSprite(sprite);
    GameWorld::instance->addChild(sprite, 0);
}

void Helicopter::update(float delta) {
    
}
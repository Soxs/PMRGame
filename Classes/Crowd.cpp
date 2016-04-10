//
//  Crowd.cpp
//  PMRGame
//
//  Created by Zakary Pacha on 09/04/2016.
//
//

#include "Crowd.hpp"
#include "GameWorld.h"

Crowd::Crowd(cocos2d::Vec2 spawnLocation) : Entity(spawnLocation) {
    cocos2d::Sprite* sprite = new cocos2d::Sprite();
    sprite->initWithFile("crowd.png");
    sprite->setPosition(spawnLocation);
    setSprite(sprite);
    GameWorld::instance->addChild(sprite, 0);
}

/*void Entity::update(float delta) {
    /*
     Update crowd movement.
     
}*/
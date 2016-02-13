//
//  Entity.cpp
//  PMRGame
//
//  Created by Zakary Pacha on 10/02/2016.
//
//

#include "Entity.hpp"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

Entity::Entity(cocos2d::Vec2 spawnLocation) {
    this->location = spawnLocation;
}

void Entity::setSprite(cocos2d::Sprite* newImage) {
    this->entityImage = newImage;
}

void Entity::setPosition(cocos2d::Vec2 newpos) {
    this->location = newpos;
}
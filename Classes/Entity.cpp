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
#include "GameWorld.h"



Entity::Entity(Vec2 spawnLocation) {
    this->location = spawnLocation;
    this->targetPos = Vec2(-1, -1);
    this->isAlive = true;
}


CCPoint Entity::tileCoordForPosition(CCPoint position)
{
    int x = position.x / GameWorld::instance->_tileMap->getTileSize().width;
    int canvasheight = GameWorld::instance->GameWorld::instance->_tileMap->getMapSize().height * GameWorld::instance->_tileMap->getTileSize().height;
    int y = (canvasheight - position.y) / GameWorld::instance->_tileMap->getTileSize().height;
    return ccp(x, y);
}
void Entity::setSprite(cocos2d::Sprite* newImage) {
    this->entityImage = newImage;
}

void Entity::setPosition(cocos2d::Vec2 newpos) {
    this->location = newpos;
}

void Entity::update(float delta) {
    
}



void Entity::update(cocos2d::Vec2 targetPos, float deltaTime) {
    
    
}

void Entity::walkTo(cocos2d::Vec2 newPos) {
    updatePosition(newPos, false);
}

void Entity::updatePosition(cocos2d::Vec2 newPos, bool tele) {
    //set the pos
    location = newPos;
    
    //Get the anchor point for the monster sprite on the y so he stands on the tile.
    int halfheight = entityImage->getTextureRect().size.height / 2;
    
    Vec2 anchoredPosition = Vec2(newPos.x,
                                 newPos.y /*+ halfheight*/);
    
    if (!tele) {
        auto move_action = MoveTo::create(0.5f, anchoredPosition);
        entityImage->runAction(move_action);
    }
    else {
        entityImage->setPosition(anchoredPosition);
        
    }
    
}
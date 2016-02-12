//
//  Player.cpp
//  PMRGame
//
//  Created by Zakary Pacha on 12/02/2016.
//
//

#include "Player.hpp"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

Player::Player(cocos2d::Vec2 spawnLocation) : Entity(spawnLocation) {
    cocos2d::CCSprite* sprite = new cocos2d::CCSprite();
    sprite->initWithFile("Player.png");
    sprite->setPosition(spawnLocation);
    setSprite(sprite);
}
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
#include "GameWorld.h"

USING_NS_CC;

Player::Player(cocos2d::Vec2 spawnLocation) : Entity(spawnLocation) {
    cocos2d::Sprite* sprite = new cocos2d::Sprite();
    sprite->initWithFile("DinoLeft.png");
    sprite->setPosition(spawnLocation);
    setSprite(sprite);
}

void Player::touchEvent(cocos2d::Touch* touch, cocos2d::Event* event) {
    

}
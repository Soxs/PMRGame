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
	setSprite(sprite);

	updatePosition(spawnLocation, true);

    
}

void Player::updatePosition(cocos2d::Vec2 newPos, bool tele) {
	//set the pos
	actualPosition = newPos;

	//Get the anchor point for the monster sprite on the y so he stands on the tile.
	int halfheight = entityImage->getTextureRect().size.height / 3;

	Vec2 anchoredPosition = Vec2(newPos.x,
		newPos.y + halfheight);

	if (!tele) {
		auto move_action = MoveTo::create(0.1f, anchoredPosition);
		entityImage->runAction(move_action);
	} else 
		entityImage->setPosition(anchoredPosition);
}

void Player::walkTo(cocos2d::Vec2 newPos) {
	updatePosition(newPos, false);
}

void Player::touchEvent(cocos2d::Touch* touch, cocos2d::Event* event) {
    

}
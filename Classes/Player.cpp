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

	//Get the anchor point for the monster sprite on the y so he stands on the tile.
	int halfheight = sprite->getTextureRect().size.height / 2;
	int halfwidth = sprite->getTextureRect().size.width / 2;
	int apos = 32 - halfheight;

	Vec2 anchoredPosition = Vec2(sprite->getPosition().x + halfwidth,
									sprite->getPosition().y - apos);

    sprite->setPosition(anchoredPosition);
    setSprite(sprite);
}

void Player::touchEvent(cocos2d::Touch* touch, cocos2d::Event* event) {
    

}
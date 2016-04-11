//
//  ScoreManager.cpp
//  PMRGame
//
//  Created by Zakary Pacha on 17/03/2016.
//
//

#include "ScoreManager.hpp"
#include "GameWorld.h"

ScoreManager::ScoreManager() {
    score = 0;
}

int ScoreManager::getScore() {
    return score;
}

void ScoreManager::addToScore(int toadd) {
    addToScore(toadd, cocos2d::Vec2(150, 150));
}

void ScoreManager::addToScore(int toadd, cocos2d::Vec2 loc) {
    
    GameWorld* gameInstance = GameWorld::instance;
    Label* tempScoreLabel = Label::createWithTTF("+" + std::to_string(toadd), "kenney-rocket.ttf", 16);
    tempScoreLabel->setColor(cocos2d::Color3B::RED);
    tempScoreLabel->enableOutline(Color4B(0,0,0,255),1);
    tempScoreLabel->setPosition(loc);
    gameInstance->addChild(tempScoreLabel, 1);
    Sequence* anim = cocos2d::Sequence::create(cocos2d::MoveTo::create(1.0f, Vec2(loc.x, loc.y + 50)), cocos2d::DelayTime::create(1.0f), cocos2d::MoveTo::create(0.5f, gameInstance->pointlocation), cocos2d::RemoveSelf::create(), NULL);
    tempScoreLabel->runAction(anim);
    score += toadd;
}

void ScoreManager::reset() {
    score = 0;
}

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
    Label* tempScoreLabel = Label::createWithTTF("+" + std::to_string(toadd), "kenney-rocket.ttf", 12);
    tempScoreLabel->setColor(cocos2d::Color3B::RED);
    tempScoreLabel->enableOutline(Color4B(0,0,0,255),1);
    tempScoreLabel->setPosition(loc);
    gameInstance->addChild(tempScoreLabel, 1);
    
    score += toadd;
}

void ScoreManager::reset() {
    score = 0;
}

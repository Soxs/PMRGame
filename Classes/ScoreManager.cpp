//
//  ScoreManager.cpp
//  PMRGame
//
//  Created by Zakary Pacha on 17/03/2016.
//
//

#include "ScoreManager.hpp"

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
    score += toadd;
}

void ScoreManager::reset() {
    score = 0;
}

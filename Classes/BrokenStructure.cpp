//
//  BrokenStructure.cpp
//  PMRGame
//
//  Created by Zakary Pacha on 13/02/2016.
//
//

#include "BrokenStructure.hpp"

BrokenStructure::BrokenStructure(int tileGID, cocos2d::Sprite* tilesprite, cocos2d::Vec2 location) : Entity(location) {
    this->gid = tileGID;
    
    setSprite(tilesprite);
}

int BrokenStructure::getGID() {
    return this->gid;
}
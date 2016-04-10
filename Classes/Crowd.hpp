//
//  Crowd.hpp
//  PMRGame
//
//  Created by Zakary Pacha on 09/04/2016.
//
//

#ifndef Crowd_hpp
#define Crowd_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Entity.hpp"

using namespace cocos2d;

class Crowd : public Entity {
public:
    Crowd(cocos2d::Vec2 spawnLocation);
    
    cocos2d::Vec2 targetLocation;
    
private:
    
};

#endif /* Crowd_hpp */

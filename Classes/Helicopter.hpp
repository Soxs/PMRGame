//
//  Helicopter.hpp
//  PMRGame
//
//  Created by Zakary Pacha on 10/04/2016.
//
//

#ifndef Helicopter_hpp
#define Helicopter_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Entity.hpp"

using namespace cocos2d;

class Helicopter : public Entity {
public:
    Helicopter(cocos2d::Vec2 spawnLocation);
    cocos2d::Vec2 targetLocation;
    
    void update(float delta);
private:
    
};


#endif /* Helicopter_hpp */

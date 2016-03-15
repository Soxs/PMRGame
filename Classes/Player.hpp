//
//  Player.hpp
//  PMRGame
//
//  Created by Zakary Pacha on 12/02/2016.
//
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "Entity.hpp"
#include "cocos2d.h"

class Player : public Entity {
public:
    Player(cocos2d::Vec2 spawnLocation);
    void touchEvent(cocos2d::Touch* touch, cocos2d::Event* event);

	cocos2d::Vec2 actualPosition;
	void updatePosition(cocos2d::Vec2 newPos, bool tele);
	void walkTo(cocos2d::Vec2 newPos);
};

#endif /* Player_hpp */

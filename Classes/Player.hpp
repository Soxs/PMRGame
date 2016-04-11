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

using namespace cocos2d;

class Player : public Entity {
public:
    Player(cocos2d::Vec2 spawnLocation);
    void touchEvent(cocos2d::Touch* touch, cocos2d::Event* event);
    void update(float deltaTime);

	cocos2d::Vec2 actualPosition;
    int currentHealth;
	Entity* targetEnemy;
    bool isDead();
	bool isChasingEnemy;
	void updatePosition(cocos2d::Vec2 newPos, bool tele);
	void walkTo(cocos2d::Vec2 newPos);
    
private:
    MotionStreak* ms;
};

#endif /* Player_hpp */

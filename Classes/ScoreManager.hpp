//
//  ScoreManager.hpp
//  PMRGame
//
//  Created by Zakary Pacha on 17/03/2016.
//
//

#ifndef ScoreManager_hpp
#define ScoreManager_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class ScoreManager {
public:
    ScoreManager();
    int getScore();
    void addToScore(int toadd);
    void addToScore(int toadd, cocos2d::Vec2 loc);
    void reset();
    
private:
    int score;
};

#endif /* ScoreManager_hpp */

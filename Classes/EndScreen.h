#ifndef __END_SCREEN_H__
#define __END_SCREEN_H__

#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "MainScreen.h"
#include "GameScreen.h"
#include "cocostudio/CocoStudio.h"

class EndScreen : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(EndScreen);
	

};

#endif
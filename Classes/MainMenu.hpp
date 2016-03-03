//
//  MainMenu.hpp
//  PMRGame
//
//  Created by Zakary Pacha on 01/03/2016.
//
//

#ifndef MainMenu_hpp
#define MainMenu_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

class MainMenu : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void startButtonClicked(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	
    
    CREATE_FUNC(MainMenu);
    
private:
    cocos2d::ui::Button* startGame;
	cocos2d::ui::Button* exitGame;
	cocos2d::ui::Button* creditbutton;
    
};

#endif /* MainMenu_hpp */

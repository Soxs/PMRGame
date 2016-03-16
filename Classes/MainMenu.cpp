//
//  MainMenu.cpp
//  PMRGame
//
//  Created by Zakary Pacha on 01/03/2016.
//
//

#include "MainMenu.hpp"
#include "GameWorld.h"
#include "CreditScreen.hpp"

USING_NS_CC;
using namespace cocostudio::timeline;

Scene* MainMenu::createScene()
{
    auto scene = Scene::create();
    auto layer = MainMenu::create();
    scene->addChild(layer);
    return scene;
}

bool MainMenu::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    //Gets the node we created in cocos2d-x.
    auto rootNode = CSLoader::createNode("MainMenu.csb");
    //Adds the node to the current scene.
    addChild(rootNode);
    
    //Gets the startWidget.
    startGame = static_cast<ui::Button*>(rootNode->getChildByName("playWidget"));
    //Sets the callback for the button click.
    startGame->addTouchEventListener(CC_CALLBACK_2(MainMenu::startButtonClicked, this));

	//Gets the exitWidget.
	exitGame = static_cast<ui::Button*>(rootNode->getChildByName("exitWidget"));
	//Sets the callback for the button click.
	exitGame->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType pressed)
	{
		if (pressed == ui::Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->end();
		}
	});

	//Gets the creditWidget.
	creditbutton = static_cast<ui::Button*>(rootNode->getChildByName("creditWidget"));
	//Sets the callback for the button click.
	creditbutton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType pressed)
	{
		if (pressed == ui::Widget::TouchEventType::ENDED)
		{
			auto scene = CreditScreen::createScene();
			Director::getInstance()->replaceScene(scene);
		}
	});
	
	
    return true;
}

void MainMenu::startButtonClicked(Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
    {
        //The start button was clicked.
        Director::getInstance()->replaceScene(GameWorld::createScene());
        
    }


}
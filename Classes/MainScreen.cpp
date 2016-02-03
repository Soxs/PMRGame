#include "MainScreen.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "EndGame.h"
#include <cstdlib>
#include <ctime>


USING_NS_CC;

using namespace cocostudio::timeline;

Scene* MainScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = MainScreen::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScreen::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("MainScreen.csb");
	
	addChild(rootNode);

	auto StartButton = rootNode->getChildByName<cocos2d::ui::Button*>("StartButton");
	auto ExitButton = rootNode->getChildByName<cocos2d::ui::Button*>("ExitButton");
	auto CreditButton = rootNode->getChildByName<cocos2d::ui::Button*>("CreditButton");
	// need to make the Game Screen - scene
	StartButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType Event)
	{
		if (Event == ui::Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->replaceScene(GameScreen::createScene());
		}
	});
	// need to make the credit screen - scene
	CreditButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType Event)
	{
		if (Event == ui::Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->replaceScene(CreditScreen::createScene());
		}
	});
	// end the application
	ExitButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType Event)
	{
		if (Event == ui::Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->end();
		}
	});

 

    return true;
}

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "CreditScreen.hpp"
#include <cstdlib>
#include <ctime>


USING_NS_CC;

using namespace cocostudio::timeline;

Scene* CreditScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = CreditScreen::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CreditScreen::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("CreditScreen.csb");
	
	addChild(rootNode);

	auto StartButton = static_cast<ui::Button*>(rootNode->getChildByName("MenuButton"));
	
	// need to make the Game Screen - scene
	StartButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType Event)
	{
		if (Event == ui::Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->replaceScene(CreditScreen::createScene());
		}
	});
    return true;
}

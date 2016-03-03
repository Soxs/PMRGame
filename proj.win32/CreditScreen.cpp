#include "CreditScreen.hpp"
#include "GameWorld.h"
#include "MainMenu.hpp"

USING_NS_CC;
using namespace cocostudio::timeline;

Scene* CreditScreen::createScene()
{
	auto scene = Scene::create();
	auto layer = CreditScreen::create();
	scene->addChild(layer);
	return scene;
}

bool CreditScreen::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//Gets the node we created in cocos2d-x.
	auto rootNode = CSLoader::createNode("CreditScreen.csb");
	//Adds the node to the current scene.
	addChild(rootNode);

	//Gets the MenuWidget.
	MenuButton = static_cast<ui::Button*>(rootNode->getChildByName("MenuWidget"));
	//Sets the callback for the button click.
	MenuButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType pressed)
	{
		if (pressed == ui::Widget::TouchEventType::ENDED)
		{
			auto scene = MainMenu::createScene();
			Director::getInstance()->replaceScene(scene);
		}
	});

	//Gets the startWidget.
	StartButton = static_cast<ui::Button*>(rootNode->getChildByName("StartWidget"));
	//Sets the callback for the button click.
	StartButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType pressed)
	{
		if (pressed == ui::Widget::TouchEventType::ENDED)
		{
			auto scene = GameWorld::createScene();
			Director::getInstance()->replaceScene(scene);
		}
	});

	

	return true;
}
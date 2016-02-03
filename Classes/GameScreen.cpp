#include "MainScreen.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameScreen.h"


USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GameScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = EndGame::create();
	

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto rootNode = CSLoader::createNode("GameScreen.csb");

    addChild(rootNode);


	//implement the varying buttons for the game that are used in cocos eg - display for cash, score, lives, time.
	//or buttons for the game controlls and general movement within the game 
	auto DisplayCash = rootNode->getChildByName<cocos2d::ui::Text*>("DisplayCash");
	auto DisplayTime = rootNode->getChildByName<cocos2d::ui::Text*>("DisplayTime");
	auto PauseButton = rootNode->getChildByName<cocos2d::ui::Button*>("PauseButton");
	auto Lane1 = rootNode->getChildByName<cocos2d::ui::Button*>("Lane1");
	auto Lane2 = rootNode->getChildByName<cocos2d::ui::Button*>("Lane2");
	auto Lane3 = rootNode->getChildByName<cocos2d::ui::Button*>("Lane3");
	auto Lane4 = rootNode->getChildByName<cocos2d::ui::Button*>("Lane4");
	auto Lane5 = rootNode->getChildByName<cocos2d::ui::Button*>("Lane5");
	auto Monster1 = rootNode->getChildByName<cocos2d::ui::Button*>("Monster1");
	auto Monster2 = rootNode->getChildByName<cocos2d::ui::Button*>("Monster2");
	auto Monster3 = rootNode->getChildByName<cocos2d::ui::Button*>("Monster3");
	auto Monster4 = rootNode->getChildByName<cocos2d::ui::Button*>("Monster4");
	
	//implement a pause screen holds the game state not allowing any interaction until unpaused possibly go to 
	//different scene but would need to keep this scene for a return opition
	PauseButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType pressed)
	{
		if (pressed == ui::Widget::TouchEventType::ENDED)
		{
			auto scene = M::createScene();
			Director::getInstance()->replaceScene(scene);
		}
	});

	Lane1->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType pressed)
	{
		if (pressed == ui::Widget::TouchEventType::ENDED)
		{
			
		}
	});

	Lane2->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType pressed)
	{
		if (pressed == ui::Widget::TouchEventType::ENDED)
		{
		
		}
	});

	Lane3->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType pressed)
	{
		if (pressed == ui::Widget::TouchEventType::ENDED)
		{
			
		}
	});

	Lane4->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType pressed)
	{
		if (pressed == ui::Widget::TouchEventType::ENDED)
		{
			
		}
	});

	Lane5->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType pressed)
	{
		if (pressed == ui::Widget::TouchEventType::ENDED)
		{

		}
	});


	DisplayCash->setString(StringUtils::format("%s %d", "Cash: ", Cash));	
	DisplayTime->setString(StringUtils::format("%s %d", "Time Remaining: ", Time));

	
    return true;
}

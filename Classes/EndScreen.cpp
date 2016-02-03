#include "MainScreen.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "EndScreen.h"


USING_NS_CC;

using namespace cocostudio::timeline;

Scene* EndScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = EndScreen::create();
	

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool EndScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto rootNode = CSLoader::createNode("EndScreen.csb");

    addChild(rootNode);



	auto LosingDisplay = rootNode->getChildByName<cocos2d::ui::Text*>("LosingDisplay");
	auto MenuButton = rootNode->getChildByName<cocos2d::ui::Button*>("MenuButton");
	
	MenuButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType pressed)
	{
		if (pressed == ui::Widget::TouchEventType::ENDED)
		{
			auto scene = MainScreen::createScene();
			Director::getInstance()->replaceScene(scene);
		}
	});
	// set up whats needed in the end screen score, winner etc
	LosingDisplay->setString(StringUtils::format("%s %d", "Score:", Losingdisplay));
    return true;
}

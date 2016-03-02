//
//  MainMenu.cpp
//  PMRGame
//
//  Created by Zakary Pacha on 01/03/2016.
//
//

#include "MainMenu.hpp"
#include "GameWorld.h"

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
    
    
    
    return true;
}
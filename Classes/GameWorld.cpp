#include "GameWorld.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <fstream>
#include <string>
#include <iostream>

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace std;

GameWorld* GameWorld::instance = nullptr;
Scene* GameWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    instance = this;
    
    
    scoreManager = new ScoreManager();
    npcManager = new NpcManager();
    structureManager = new StructureManager();
    touchLocation = ccp(-1, -1);
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);
    
    _tileMap = TMXTiledMap::create("greenmap.tmx");
    
    pathFinding = new PathFinding();

    _background = _tileMap->layerNamed("Background");

	TMXObjectGroup *objectGroup = _tileMap->objectGroupNamed("Objects");

	if (objectGroup == NULL){
		return false;
	}

	auto spawnPoints = objectGroup->objectNamed("spawnPoint");
	int x = spawnPoints.at("x").asInt();
	int y = spawnPoints.at("y").asInt();

	
    this->addChild(_tileMap);

	player = new Player(ccp(x, y));
    
    _meta = _tileMap->layerNamed("Meta");
    _meta->setVisible(false);
    
    
    CCPoint cp1 = tileCoordForPosition(ccp(798, 444));
    CCPoint cp2 = tileCoordToPosition(cp1);
    //CCLOG("x: %f, y: %f", cp2.x, cp2.y);
    
    
    
    
    this->addChild(player->entityImage, 2);
    this->setViewPointCenter(player->entityImage->getPosition());
    
    heartsprite = new cocos2d::Sprite();
    heartsprite->initWithFile("heart.png");
    heartsprite->setScale(1.5f, 1.5f);
    heartsprite->setPosition(this->convertToNodeSpace(CCDirector::sharedDirector()->convertToGL(ccp(30, 60))));
    this->addChild(heartsprite, 3);
    
    healthLabel = Label::createWithTTF(std::to_string(player->currentHealth), "kenney-rocket.ttf", 32);
    healthLabel->setColor(cocos2d::Color3B::RED);
    healthLabel->enableOutline(Color4B(0,0,0,255),3);
    healthLabel->setPosition(this->convertToNodeSpace(CCDirector::sharedDirector()->convertToGL(ccp(114, 60))));
    this->addChild(healthLabel, 3);
    
    scoreTextLabel = Label::createWithTTF("Score:", "kenney-rocket.ttf", 24);
    scoreTextLabel->enableOutline(Color4B(0,0,0,255),3);
    scoreTextLabel->setPosition(this->convertToNodeSpace(CCDirector::sharedDirector()->convertToGL(ccp(100, 100))));
    this->addChild(scoreTextLabel, 3);
    
    scoreLabel = Label::createWithTTF(std::to_string(scoreManager->getScore()), "kenney-rocket.ttf", 32);
    scoreLabel->enableOutline(Color4B(0,0,0,255),4);
    scoreLabel->setPosition(this->convertToNodeSpace(CCDirector::sharedDirector()->convertToGL(ccp(110, 130))));
    this->addChild(scoreLabel, 3);
    
    
    keyboardListener();
    this->scheduleUpdate();
    this->schedule(schedule_selector(GameWorld::cameraUpdater), 1.0f);
    return true;
}

void GameWorld::cameraUpdater(float delta)
{
    this->setViewPointCenter(player->entityImage->getPosition());
}

void GameWorld::update(float delta) {

    scoreTextLabel->setPosition(this->convertToNodeSpace(CCDirector::sharedDirector()->convertToGL(ccp(100, 100))));
    
    scoreLabel->setString(std::to_string(scoreManager->getScore()));
    scoreLabel->setPosition(this->convertToNodeSpace(CCDirector::sharedDirector()->convertToGL(ccp(110, 130))));
    
    heartsprite->setPosition(this->convertToNodeSpace(CCDirector::sharedDirector()->convertToGL(ccp(30, 60))));
    
    healthLabel->setString(std::to_string(player->currentHealth));
	healthLabel->setPosition(this->convertToNodeSpace(CCDirector::sharedDirector()->convertToGL(ccp(114, 60))));
    
    //Update the player.
    player->update(delta);
    
    //Update all the npcs.
    for (Entity* e : *npcManager->getNpcs()) {
        if (IsType<Crowd>(e)) {
            Crowd* c = static_cast<Crowd*>(e);
            c->update(delta);
        } else if (IsType<Helicopter>(e)) {
            Helicopter* h = static_cast<Helicopter*>(e);
            h->update(delta);
        } else
            e->update(delta);
    }
    
    //Update all the broken buildings.
    for (BrokenStructure* b : *structureManager->getStructures()) {
        b->update(delta);
    }
    
}


void GameWorld::setViewPointCenter(CCPoint position) {
    //Window size.
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
	//Get the actual position that correlates with the tilemap.
    int x = MAX(position.x, winSize.width/2);
    int y = MAX(position.y, winSize.height/2);
    x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
    y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height/2);
    CCPoint actualPosition = ccp(x, y);
    
	//Get the vector that moves the camera to the center.
    CCPoint centerOfView = ccp(winSize.width/2, winSize.height/2);
    centerPoint = ccpSub(centerOfView, actualPosition);

	//More dramatic camera movement.
    auto move_action = MoveTo::create(1.0f, centerPoint);
    this->runAction(move_action);

	//Instantanious camera movement.
    //this->setPosition(centerPoint);
}

bool GameWorld::onTouchBegan(Touch* touch, Event* event)
{
    touchEvent(touch, event);
    return true;
}

void GameWorld::onDragEvent(Touch* touch, Event* event)
{
    touchEvent(touch, event);
}

void GameWorld::touchEvent(Touch* touch, Event* event)
{
    CCPoint touchl = touch->getLocationInView();
    touchl = CCDirector::sharedDirector()->convertToGL(touchl);
    
    touchLocation = this->convertToNodeSpace(touchl);
    vector<ASWaypoint*> path = pathFinding->searchPath(tileCoordForPosition(player->actualPosition), tileCoordForPosition(touchLocation));
    chosenPath = path;
}


bool GameWorld::checkCollision(int tileGID) {
    if (tileGID > 0) {
        ValueMap tileValues = _tileMap->getPropertiesForGID(tileGID).asValueMap();
        CCString* testme = new CCString();
        *testme = tileValues.at("Collidable").asString();
        if ((testme->length()) > 0 &&
            (testme->compare("True") == 0)) {
            return true;
        }
    }
    return false;
}

void GameWorld::resetWorld()
{
    //remove saved locations of destroyed buildings.
    structureManager->resetManager();
}

void GameWorld::keyboardListener()
{
    auto touchListener = EventListenerTouchOneByOne::create();
    
    //Set callbacks for our touch functions.
    touchListener->onTouchBegan = CC_CALLBACK_2(GameWorld::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameWorld::onDragEvent, this);
    
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

CCPoint GameWorld::tileCoordForPosition(CCPoint position)
{
    int x = position.x / _tileMap->getTileSize().width;
    int canvasheight = _tileMap->getMapSize().height * _tileMap->getTileSize().height;
    int y = (canvasheight - position.y) / _tileMap->getTileSize().height;
    return ccp(x, y);
}

CCPoint GameWorld::tileCoordToPosition(CCPoint tileCoord)
{
    int x = tileCoord.x * _tileMap->getTileSize().width;
    int canvasheight = _tileMap->getMapSize().height * _tileMap->getTileSize().height;
    int difference = tileCoord.y * _tileMap->getTileSize().height;
    int y = canvasheight - difference;
    //int y = ((tileCoord.y * _tileMap->getTileSize().height)-(_tileMap->getMapSize().height * _tileMap->getTileSize().height)) *-1;
    
    return this->convertToNodeSpace(CCDirector::sharedDirector()->convertToGL(ccp(x, y))) ;
}
#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    isMoving = false;
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);
    
    _tileMap = new CCTMXTiledMap();
    _tileMap->initWithTMXFile("gamemap.tmx");
    _background = _tileMap->layerNamed("Background");
    
    this->addChild(_tileMap);
    
    _meta = _tileMap->layerNamed("Meta");
    _meta->setVisible(false);
    
    CCTMXObjectGroup *objectGroup = _tileMap->objectGroupNamed("Objects");
    
    if(objectGroup == NULL){
        CCLog("tile map has no objects object layer");
        return false;
    }
    
    auto spawnPoints = objectGroup->objectNamed("spawnPoint");
    int x = spawnPoints.at("x").asInt();
    int y = spawnPoints.at("y").asInt();
    
    _player = new CCSprite();
    _player->initWithFile("Player.png");
    _player->setPosition(ccp(x,y));
    
    this->addChild(_player);
    this->setViewPointCenter(_player->getPosition());
    keyboardListener();
    return true;
}

void HelloWorld::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    Vec2 loc = event->getCurrentTarget()->getPosition();
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case EventKeyboard::KeyCode::KEY_A:
            //event->getCurrentTarget()->setPosition(loc.x - 10, loc.y);
            _player->setPositionY(_player->getPositionY() + 4);
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case EventKeyboard::KeyCode::KEY_D:
            //event->getCurrentTarget()->setPosition(loc.x + 10, loc.y);
            _player->setPositionY(_player->getPositionY() - 4);
            break;
    }
}

void HelloWorld::setViewPointCenter(CCPoint position) {
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    int x = MAX(position.x, winSize.width/2);
    int y = MAX(position.y, winSize.height/2);
    x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
    y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height/2);
    CCPoint actualPosition = ccp(x, y);
    
    CCPoint centerOfView = ccp(winSize.width/2, winSize.height/2);
    centerPoint = ccpSub(centerOfView, actualPosition);
    this->setPosition(centerPoint);
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    
    
    
    CCPoint touchLocation = touch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    touchLocation = this->convertToNodeSpace(touchLocation);
    
    CCPoint playerPos = _player->getPosition();
    CCPoint diff = ccpSub(touchLocation, playerPos);
    
    if ( abs(diff.x) > abs(diff.y) ) {
        if (diff.x > 0) {
            playerPos.x += _tileMap->getTileSize().width;
        } else {
            playerPos.x -= _tileMap->getTileSize().width;
        }
    } else {
        if (diff.y > 0) {
            playerPos.y += _tileMap->getTileSize().height;
        } else {
            playerPos.y -= _tileMap->getTileSize().height;
          
        }
    }
    
    // safety check on the bounds of the map
    if (playerPos.x <= (_tileMap->getMapSize().width * _tileMap->getTileSize().width) &&
        playerPos.y <= (_tileMap->getMapSize().height * _tileMap->getTileSize().height) &&
        playerPos.y >= 0 &&
        playerPos.x >= 0 )
    {
        
        CCPoint tileCoord = this->tileCoordForPosition(touchLocation);
        Vec2 place = Vec2(tileCoord.x, tileCoord.y);
        bool collisionbool = false;
        int tileGid = _meta->getTileGIDAt(place);

        if (tileGid) {
            auto properties = _tileMap->getPropertiesForGID(tileGid).asValueMap();
            if (!properties.empty())  {
                CCString *collision = new CCString();
                 *collision = properties.at("Collidable").asString();
                if (collision && (collision->compare("True") == 0)) {
                    collisionbool = true;
                }
            }
        }
        if (!collisionbool && !isMoving) {
            isMoving = true;
            auto move_action = MoveTo::create(1.f, playerPos);
            _player->runAction(move_action);
            isMoving = false;
        }
        
        
       
         //_player->setPosition(playerPos);
      //  this->setPlayerPosition(playerPos);
    }
    
    this->setViewPointCenter(_player->getPosition());
    
    
    
    
    
    return true;
}

void HelloWorld::keyboardListener()
{
    auto eventListener = EventListenerKeyboard::create();
    eventListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::keyPressed, this);
    
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, _player);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    
    //Set callbacks for our touch functions.
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

CCPoint HelloWorld::tileCoordForPosition(CCPoint position)
{
    int x = position.x / _tileMap->getTileSize().width;
    int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
    return ccp(x, y);
}

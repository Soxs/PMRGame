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
    
    structureManager = new StructureManager();
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);
    
    _tileMap = new CCTMXTiledMap();
    _tileMap->initWithTMXFile("greenmap.tmx");
    _background = _tileMap->layerNamed("Background");
    
    this->addChild(_tileMap);
    
    _meta = _tileMap->layerNamed("Meta");
    _meta->setVisible(false);
    
    CCTMXObjectGroup *objectGroup = _tileMap->objectGroupNamed("Objects");
    
    if(objectGroup == NULL){
        return false;
    }
    
    auto spawnPoints = objectGroup->objectNamed("spawnPoint");
    int x = spawnPoints.at("x").asInt();
    int y = spawnPoints.at("y").asInt();
    
    player = new Player(ccp(x,y));
    
    this->addChild(player->entityImage);
    this->setViewPointCenter(player->entityImage->getPosition());
    keyboardListener();
    return true;
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
    auto move_action = MoveTo::create(0.5f, centerPoint);
    this->runAction(move_action);
    //this->setPosition(centerPoint);
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    
    CCPoint touchLocation = touch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    touchLocation = this->convertToNodeSpace(touchLocation);
    
    CCPoint playerPos = player->entityImage->getPosition();
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
        CCPoint nextTileCoord = this->tileCoordForPosition(playerPos);
        
        Vec2 place = Vec2(tileCoord.x, tileCoord.y);
        Vec2 nextPlace = Vec2(nextTileCoord.x, nextTileCoord.y);
        
        bool collisionbool = false;
        
        //check collision on tile next to character
        if (checkCollision(_meta->getTileGIDAt(nextPlace))) {
            
            int buildingSpriteGID = _background->getTileGIDAt(nextPlace);
            if (!structureManager->containsStructure(buildingSpriteGID, nextPlace)) {
                ValueMap tileValues = _tileMap->getPropertiesForGID(buildingSpriteGID).asValueMap();
                CCString* testme = new CCString();
                *testme = tileValues.at("type").asString();
                if (testme->length() > 0) {
                    Sprite *tile = _background->getTileAt(nextPlace);
                    
                    if (testme->compare("top-left") == 0) {
                        
                        //sets rectangle inside sprite sheet.
                        cocos2d::Rect originalTileSprite = tile->getTextureRect();
                        float x = originalTileSprite.origin.x + 64; //bottom left point x (we add 64 because the broken equivalent starts 64 pixels to the right)
                        float y = originalTileSprite.origin.y; //bottom left point y
                        float width = originalTileSprite.size.width;
                        float height = originalTileSprite.size.height;
                        
                        cocos2d::Rect brokenEquivalent = *new cocos2d::Rect(x, y, width, height);
                        tile->setTextureRect(brokenEquivalent);
                        structureManager->addStructure(new BrokenStructure(buildingSpriteGID, tile, nextPlace));
                        
                    }
                    
                    if (testme->compare("top-right") == 0) {
                        //sets rectangle inside sprite sheet.
                        cocos2d::Rect originalTileSprite = tile->getTextureRect();
                        float x = originalTileSprite.origin.x + 64; //bottom left point x (we add 64 because the broken equivalent starts 64 pixels to the right)
                        float y = originalTileSprite.origin.y; //bottom left point y
                        float width = originalTileSprite.size.width;
                        float height = originalTileSprite.size.height;
                        
                        cocos2d::Rect brokenEquivalent = *new cocos2d::Rect(x, y, width, height);
                        tile->setTextureRect(brokenEquivalent);
                        structureManager->addStructure(new BrokenStructure(buildingSpriteGID, tile, nextPlace));
                    }
                    
                    if (testme->compare("bottom-left") == 0) {
                        //sets rectangle inside sprite sheet.
                        cocos2d::Rect originalTileSprite = tile->getTextureRect();
                        float x = originalTileSprite.origin.x + 64; //bottom left point x (we add 64 because the broken equivalent starts 64 pixels to the right)
                        float y = originalTileSprite.origin.y; //bottom left point y
                        float width = originalTileSprite.size.width;
                        float height = originalTileSprite.size.height;
                        
                        cocos2d::Rect brokenEquivalent = *new cocos2d::Rect(x, y, width, height);
                        tile->setTextureRect(brokenEquivalent);
                        structureManager->addStructure(new BrokenStructure(buildingSpriteGID, tile, nextPlace));
                    }
                    
                    if (testme->compare("bottom-right") == 0) {
                        //sets rectangle inside sprite sheet.
                        cocos2d::Rect originalTileSprite = tile->getTextureRect();
                        float x = originalTileSprite.origin.x + 64; //bottom left point x (we add 64 because the broken equivalent starts 64 pixels to the right)
                        float y = originalTileSprite.origin.y; //bottom left point y
                        float width = originalTileSprite.size.width;
                        float height = originalTileSprite.size.height;
                        
                        cocos2d::Rect brokenEquivalent = *new cocos2d::Rect(x, y, width, height);
                        tile->setTextureRect(brokenEquivalent);
                        structureManager->addStructure(new BrokenStructure(buildingSpriteGID, tile, nextPlace));
                    }
                }
            }
            collisionbool = true;
            
        //checks collsion on tile that players clicks.
        } else if (checkCollision(_meta->getTileGIDAt(place))) {
            collisionbool = true;
        }
        
        if (!collisionbool) {
            auto move_action = MoveTo::create(0.1f, playerPos);
            player->entityImage->runAction(move_action);
        }
        
        //ValueMap properertiesfornexttile = _tileMap->getPropertiesForGID(nextTileGID).asValueMap();
        
        /*if (!properertiesfornexttile.empty()) {
            CCString *collision = new CCString();
            *collision = properertiesfornexttile.at("Collidable").asString();
            if (collision && (collision->compare("True") == 0))
                collisionbool = true;
        }
        
        if (tileGid && nextTileGID) {
            auto properties = _tileMap->getPropertiesForGID(tileGid).asValueMap();
            auto propertiesNextTile = _tileMap->getPropertiesForGID(nextTileGID).asValueMap();
            if (!properties.empty() &&
                !propertiesNextTile.empty())  {
                
                CCString *collision = new CCString();
                CCString *collisionAtNextTile = new CCString();
                
                *collision = properties.at("Collidable").asString();
                *collisionAtNextTile = propertiesNextTile.at("Collidable").asString();
                if ((collisionAtNextTile && (collisionAtNextTile->compare("True") == 0)) ||
                    (collision && (collision->compare("True") == 0))) {
                    collisionbool = true;
                }
            }
        }*/
        
        
        
       
         //_player->setPosition(playerPos);
      //  this->setPlayerPosition(playerPos);
    }
    
    this->setViewPointCenter(player->entityImage->getPosition());
    
    
    return true;
}

bool HelloWorld::checkCollision(int tileGID) {
    if (!tileGID)
        return false;
    if (tileGID > 0)
        return true;
    return false;
}

void HelloWorld::keyboardListener()
{
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

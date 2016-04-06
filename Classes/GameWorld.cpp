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
    CCLOG("x: %f, y: %f", cp2.x, cp2.y);
    
    
    
    
    this->addChild(player->entityImage);
    this->setViewPointCenter(player->entityImage->getPosition());
    
    
    scoreTextLabel = Label::createWithTTF("Score:", "kenney-rocket.ttf", 24);
    scoreTextLabel->enableOutline(Color4B(0,0,0,255),3);
    scoreTextLabel->setPosition(100, 100);
    this->addChild(scoreTextLabel);
    
    scoreLabel = Label::createWithTTF(std::to_string(scoreManager->getScore()), "kenney-rocket.ttf", 32);
    scoreLabel->enableOutline(Color4B(0,0,0,255),4);
    scoreLabel->setPosition(110, 130);
    this->addChild(scoreLabel, 0);
    
    
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

    
    CCPoint pos = ccp(100,100);
    Vec2 postohud = CCDirector::sharedDirector()->convertToGL(pos);
    postohud = this->convertToNodeSpace(postohud);
    scoreTextLabel->setPosition(postohud);
    
    pos = ccp(110,130);
    postohud = CCDirector::sharedDirector()->convertToGL(pos);
    postohud = this->convertToNodeSpace(postohud);
    scoreLabel->setString(std::to_string(scoreManager->getScore()));
    scoreLabel->setPosition(postohud);
    
	//return if the player is already in a moving animation.
	if (player->entityImage->getNumberOfRunningActions() > 0)
		return;

    //return if no touch location is registered.
    if (touchLocation.x == -1 &&
        touchLocation.y == -1)
        return;
    
    if (chosenPath.size() == 0)
        return;
    
    //return if the distance to the location is less than a tile.
    if (tileCoordForPosition(touchLocation).distance(tileCoordForPosition(player->actualPosition)) == 0)
        return;
    
    ASWaypoint* nextSpot = chosenPath[0];
    Vec2 difference = tileCoordForPosition(player->actualPosition) - nextSpot->coord;
    
    Vec2 realSpot = Vec2(player->actualPosition.x - (difference.x * _tileMap->getTileSize().width),
                         player->actualPosition.y + (difference.y * _tileMap->getTileSize().height));
    
	//Player position.
    CCPoint playerPos = player->actualPosition;
    CCLOG("Player Coord [x: %f, y: %f]", tileCoordForPosition(player->actualPosition).x,tileCoordForPosition(player->actualPosition).y);
    CCLOG("Next Coord [x: %f, y: %f]", nextSpot->coord.x, nextSpot->coord.y);
    
    CCLOG("Player Position [x: %f, y: %f]", player->actualPosition.x, player->actualPosition.y);
    CCLOG("Next Position [x: %f, y: %f]", realSpot.x, realSpot.y);
	//Difference between the touch location and the players location.
    CCPoint diff = ccpSub(realSpot, playerPos);
    
	//Calculate if we're going left, right, down, or up, and get the new position we'll be moving to.
    playerPos = realSpot;
    /*if ( abs(diff.x) > abs(diff.y) ) {
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
    }*/
    
    
    // safety check on the bounds of the map
    if (playerPos.x <= (_tileMap->getMapSize().width * _tileMap->getTileSize().width) &&
        playerPos.y <= (_tileMap->getMapSize().height * _tileMap->getTileSize().height) &&
        playerPos.y >= 0 &&
        playerPos.x >= 0 )
    {
		//the tile where the player touches.
        CCPoint tileCoord = nextSpot->coord;

		//the tile immediately next to the player.
        CCPoint nextTileCoord = this->tileCoordForPosition(playerPos); 
        
        Vec2 place = Vec2(tileCoord.x, tileCoord.y);
        Vec2 nextPlace = Vec2(nextTileCoord.x, nextTileCoord.y);
        
        bool collisionbool = false;
        
        //check collision on tile next to character
        if (checkCollision(_meta->getTileGIDAt(nextPlace))) {

            //id of the tile type at the location.
            int buildingSpriteGID = _background->getTileGIDAt(nextPlace);

			//Check if we've already destroyed this building to avoid adding more to the x value in the sprite rectangle.
            if (!structureManager->containsStructure(buildingSpriteGID, nextPlace)) {
                ValueMap tileValues = _tileMap->getPropertiesForGID(buildingSpriteGID).asValueMap();
                CCString* testme = new CCString();
                *testme = tileValues.at("type").asString();
                if (testme->length() > 0) {
                    Sprite *tile = _background->getTileAt(nextPlace);
                    
                    cocos2d::Rect originalTileSprite = tile->getTextureRect();
                    /*
                     On the tile map sheet, the broken versions of the buildings are positioned 64 pixels to the right.
                     So in order to set the texture of the sprite to the broken version we need to create the rectangle we're setting it to.
                     */
                    
                    float x = originalTileSprite.origin.x + 64; //bottom left point x (we add 64 because the broken equivalent starts 64 pixels to the right)
                    float y = originalTileSprite.origin.y; //doesnt need to change, the y is the same.
                    float width = originalTileSprite.size.width; //probs a good idea to keep it the same size :)
                    float height = originalTileSprite.size.height; //ditto the line above.
                    
                    cocos2d::Rect brokenEquivalent = *new cocos2d::Rect(x, y, width, height); //Creates the new rectangle where the broken equivelant of the same building is.
                    tile->setTextureRect(brokenEquivalent);//Sets the new rectangle to the tile map sheet.
                    structureManager->addStructure(new BrokenStructure(buildingSpriteGID, tile, nextPlace)); //Adds the building attacked to the structure manaager, so we remember which buildings we've already destroyed.
                    
                    scoreManager->addToScore(50); //add to score example...
                    
                }
                //collisionbool = true; // walks over buildings
            }
            collisionbool = true; // cant walk over buildings
        }
        if (chosenPath.size() == 1) {
            chosenPath.clear();
        } else {
            vector<ASWaypoint*> newPath;
            for (int i = 1; i < chosenPath.size(); i++) {
                newPath.push_back(chosenPath[i]);
            }
            chosenPath = newPath;
        }
        
        if (!collisionbool) {
			player->walkTo(playerPos);
            //player->entityImage->setPosition(playerPos);
        }
		//this->setViewPointCenter(player->entityImage->getPosition());

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
    CCPoint touchl = touch->getLocationInView();
    touchl = CCDirector::sharedDirector()->convertToGL(touchl);
    
    touchLocation = this->convertToNodeSpace(touchl);
    vector<ASWaypoint*> path = pathFinding->searchPath(tileCoordForPosition(player->actualPosition), tileCoordForPosition(touchLocation));
    chosenPath = path;
    return true;
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
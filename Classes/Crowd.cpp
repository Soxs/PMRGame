//
//  Crowd.cpp
//  PMRGame
//
//  Created by Zakary Pacha on 09/04/2016.
//
//

#include "Crowd.hpp"
#include "GameWorld.h"


Crowd::Crowd(cocos2d::Vec2 spawnLocation) : Entity(spawnLocation) {
    cocos2d::Sprite* sprite = new cocos2d::Sprite();
    sprite->initWithFile("crowd.png");
    sprite->setPosition(spawnLocation);
    setSprite(sprite);
    
    //PathFinding* p = GameWorld::instance->pathFinding;
    int w = GameWorld::instance->_tileMap->getMapSize().width;
    int h = GameWorld::instance->_tileMap->getMapSize().height;
    //	targetPos = Vec2(32 * (rand() % w + 1), 32 * (rand() % h + 1));
    targetPos = Vec2(200, 200);
    //this->Path = p->searchPath(tileCoordForPosition(spawnLocation), tileCoordForPosition(targetPos));
    //this->walkTo(Vec2(32 * 2, 32 * 10));
    GameWorld::instance->addChild(sprite, 0);
}

void Crowd::update(float delta) {
    
    
    //return if the player is already in a moving animation.
    if (entityImage->getNumberOfRunningActions() > 0)
        return;
    
    if (GameWorld::instance->tileCoordForPosition(location).distance(GameWorld::instance->tileCoordForPosition(GameWorld::instance->player->actualPosition) ) <= 1)
    {
        isAlive = false;
        
        this->entityImage->setColor(cocos2d::Color3B::RED);
        Sequence* anim = cocos2d::Sequence::create( cocos2d::DelayTime::create(5.0f),cocos2d::FadeOut::create(2.0f), cocos2d::RemoveSelf::create(), NULL);
        this->entityImage->runAction(anim);
        
    }
    if (!isAlive){
        //todo: add health to monster
        GameWorld::instance->npcManager->removeNpc(this);
        GameWorld::instance->scoreManager->addToScore(20, this->location + Vec2(0,10));
    }
    
    
    
    //return if no touch location is registered.
    //	if (targetPos == nullptr)
    //	return;
    
    if (this->Path.size() == 0 &&
        GameWorld::instance->tileCoordForPosition(location).distance(GameWorld::instance->tileCoordForPosition(targetPos)) == 0)
        return;
    
    if (this->Path.size() == 0)
    {
        {
            int w = GameWorld::instance->_tileMap->getMapSize().width;
            int h = GameWorld::instance->_tileMap->getMapSize().height;
            targetPos = Vec2(32 * (rand() % w + 1), 32 * (rand() % h + 1));
            PathFinding* p = new PathFinding();
            this->Path = p->searchPath(tileCoordForPosition(location), tileCoordForPosition(targetPos));
            
        }
    }
    //return if the distance to the location is less than a tile.
    if (GameWorld::instance->tileCoordForPosition(targetPos).distance(GameWorld::instance->tileCoordForPosition(location)) == 0)
        return;
    
    Vec2 difference = GameWorld::instance->tileCoordForPosition(location) - GameWorld::instance->tileCoordForPosition(targetPos);
    
    ASWaypoint* nextSpot;
    if (this->Path.size() > 0) {
        nextSpot = this->Path[0];
        difference = GameWorld::instance->tileCoordForPosition(location) - nextSpot->coord;
    }
    
    Vec2 realSpot = Vec2(location.x - (difference.x * GameWorld::instance->_tileMap->getTileSize().width),
                         location.y + (difference.y * GameWorld::instance->_tileMap->getTileSize().height));
    
    //Player position.
    CCPoint playerPos = location;
    //Difference between the touch location and the players location.
    CCPoint diff = ccpSub(realSpot, playerPos);
    
    //Calculate if we're going left, right, down, or up, and get the new position we'll be moving to.
    playerPos = realSpot;
    Vec2 nextPos = location;
    if (abs(diff.x) > abs(diff.y)) {
        
        
        //TODO: add diagonal check for the collision.
        
        
        
        if (diff.x > 0) {
            //east
            nextPos.x += GameWorld::instance->_tileMap->getTileSize().width;
            //entityImage->initWithFile("BigDDirection/BigDR1.png");
        }
        else {
            //west
            nextPos.x -= GameWorld::instance->_tileMap->getTileSize().width;
            //entityImage->initWithFile("BigDDirection/BigDL1.png");
        }
    }
    else {
        if (diff.y > 0) {
            //north
            nextPos.y += GameWorld::instance->_tileMap->getTileSize().height;
            //entityImage->initWithFile("BigDDirection/BigDB1.png");
        }
        else {
            //south
            nextPos.y -= GameWorld::instance->_tileMap->getTileSize().height;
            //entityImage->initWithFile("BigDDirection/BigDF1.png");
        }
    }
    
    
    // safety check on the bounds of the map
    if (playerPos.x <= (GameWorld::instance->_tileMap->getMapSize().width * GameWorld::instance->_tileMap->getTileSize().width) &&
        playerPos.y <= (GameWorld::instance->_tileMap->getMapSize().height * GameWorld::instance->_tileMap->getTileSize().height) &&
        playerPos.y >= 0 &&
        playerPos.x >= 0)
    {
        //the tile where the player touches.
        CCPoint tileCoord;
        if (this->Path.size() > 0)
            tileCoord = nextSpot->coord;
        else
            tileCoord = GameWorld::instance->tileCoordForPosition(targetPos);
        
        //the tile immediately next to the player.
        CCPoint nextTileCoord = GameWorld::instance->tileCoordForPosition(realSpot);
        
        Vec2 place = Vec2(tileCoord.x, tileCoord.y);
        Vec2 nextPlace = Vec2(nextTileCoord.x, nextTileCoord.y);
        
        bool collisionbool = false;
        
        //check collision on tile next to character
        if (GameWorld::instance->checkCollision(GameWorld::instance->_meta->getTileGIDAt(nextPlace))) {
            
            //id of the tile type at the location.
            int buildingSpriteGID = GameWorld::instance->_background->getTileGIDAt(nextPlace);
            
            //Check if we've already destroyed this building to avoid adding more to the x value in the sprite rectangle.
            if (!GameWorld::instance->structureManager->containsStructure(buildingSpriteGID, nextPlace)) {
                //collision, not destroyed yet
                
                
                //collisionbool = true; // walks over buildings
            }
            collisionbool = true; // cant walk over buildings
        }
        if (this->Path.size() == 1) {
            this->Path.clear();
        }
        else {
            vector<ASWaypoint*> newPath;
            for (int i = 1; i < this->Path.size(); i++) {
                newPath.push_back(this->Path[i]);
            }
            this->Path = newPath;
        }
        
        if (!collisionbool) {
            walkTo(realSpot);
            //player->entityImage->setPosition(playerPos);
        }
        //this->setViewPointCenter(player->entityImage->getPosition());
        
    }
    
    
    
    
}
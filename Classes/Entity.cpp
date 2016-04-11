//
//  Entity.cpp
//  PMRGame
//
//  Created by Zakary Pacha on 10/02/2016.
//
//

#include "Entity.hpp"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameWorld.h"



Entity::Entity(Vec2 spawnLocation) {
    this->location = spawnLocation;
	this->targetPos = Vec2(-1, -1);
	this->isAlive = true;
}


CCPoint Entity::tileCoordForPosition(CCPoint position)
{
	int x = position.x / GameWorld::instance->_tileMap->getTileSize().width;
	int canvasheight = GameWorld::instance->GameWorld::instance->_tileMap->getMapSize().height * GameWorld::instance->_tileMap->getTileSize().height;
	int y = (canvasheight - position.y) / GameWorld::instance->_tileMap->getTileSize().height;
	return ccp(x, y);
}
void Entity::setSprite(cocos2d::Sprite* newImage) {
    this->entityImage = newImage;
}

void Entity::setPosition(cocos2d::Vec2 newpos) {
    this->location = newpos;
}

void Entity::update(float delta) {
    
}



void Entity::update(cocos2d::Vec2 targetPos, float deltaTime) {
	//return if the player is already in a moving animation.
	if (entityImage->getNumberOfRunningActions() > 0)
		return;

	//return if no touch location is registered.
	if (targetPos == nullptr)
		return;

	if (GameWorld::instance->chosenPath.size() == 0 &&
		GameWorld::instance->tileCoordForPosition(location).distance(GameWorld::instance->tileCoordForPosition(targetPos)) == 0)
		return;

	//return if the distance to the location is less than a tile.
	if (GameWorld::instance->tileCoordForPosition(targetPos).distance(GameWorld::instance->tileCoordForPosition(location)) == 0)
		return;

	Vec2 difference = GameWorld::instance->tileCoordForPosition(location) - GameWorld::instance->tileCoordForPosition(targetPos);

	ASWaypoint* nextSpot;
	if (GameWorld::instance->chosenPath.size() > 0) {
		nextSpot = GameWorld::instance->chosenPath[0];
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
			entityImage->initWithFile("BigDDirection/BigDR1.png");
		}
		else {
			//west
			nextPos.x -= GameWorld::instance->_tileMap->getTileSize().width;
			entityImage->initWithFile("BigDDirection/BigDL1.png");
		}
	}
	else {
		if (diff.y > 0) {
			//north
			nextPos.y += GameWorld::instance->_tileMap->getTileSize().height;
			entityImage->initWithFile("BigDDirection/BigDB1.png");
		}
		else {
			//south
			nextPos.y -= GameWorld::instance->_tileMap->getTileSize().height;
			entityImage->initWithFile("BigDDirection/BigDF1.png");
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
		if (GameWorld::instance->chosenPath.size() > 0)
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

				ValueMap tileValues = GameWorld::instance->_tileMap->getPropertiesForGID(buildingSpriteGID).asValueMap();
				CCString* testme = new CCString();
				*testme = tileValues.at("type").asString();
				if (testme->length() > 0) {
					Sprite *tile = GameWorld::instance->_background->getTileAt(nextPlace);

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
					GameWorld::instance->structureManager->addStructure(new BrokenStructure(buildingSpriteGID, tile, nextPlace)); //Adds the building attacked to the structure manaager, so we remember which buildings we've already destroyed.

					GameWorld::instance->scoreManager->addToScore(50, tile->getPosition()); //add to score example...

					Vec2 attackedTileLocation = tile->getPosition();
					Vec2 crowdSpawnLocation = attackedTileLocation;

					//get a good spawn for the crowd.
					if (testme->compare("top-left") == 0) {
						//top-left of struct.
						//either want crowd to spawn on left or above.
						Vec2 positionabove = ccp(attackedTileLocation.x + 16, attackedTileLocation.y + 48);
						Vec2 positionleft = ccp(attackedTileLocation.x - 16, attackedTileLocation.y + 16);

						if (location.distance(positionabove) <
							location.distance(positionleft))
							crowdSpawnLocation = positionleft;
						else
							crowdSpawnLocation = positionabove;

					}
					else if (testme->compare("top-right") == 0) {
						//top-right of struct.

						//either want crowd to spawn on right or above.
						Vec2 positionabove = ccp(attackedTileLocation.x + 16, attackedTileLocation.y + 48);
						Vec2 positionright = ccp(attackedTileLocation.x + 48, attackedTileLocation.y + 16);

						if (location.distance(positionabove) <
							location.distance(positionright))
							crowdSpawnLocation = positionright;
						else
							crowdSpawnLocation = positionabove;

					}
					else if (testme->compare("bottom-left") == 0) {
						//bottom-left of struct.
						//either want crowd to spawn on left or bottom.
						Vec2 positionbelow = ccp(attackedTileLocation.x + 16, attackedTileLocation.y - 16);
						Vec2 positionleft = ccp(attackedTileLocation.x - 16, attackedTileLocation.y + 16);

						if (location.distance(positionbelow) <
							location.distance(positionleft))
							crowdSpawnLocation = positionleft;
						else
							crowdSpawnLocation = positionbelow;

					}
					else if (testme->compare("bottom-right") == 0) {
						//bottom-right of struct.
						//either want crowd to spawn on left or bottom.
						Vec2 positionbelow = ccp(attackedTileLocation.x + 16, attackedTileLocation.y - 16);
						Vec2 positionright = ccp(attackedTileLocation.x + 48, attackedTileLocation.y + 16);

						if (location.distance(positionbelow) <
							location.distance(positionright))
							crowdSpawnLocation = positionright;
						else
							crowdSpawnLocation = positionbelow;
					}

					GameWorld::instance->npcManager->addNpc(new Crowd(crowdSpawnLocation));

					//TODO: add animations for destoying buildings



				}
				//collisionbool = true; // walks over buildings
			}
			collisionbool = true; // cant walk over buildings
		}
		if (GameWorld::instance->chosenPath.size() == 1) {
			GameWorld::instance->chosenPath.clear();
		}
		else {
			vector<ASWaypoint*> newPath;
			for (int i = 1; i < GameWorld::instance->chosenPath.size(); i++) {
				newPath.push_back(GameWorld::instance->chosenPath[i]);
			}
			GameWorld::instance->chosenPath = newPath;
		}

		if (!collisionbool) {
			walkTo(realSpot);
			//player->entityImage->setPosition(playerPos);
		}
		//this->setViewPointCenter(player->entityImage->getPosition());

	}

}

void Entity::walkTo(cocos2d::Vec2 newPos) {
	updatePosition(newPos, false);
}

void Entity::updatePosition(cocos2d::Vec2 newPos, bool tele) {
	//set the pos
	location = newPos;

	//Get the anchor point for the monster sprite on the y so he stands on the tile.
	int halfheight = entityImage->getTextureRect().size.height / 2;

	Vec2 anchoredPosition = Vec2(newPos.x,
		newPos.y + halfheight);

	if (!tele) {
		auto move_action = MoveTo::create(0.34f, anchoredPosition);
		entityImage->runAction(move_action);
	}
	else {
		entityImage->setPosition(anchoredPosition);
		
	}

}

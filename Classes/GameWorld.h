#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Player.hpp"
#include "StructureManager.hpp"

class GameWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void update(float);
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void keyboardListener();
    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
    double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);
    cocos2d::CCPoint tileCoordForPosition(cocos2d::CCPoint position);
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameWorld);
    
    cocos2d::CCPoint centerPoint;
    cocos2d::CCPoint touchLocation;
    cocos2d::TMXTiledMap* _tileMap;
    cocos2d::TMXLayer* _background;
    cocos2d::TMXLayer *_meta;
    void setViewPointCenter(cocos2d::CCPoint position);
    void cameraUpdater(float delta);
    StructureManager* structureManager;
    
private:
    Player* player;
    
    bool checkCollision(int tilegid);
    
};

#endif // __HELLOWORLD_SCENE_H__

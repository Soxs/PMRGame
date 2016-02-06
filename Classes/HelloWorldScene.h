#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    void keyboardListener();
    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
    double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);
    cocos2d::CCPoint tileCoordForPosition(cocos2d::CCPoint position);
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    cocos2d::CCPoint centerPoint;
    cocos2d::CCTMXTiledMap* _tileMap;
    cocos2d::CCTMXLayer* _background;
    cocos2d::CCTMXLayer *_meta;
    void setViewPointCenter(cocos2d::CCPoint position);
    
private:
    cocos2d::CCSprite *_player;
    bool isMoving;
    
};

#endif // __HELLOWORLD_SCENE_H__

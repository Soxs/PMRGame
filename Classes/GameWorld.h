#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Player.hpp"
#include "NpcManager.hpp"
#include "Crowd.hpp"
#include "Helicopter.hpp"
#include "StructureManager.hpp"
#include "ScoreManager.hpp"
#include "PathFinding.hpp"

class GameWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    static GameWorld* instance;
    

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void update(float);
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onDragEvent(cocos2d::Touch* touch, cocos2d::Event* event);
    
    void touchEvent(cocos2d::Touch* touch, cocos2d::Event* event);
    
    void keyboardListener();
    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
    double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);
    cocos2d::CCPoint tileCoordForPosition(cocos2d::CCPoint position);
    cocos2d::CCPoint tileCoordToPosition(cocos2d::CCPoint tileCoord);
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameWorld);
    
    
    cocos2d::Vec2 pointlocation;
    
    cocos2d::CCPoint centerPoint;
    cocos2d::CCPoint touchLocation;
    cocos2d::TMXTiledMap* _tileMap;
    cocos2d::TMXLayer* _background;
    cocos2d::TMXLayer *_meta;
    void resetWorld();
    void cameraUpdater(float delta);
    bool checkCollision(int tilegid);
    
    NpcManager* npcManager;
    StructureManager* structureManager;
    ScoreManager* scoreManager;
    vector<ASWaypoint*> chosenPath;
    PathFinding* pathFinding;
    Player* player;
    
    template <class DstType, class SrcType>
    bool IsType(const SrcType* src)
    {
        return dynamic_cast<const DstType*>(src) != 0;
    }
    
private:
    
    
    
    void setViewPointCenter(cocos2d::CCPoint position);
    
    
    
    cocos2d::Sprite* heartsprite;
    cocos2d::Label* healthLabel;
    
    cocos2d::Label* scoreTextLabel;
    cocos2d::Label* scoreLabel;
    
};

#endif // __HELLOWORLD_SCENE_H__

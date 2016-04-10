//
//  PathFinding.hpp
//  PMRGame
//
//  Created by Zakary Pacha on 03/03/2016.
//
//

#ifndef PathFinding_hpp
#define PathFinding_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace std;
//using namespace cocos2d;

const int width = 45, height = 45;
const int dir = 8; // number of possible directions to go at any position


struct ASWaypoint {
    
    bool hasParent = false;
    bool closed = false;
    
    //g score is the shortest distance/cost from start to current node.
    int g;
    
    //h is the distance/cost from the current to the end node.
    int h;
    
    //f is the total distance/cost from beginning to end. (g + h)
    int f;
    
    cocos2d::Vec2 coord;
    ASWaypoint* parent;
    
    int GetID() {
        return std::stoi( std::to_string(coord.x) + std::to_string(coord.y) );
    }
    
};

class PathFinding {
public:
    PathFinding();
    vector<ASWaypoint*> searchPath(cocos2d::Vec2 a, cocos2d::Vec2 b);
    
private:
    int w;
    int h;
    
    void init();
    
    int getHeuristic(cocos2d::Vec2 a, cocos2d::Vec2 b);
    vector<ASWaypoint*> ASWaypoints;
    vector<ASWaypoint*> getConnectedASWaypoints(ASWaypoint* aswp);
    ASWaypoint* getASWaypointWithCoord(cocos2d::Vec2 coord);
    int coordToID(cocos2d::Vec2 coord);
    
};


#endif /* PathFinding_hpp */

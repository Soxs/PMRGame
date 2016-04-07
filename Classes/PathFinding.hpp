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

using namespace std;
using namespace cocos2d;

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
    
    Vec2 coord;
    ASWaypoint* parent;
    
    int GetID() {
        return std::stoi( std::to_string(coord.x) + std::to_string(coord.y) );
    }
    
};

class PathFinding {
public:
    PathFinding();
    vector<ASWaypoint*> searchPath(Vec2 a, Vec2 b);
    
private:
    int w;
    int h;
    
    void init();
    
    int getHeuristic(Vec2 a, Vec2 b);
    vector<ASWaypoint*> ASWaypoints;
    vector<ASWaypoint*> getConnectedASWaypoints(ASWaypoint* aswp);
    ASWaypoint* getASWaypointWithCoord(Vec2 coord);
    int coordToID(Vec2 coord);
    
};


#endif /* PathFinding_hpp */

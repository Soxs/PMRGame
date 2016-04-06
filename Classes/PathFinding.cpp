//
//  PathFinding.cpp
//  PMRGame
//
//  Created by Zakary Pacha on 03/03/2016.
//
//

#include "PathFinding.hpp"

PathFinding::PathFinding(int wi, int he) {
    w=wi;
    h=he;
}

void PathFinding::init() {
    ASWaypoints.clear();
    for (int y = h-1; y == 0; y--) {
    //for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            ASWaypoint* asway = new ASWaypoint();
            asway->coord = Vec2(x, y);
            asway->f = 0;
            asway->g = 0;
            asway->h = 0;
            ASWaypoints.push_back(asway);
        }
    }
}

vector<ASWaypoint*> PathFinding::searchPath(Vec2 start, Vec2 end) {
    init();
    
    //initiate lists.
    vector<ASWaypoint*> open_list;
    vector<ASWaypoint*> closed_list;
    vector<ASWaypoint*> emptyPath;
    //reset the lists.
    open_list.clear();
    closed_list.clear();
    
    ASWaypoint* startasway = getASWaypointWithCoord(start);
    
    //add the start to the list;
    open_list.push_back(startasway);
    
    while (open_list.size() > 0) {
        
        // Grab the lowest f(x) to process next
        int lowInd = 0;
        for (int i = 0; i<open_list.size(); i++) {
            if (open_list.at(i)->f < open_list.at(lowInd)->f)
                lowInd = i;
        }
        ASWaypoint* currentNode = open_list.at(lowInd);
        
        // End case -- result has been found, return the traced path
        if (currentNode->coord.x == end.x &&
            currentNode->coord.y == end.y) {
            ASWaypoint* curr = currentNode;
            vector<ASWaypoint*> ret;
            while (curr->hasParent) {
                if (curr->coord == curr->parent->coord)
                    break;
                else{
                    ret.push_back(curr);
                    curr = curr->parent;
                }
            }
            reverse(ret.begin(), ret.end());
            emptyPath = ret;
            CCLOG("===== A* =====");
            
            CCLOG("== S %f, %f ==", start.x, start.y);
            CCLOG("== E %f, %f ==", end.x, end.y);
            for (int reti = 0; reti < ret.size(); reti++) {
                ASWaypoint* aw = ret[reti];
                CCLOG("x: %f, y: %f", aw->coord.x, aw->coord.y);
            }
            CCLOG("==============");
            return ret;
        }
        
        // Normal case -- move currentNode from open to closed, process each of its neighbors
        for (int indexToRemove = 0; indexToRemove < open_list.size(); indexToRemove++)
        {
            
            if (currentNode->coord == open_list[indexToRemove]->coord){
                open_list.erase(open_list.begin() + indexToRemove);
                break;
            }
            
        }
        
        closed_list.push_back(currentNode);
        vector<ASWaypoint*> neighbors = getConnectedASWaypoints(currentNode);
        
        for (int i = 0; i < neighbors.size(); i++) {
            ASWaypoint* neighbor = neighbors.at(i);
            
            bool isClosed = false;
            for (int index = 0; index < closed_list.size(); index++)
            {
                
                if (neighbor->coord == closed_list[index]->coord)
                    isClosed = true;
            }
            if (isClosed){
                continue;
            }
            
            
            // g score is the shortest distance from start to current node, we need to check if
            //	 the path we have arrived at this neighbor is the shortest one we have seen yet
            int gScore = currentNode->g +1;//+ getHeuristic(currentNode->coord, neighbor->coord); // + 1; // 1 is the distance for manhattan from a node to it's neighbor
            bool gScoreIsBest = false;
            
            
            bool isOpen = false;
            for (int index = 0; index < open_list.size(); index++)
            {
                ASWaypoint* var = open_list[index];
                if (var->coord == neighbor->coord)
                    isOpen = true;
            }
            
            if (!isOpen){
                gScoreIsBest = true;
                neighbor->h = getHeuristic(neighbor->coord, end);
            }
            else if (gScore < neighbor->g){
                gScoreIsBest = true;
            }
            
            if (gScoreIsBest){
                // Found an optimal (so far) path to this node.	 Store info on how we got here and
                //	just how good it really is...
                neighbor->parent = currentNode;
                neighbor->hasParent = true;
                neighbor->g = gScore;
                neighbor->f = neighbor->g + neighbor->h;
                emptyPath.push_back(neighbor);
            }
            
            if (!isOpen){
                open_list.push_back(neighbor);
            }
        }
        
    }
    
    
    return emptyPath;
    
}



int PathFinding::getHeuristic(Vec2 a, Vec2 b) {
    
    
    int xd, yd;
    xd = b.x - a.x;
    yd = b.y - a.y;
    
    // Manhattan distance
    return abs(xd)+abs(yd);
    
    // Chebyshev distance
    //return max(abs(xd), abs(yd));
    
    //Gets the euclidian distance
    //return static_cast<int>(sqrt(xd*xd + yd*yd));
}

vector<ASWaypoint*> PathFinding::getConnectedASWaypoints(ASWaypoint* aswp) {
    vector<ASWaypoint*> aswps;
    float x = aswp->coord.x;
    float y = aswp->coord.y;
    
    // West
    if (x-1 > 0 && x-1 < 45)
        aswps.push_back( getASWaypointWithCoord( Vec2(x-1, y)) );
    
    // East
    if (x+1 > 0 && x+1 < 45)
        aswps.push_back( getASWaypointWithCoord( Vec2(x+1, y)) );
    
    // North
    if (y-1 >= 0 && y-1 < 45)
        aswps.push_back( getASWaypointWithCoord( Vec2(x, y-1)) );
    
    // South
    if (y+1 >= 0 && y+1 < 45)
        aswps.push_back( getASWaypointWithCoord( Vec2(x, y+1)) );
    
    // Southwest
    //aswps.push_back( getASWaypointWithCoord( Vec2(x-1, y-1)) );
        
    // Southeast
    //aswps.push_back( getASWaypointWithCoord( Vec2(x+1, y-1)) );
        
    // Northwest
    //aswps.push_back( getASWaypointWithCoord( Vec2(x-1, y+1)) );
        
    // Northeast
    //aswps.push_back( getASWaypointWithCoord( Vec2(x+1, y+1)) );
    
    return aswps;
}

ASWaypoint* PathFinding::getASWaypointWithCoord(Vec2 coord) {
    for (int index = 0; index < ASWaypoints.size(); index++) {
        ASWaypoint* asway = ASWaypoints[index];
        if (asway->coord == coord) {
            return asway;
        }
    }
    ASWaypoint* nn = new ASWaypoint();
    nn->coord = coord;
    nn->f = 0;
    nn->g = 0;
    nn->h = 0;
    ASWaypoints.push_back(nn);
    return nn;
}

int PathFinding::coordToID(cocos2d::Vec2 coord) {
    return std::stoi( std::to_string(coord.x) + std::to_string(coord.y) );
}
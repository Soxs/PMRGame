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

const int width = 45, height = 45;
const int dir = 8; // number of possible directions to go at any position

class PathFinding {
public:
    PathFinding(int height, int width);
    string searchPath();
    
private:
    
    int map[width][height];
    static int closed_nodes_map[width][height];
    static int open_nodes_map[width][height];
    static int dir_map[width][height];
    
};

class node
{
    // current position
    int xPos;
    int yPos;
    // total distance already travelled to reach the node
    int level;
    // priority=level+remaining distance estimate
    int priority;  // smaller: higher priority
    
public:
    node(int xp, int yp, int d, int p)
    {xPos=xp; yPos=yp; level=d; priority=p;}
    
    int getxPos() const {return xPos;}
    int getyPos() const {return yPos;}
    int getLevel() const {return level;}
    int getPriority() const {return priority;}
    
    void updatePriority(const int & xDest, const int & yDest)
    {
        priority=level+estimate(xDest, yDest)*10; //A*
    }
    
    // give better priority to going strait instead of diagonally
    void nextLevel(const int & i) // i: direction
    {
        level+=(dir==8?(i%2==0?10:14):10);
    }
    
    // Estimation function for the remaining distance to the goal.
    const int & estimate(const int & xDest, const int & yDest) const
    {
        static int xd, yd, d;
        xd=xDest-xPos;
        yd=yDest-yPos;
        
        // Euclidian Distance
        d=static_cast<int>(sqrt(xd*xd+yd*yd));
        
        // Manhattan distance
        //d=abs(xd)+abs(yd);
        
        // Chebyshev distance
        //d=max(abs(xd), abs(yd));
        
        return(d);
    }
};

// Determine priority (in the priority queue)
bool operator<(const node & a, const node & b)
{
    return a.getPriority() > b.getPriority();
}

#endif /* PathFinding_hpp */

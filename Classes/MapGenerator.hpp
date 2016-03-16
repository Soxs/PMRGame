//
//  MapGenerator.hpp
//  PMRGame
//
//  Created by Zakary Pacha on 02/03/2016.
//
//

#ifndef MapGenerator_hpp
#define MapGenerator_hpp

#include <stdio.h>
#include "cocos2d.h"

class MapGenerator {
public:
	MapGenerator(cocos2d::Vec2 size);

private:
	//int map[];
	int width, height;

	int plaint = 0;
	int vroad = 1;
	int hroad = 2;
	int struc = 3;

};

#endif /* MapGenerator_hpp */

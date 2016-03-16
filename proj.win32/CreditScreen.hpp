#ifndef Credit_Screen_hpp
#define Credit_Screen_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

class CreditScreen : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	


	CREATE_FUNC(CreditScreen);

private:
	cocos2d::ui::Button* MenuButton;
	cocos2d::ui::Button* StartButton;
	

};

#endif 
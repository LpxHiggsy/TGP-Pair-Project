#ifndef __CocosProject__Wall__
#define __CocosProject__Wall__

#include "cocos2d.h"
#include "ui/cocosGUI.h"

#include <stdio.h>


class Wall : public cocos2d::Node
{
public:
	Wall();
	~Wall();

	virtual bool init() override;
	static Wall* create();

	void    update(float);
	void	reset();
	bool    hasCollidedWithAWall(cocos2d::Rect collisionBoxToCheck);

private:
	cocos2d::Sprite* wall;
	float       startXPosition;
	float       startYPosition;
	float       currentSpeed;


};
#endif 
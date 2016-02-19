#ifndef __CocosProject__Barrel__
#define __CocosProject__Barrel__

#include "cocos2d.h"
#include "ui/cocosGUI.h"

#include <stdio.h>


class Barrel : public cocos2d::Node
{
public:
	Barrel();
	~Barrel();

	virtual bool init() override;
	static Barrel* create();

	void    update(float);
	void	reset();
	bool    hasCollidedWithABarrel(cocos2d::Rect collisionBoxToCheck);

private:
	cocos2d::Sprite* barrel;
	float       startXPosition;
	float       startYPosition;
	float       currentSpeed;


};
#endif 
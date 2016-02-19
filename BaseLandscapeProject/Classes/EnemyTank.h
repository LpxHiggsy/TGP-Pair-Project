#ifndef __CocosProject__EnemyTank__
#define __CocosProject__EnemyTank__

#include "cocos2d.h"
#include "ui/cocosGUI.h"

#include <stdio.h>


class EnemyTank : public cocos2d::Node
{
public:
	EnemyTank();
	~EnemyTank();

	virtual bool init() override;
	static EnemyTank* create();

	void    update(float);
	void	reset();
	bool    hasCollidedWithAEnemyTank(cocos2d::Rect collisionBoxToCheck);

private:
	cocos2d::Sprite* Enemy_Tank;
	float       startXPosition;
	float       startYPosition;
	float       currentSpeed;


};
#endif 
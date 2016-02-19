#include "EnemyTank.h"
#include "cocostudio/CocoStudio.h"
#include "GameManager.h"

using namespace cocos2d;

EnemyTank* EnemyTank::create()
{
	EnemyTank* myNode = new EnemyTank();
	if (myNode->init())
	{
		myNode->autorelease();
		return myNode;
	}
	else
	{
		CC_SAFE_DELETE(myNode);
		return nullptr;
	}
	return myNode;
}

bool EnemyTank::init()
{
	if (!Node::init())
	{
		return false;
	}

	//Load this object in from cocos studio.
	auto rootNode = CSLoader::createNode("res/EnemyTank.csb");
	addChild(rootNode);

	auto winSize = Director::getInstance()->getVisibleSize();
	this->setAnchorPoint(Vec2(1.0f, 0.0f));
	this->setPosition(Vec2(0.0f, winSize.height*0.25));
	this->scheduleUpdate();

	Enemy_Tank = (Sprite*)rootNode->getChildByName("enemyTank");

	startXPosition = 1190.0f;
	startYPosition = Enemy_Tank->getPositionY();
	Enemy_Tank->setPosition(startXPosition, startYPosition);

	currentSpeed = 814.0f;

	return true;
}

EnemyTank::EnemyTank()
{
}


EnemyTank::~EnemyTank()
{

}


void EnemyTank::update(float deltaTime)
{
	if (GameManager::sharedGameManager()->isGameLive)
	{
		//Get the window size.
		auto  winSize = Director::getInstance()->getVisibleSize();

		//Move the pipes to the left.
		Vec2 currentTankPos = Enemy_Tank->getPosition();
		Enemy_Tank->setPosition(currentTankPos.x - currentSpeed*deltaTime, currentTankPos.y);

		//Did the x position (incorporating the sprite width) go off screen.
		if (currentTankPos.x < -Enemy_Tank->getBoundingBox().size.width*0.5f)
		{
			//Set the new positionings.
			Enemy_Tank->setPosition(startXPosition, startYPosition);
		}
	}

}

bool EnemyTank::hasCollidedWithAEnemyTank(Rect collisionBoxToCheck)
{
	Rect modifiedEnemyTank;
	modifiedEnemyTank.size = Enemy_Tank->getBoundingBox().size;
	modifiedEnemyTank.origin = convertToWorldSpaceAR(Enemy_Tank->getBoundingBox().origin);

	if (modifiedEnemyTank.intersectsRect(collisionBoxToCheck))
	{
		return true;
	}
	return false;
}
void EnemyTank::reset()
{
	Enemy_Tank->setPosition(startXPosition, startYPosition);
}

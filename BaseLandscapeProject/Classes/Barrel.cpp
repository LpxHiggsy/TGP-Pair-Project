#include "Barrel.h"
#include "cocostudio/CocoStudio.h"
#include "GameManager.h"
#include "ui/CocosGUI.h"
#include "stdio.h"

using namespace cocos2d;

Barrel* Barrel::create()
{
	Barrel* myNode = new Barrel();
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

bool Barrel::init()
{
	if (!Node::init())
	{
		return false;
	}

	//Load this object in from cocos studio.
	auto rootNode = CSLoader::createNode("res/Barrel.csb");
	addChild(rootNode);

	this->scheduleUpdate();

	barrel = (Sprite*)rootNode->getChildByName("Barrel");

	auto winSize = Director::getInstance()->getVisibleSize();
	this->setPosition(Vec2(0.0f, winSize.height*0.5));
	this->scheduleUpdate();

	startXPosition = 1190.0f;
	startYPosition = barrel->getPositionY();
	barrel->setPosition(startXPosition, startYPosition);

	currentSpeed = 701.8f;
	

	return true;
}

Barrel::Barrel()
{
}


Barrel::~Barrel()
{

}


void Barrel::update(float deltaTime)
{
	if (GameManager::sharedGameManager()->isGameLive)
	{
		//Get the window size.
		auto  winSize = Director::getInstance()->getVisibleSize();

		//Move the pipes to the left.
		Vec2 currentBarrelPos = barrel->getPosition();
		barrel->setPosition(currentBarrelPos.x - currentSpeed*deltaTime, currentBarrelPos.y);

		//Did the x position (incorporating the sprite width) go off screen.
		if (currentBarrelPos.x < -barrel->getBoundingBox().size.width*0.5f)
		{
			//Set the new positionings.
			barrel->setPosition(startXPosition, startYPosition);
		}
	}
}

bool Barrel::hasCollidedWithABarrel(Rect collisionBoxToCheck)
{
	Rect modifiedBarrel;
	modifiedBarrel.size = barrel->getBoundingBox().size;
	modifiedBarrel.origin = convertToWorldSpaceAR(barrel->getBoundingBox().origin);

	if (modifiedBarrel.intersectsRect(collisionBoxToCheck))
	{
		return true;
	}
	return false;
}
void Barrel::reset()
{
	barrel->setPosition(startXPosition, startYPosition);
}
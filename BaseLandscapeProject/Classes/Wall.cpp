#include "Wall.h"
#include "cocostudio/CocoStudio.h"
#include "GameManager.h"


using namespace cocos2d;

Wall* Wall::create()
{
	Wall* myNode = new Wall();
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

bool Wall::init()
{
	if (!Node::init())
	{
		return false;
	}

	//Load this object in from cocos studio.
	auto rootNode = CSLoader::createNode("res/Wall.csb");
	addChild(rootNode);

	auto winSize = Director::getInstance()->getVisibleSize();
	this->setPosition(Vec2(0.0f, winSize.height*0.8));
	this->scheduleUpdate();

	wall = (Sprite*)rootNode->getChildByName("Wall");

	startXPosition = 1190.0f;
	startYPosition = wall->getPositionY();
	wall->setPosition(startXPosition, startYPosition);

	currentSpeed = 514.8f;

	return true;
}

Wall::Wall()
{
}


Wall::~Wall()
{

}


void Wall::update(float deltaTime)
{
	if (GameManager::sharedGameManager()->isGameLive)
	{
		//Get the window size.
		auto  winSize = Director::getInstance()->getVisibleSize();

		//Move the pipes to the left.
		Vec2 currentWallPos = wall->getPosition();
		wall->setPosition(currentWallPos.x - currentSpeed*deltaTime, currentWallPos.y);

		//Did the x position (incorporating the sprite width) go off screen.
		if (currentWallPos.x < -wall->getBoundingBox().size.width*0.5f)
		{
			//Set the new positionings.
			wall->setPosition(startXPosition, startYPosition);
		}
	}
}

bool Wall::hasCollidedWithAWall(Rect collisionBoxToCheck)
{
	Rect modifiedWall;
	modifiedWall.size = wall->getBoundingBox().size;
	modifiedWall.origin = convertToWorldSpaceAR(wall->getBoundingBox().origin);

	if (modifiedWall.intersectsRect(collisionBoxToCheck))
	{
		return true;
	}
	return false;
}
void Wall::reset()
{
	wall->setPosition(startXPosition, startYPosition);
}
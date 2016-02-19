#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "GameManager.h"
#include "ui/CocosGUI.h"
#include "stdio.h"
#include "EnemyTank.h"
#include "Wall.h"
#include "Barrel.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);

	this->scheduleUpdate();
	auto winSize = Director::getInstance()->getVisibleSize();
	HighScore = 0;
	Tank = (Sprite*)rootNode->getChildByName("Player");

	enemyTankNode = (EnemyTank*)rootNode->getChildByName("enemyTank");
	enemyTank = EnemyTank::create();
	this->addChild(enemyTank);


	wallNode = (Wall*)rootNode->getChildByName("Wall");
	wall = Wall::create();
	this->addChild(wall);


	barrelNode = (Barrel*)rootNode->getChildByName("Barrel");
	barrel = Barrel::create();
	this->addChild(barrel);


	scoreLabel = static_cast<ui::Text*>(rootNode->getChildByName("label"));
	
	Highscore = static_cast<ui::Text*>(rootNode->getChildByName("High"));
	Highscore->setPosition(Vec2(0-500.0f, 3 * (winSize.height*0.25f)));
	Highscore->setAnchorPoint(Vec2(0.5, 0.5));

	playerHealth = static_cast<ui::Text*>(rootNode->getChildByName("Player_Health"));

	////TOUCHES
	auto touchListener = EventListenerTouchOneByOne::create();

	// Set callbacks for our touch functions.
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//StartButton
	StartButton = static_cast<ui::Button*>(rootNode->getChildByName("StartButton"));
	StartButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::StartButtonPressed, this));
	StartButton->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.5f));

	Up_Button = static_cast<ui::Button*>(rootNode->getChildByName("Up_Button"));
	Up_Button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::UpButtonPressed, this));
	Up_Button->setAnchorPoint(Vec2(0, 0));
	Up_Button->setPosition(Vec2(0, 0));
	Up_Button->setScale(3.0f);

	Down_Button = static_cast<ui::Button*>(rootNode->getChildByName("Down_Button"));
	Down_Button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::DownButtonPressed, this));
	Down_Button->setAnchorPoint(Vec2(1, 0));
	Down_Button->setPosition(Vec2(winSize.width, 0));
	Down_Button->setScale(3.0f);

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("res/crash-collision.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("res/explosion.wav");

	GameManager::sharedGameManager()->isGameLive = false;

    return true;
}

void HelloWorld::UpButtonPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (GameManager::sharedGameManager()->isGameLive)
	{
		CCLOG("In touch &d", type);
		Vec2 currentPos = Tank->getPosition();

		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			if (currentPos.y < 468)
			{
				Tank->setPosition(currentPos.x, currentPos.y += 113);
			}
		}
	}

}

void HelloWorld::DownButtonPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (GameManager::sharedGameManager()->isGameLive)
	{
		CCLOG("In touch &d", type);
		Vec2 currentPos = Tank->getPosition();

		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			if (currentPos.y > 242)
			{
				Tank->setPosition(currentPos.x, currentPos.y -= 113);
			}
		}
		
	}
}

void HelloWorld::StartButtonPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
	CCLOG("In touch %d", type);

	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		this->StartGame();
	}

	this->StartGame();
}

void HelloWorld::StartGame()
{
	auto winSize = Director::getInstance()->getVisibleSize();
	GameManager::sharedGameManager()->isGameLive = true;
	Vec2 currentPos = Tank->getPosition();

	auto moveTo = MoveTo::create(0.0f, Vec2(-winSize.width*0.5f, winSize.height*0.5f));
	StartButton->runAction(moveTo);

	Tank->setPosition(currentPos.x, currentPos.y);
	enemyTank->reset();
	wall->reset();
	barrel->reset();

	auto Highscorereset = MoveTo::create(0.0f, (Vec2(0 - 500.0f, 3 * (winSize.height*0.25f))));
	Highscore->runAction(Highscorereset);

	GameManager::sharedGameManager()->ResetScore();
	GameManager::sharedGameManager()->ResetHealth();
}

void HelloWorld::EndGame()
{
	auto winSize = Director::getInstance()->getVisibleSize();
	GameManager::sharedGameManager()->isGameLive = false;

	auto moveTo = MoveTo::create(0.0f, Vec2(winSize.width*0.5f, winSize.height*0.5f));
	StartButton->runAction(moveTo);

	auto Highscoremove = MoveTo::create(0.0f, Vec2(winSize.width*0.5f, 3*(winSize.height*0.25f)));
	Highscore->runAction(Highscoremove);

	if (GameManager::sharedGameManager()->GetScore() > HighScore)
	{
		HighScore = GameManager::sharedGameManager()->GetScore();
		Highscore->setString(StringUtils::format("High Score: %d", HighScore));
	}
	
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	cocos2d::log("touch began");
	return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	cocos2d:log("touch ended");
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
	cocos2d::log("touch moved");
}

void HelloWorld::onTouchCancelled(Touch* touch, Event* event)
{
	cocos2d::log("touch cancelled");
}

void HelloWorld::update(float delta)
{
	if (GameManager::sharedGameManager()->isGameLive)
	{

		Vec2 currentPos = Tank->getPosition();
		Tank->setPosition(currentPos.x, currentPos.y);
		GameManager::sharedGameManager()->AddToScore(1);
		int score = GameManager::sharedGameManager()->GetScore();
		Health = GameManager::sharedGameManager()->GetHealth();
		scoreLabel->setString(StringUtils::format("Score: %d", GameManager::sharedGameManager()->GetScore()));
		playerHealth->setString(StringUtils::format("Health: %d", Health));

		if (enemyTank->hasCollidedWithAEnemyTank(Tank->getBoundingBox()))
		{
			GameManager::sharedGameManager()->SubtractHealth(3);
			enemyTank->reset();
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("res/crash-collision.wav", false, 1.0f, 1.0f, 1.0f);
		}
		if (wall->hasCollidedWithAWall(Tank->getBoundingBox()))
		{
			GameManager::sharedGameManager()->SubtractHealth(2);
			wall->reset();
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("res/crash-collision.wav", false, 1.0f, 1.0f, 1.0f);
		}
		if (barrel->hasCollidedWithABarrel(Tank->getBoundingBox()))
		{
			GameManager::sharedGameManager()->SubtractHealth(1);
			barrel->reset();
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("res/crash-collision.wav", false, 1.0f, 1.0f, 1.0f);
		}
		if (Health <= 0)
		{
			playerHealth->setString(StringUtils::format("Health: %d", 0));
			this->EndGame();
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("res/explosion.wav", false, 1.0f, 1.0f, 1.0f);
		}
	}
}
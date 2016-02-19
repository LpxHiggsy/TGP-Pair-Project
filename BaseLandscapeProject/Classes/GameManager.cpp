#include "GameManager.h"

GameManager* GameManager::instance = NULL;

GameManager* GameManager::sharedGameManager()
{
	if (instance == NULL)
	{
		instance = new GameManager();
	}

	return instance;
}


GameManager::GameManager()
{
	isGameLive = false;
	score = 0;
	health = 20;
}

GameManager::~GameManager()
{

}

void GameManager::AddToScore(int increment)
{
	this->score += increment;
}

void GameManager::ResetScore()
{
	score = 0;
}

int GameManager::GetScore()
{
	return score;
}

void GameManager::SubtractHealth(int increment)
{
	this->health -= increment;
}

void GameManager::ResetHealth()
{
	health = 20;
}

int GameManager::GetHealth()
{
	return health;
}
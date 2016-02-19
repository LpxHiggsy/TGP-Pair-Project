//
//  GameManger.h
//  CocosProject


#ifndef __CocosProject__GameManager__
#define __CocosProject__GameManager__

#include <stdio.h>

class GameManager
{
public:
	~GameManager();
	static GameManager* sharedGameManager();

	void AddToScore(int increment);
	void ResetScore();
	int GetScore();

	void SubtractHealth(int increment);
	void ResetHealth();
	int GetHealth();

	bool isGameLive;

private:
	GameManager();
	static GameManager* instance;

	int score;
	int health;
};
#endif /* defined(__CocosProject__GameManger__) */
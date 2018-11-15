#pragma once
#include "gameNode.h"
#include "background.h"
#include "player.h"
#include "bulletManager.h"
#include "enemyManager.h"
#include "itemManager.h"
#include "UI.h"

class playGround : public gameNode
{
private:
	background * _bg;
	player* _player;
	playerBullet* _pBullet;
	enemyManager* _em;
	enemyBullet* _eBullet;
	itemManager* _im;
	UI* _ui;
	image* _gameOverImage;
	image* _ending;
	bool _gameStart;
	bool _gameOver;
	int _alpha1;

	//TCHAR test1[128];
	

public:
	virtual HRESULT init(void);		//초기화 함수
	virtual void release(void);		//메모리 관련 해제
	virtual void update(void);		//업데이트(연산)
	virtual void render(void);		//그려주는 함수

	void gameStart(void);

	playGround();
	~playGround();
};


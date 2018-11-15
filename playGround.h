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
	virtual HRESULT init(void);		//�ʱ�ȭ �Լ�
	virtual void release(void);		//�޸� ���� ����
	virtual void update(void);		//������Ʈ(����)
	virtual void render(void);		//�׷��ִ� �Լ�

	void gameStart(void);

	playGround();
	~playGround();
};


#pragma once
#include "gameNode.h"

class player;
class enemyManager;
class playerBullet;
class UI;

class itemManager : public gameNode
{
private:
	image * _item[3];
	enemyManager* _em;
	player* _player;
	playerBullet* _pBullet;
	UI* _ui;
	float _x;
	float _y;
	float _speed;
	int _type;
	bool _isPresent;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void setItem(float x, float y, bool isPresent)
	{
		if (_isPresent == false)
		{
			_type = RND->getInt(3);
			_x = x;
			_y = y;
			_isPresent = isPresent;
		}
	}
	void setEnemyManagerMemoryAddressLink(enemyManager* em) { _em = em; }
	void setPlayerMemoryAddressLink(player* player) { _player = player; }
	void setPlayerBulletMemoryAddressLink(playerBullet* pBullet) { _pBullet = pBullet; }
	void setUIMemoryAddressLink(UI* ui) { _ui = ui; }

	itemManager();
	~itemManager();
};


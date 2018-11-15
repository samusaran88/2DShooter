#pragma once
#include "gameNode.h"
#include <vector>

enum
{
	RED, BLUE, GREEN, YELLOW, PURPLE
};

struct tagBULLET
{
	int type;
	int type2;
	int count;
	int frame;
	float x;
	float y;
	float radius;
	float speed;
	float directionAngle;
	float spinAngle;
	float damage;
	bool isFire;
	bool isDestroyed;
};

class player;
class enemyManager;

class playerBullet : public gameNode
{
private:
	image * _redBullet;
	image* _blueBullet;
	image* _greenBullet;
	image* _redBulletExplode;
	image* _blueBulletExplode;
	image* _greenBulletExplode;
	vector<tagBULLET> _vPlayerBullet;
	vector<tagBULLET>::iterator _viPlayerBullet;
	player* _player;
	enemyManager * _em;
	int _bulletType;
	int _counter;
	int _bulletCount;

public:

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void pBulletMove(void);
	void pBulletSetting(void);
	void pBulletCollision(void);
	void setEnemyManagerMemoryAddressLink(enemyManager* em) { _em = em; }
	void setPlayerMemoryAddressLink(player* player) { _player = player; }
	void setBulletType(int type) { _bulletType = type; }
	

	playerBullet();
	~playerBullet();
};

class enemyBullet : public gameNode
{
private:
	image * _yellowBullet;
	image* _purpleBullet;
	image* _damageImage;
	vector<tagBULLET> _vEnemyBullet;
	vector<tagBULLET>::iterator _viEnemyBullet;
	player * _player;
	enemyManager * _em;
	int _bulletCount;
	int _bulletCount2;
	int _damage;
	float _tempX;
	float _tempY;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void eBulletMove(void);
	void eBulletSetting(void);
	void eBulletCollision(void);
	void removeAllBullets(void);
	void setEnemyManagerMemoryAddressLink(enemyManager* em) { _em = em; }
	void setPlayerMemoryAddressLink(player* player) { _player = player; }
	void setBulletCount() { _bulletCount2 = 0; }

	enemyBullet();
	~enemyBullet();
};
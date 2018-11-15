#pragma once
#include "gameNode.h"
#include <vector>

struct tagENEMY
{
	float x;
	float y;
	float direction;
	float radius;
	float speed;
	float percent;
	int frameX;
	int frameEx;
	int type;
	int maxHp;
	int currentHp;
	int count;
	int bulletCount;
	int alpha;
	int stage;
	int pattern;
	int item;
	bool isPresent;
	bool onScreen;
	bool isStop;
	bool isFire;
	bool isDead;
	bool remove;
};
 
class enemyBullet;
class player;
class itemManager;

class enemyManager
{
private:
	image * _minion[3];
	image * _hpBarTop;
	image* _hpBarBottom;
	image* _explosion;
	image* _boss1Idle;
	image* _boss1Attack;
	enemyBullet* _eBullet;
	player* _player;
	itemManager* _im;
	vector<tagENEMY> _vEnemy;
	vector<tagENEMY>::iterator _viEnemy;
	int _count;
	int _frameCount;
	int _frameIndex;
	int _frameIndex2;
	int _stage;
	int _vNum;
	int bezierX;
	int bezierY;
	int _state;
	int _life;
	bool _gameOver;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void setEnemy(float x, float y, float direction, int type);
	void setStage(void);
	void move(void);
	void frameCount(void);
	void removeEnemy(void);
	void bossHpSetting(HDC hdc);
	float getPt(float n1, float n2, float perc);
	void bezier(float x1, float y1, float x2, float y2, float x3, float y3, float i);
	vector<tagENEMY> getVEnemy() { return _vEnemy; }
	vector<tagENEMY>::iterator getVIEnemy() { return _viEnemy; }
	int getStage() { return _stage; }
	bool getGameOver() { return _gameOver; }
	void setVEnemyFire(bool isFire, int vNum) { _vEnemy[vNum].isFire = isFire; }
	void setVEnemyHp(float damage, int vNum) { _vEnemy[vNum].currentHp -= damage; }
	void setEnemyBulletMemoryAddressLink(enemyBullet* eBullet) { _eBullet = eBullet; }
	void setPlayerMemoryAddressLink(player* player) { _player = player; }
	void setItemManagerAddressLink(itemManager* im) { _im = im; }

	enemyManager();
	~enemyManager();
};


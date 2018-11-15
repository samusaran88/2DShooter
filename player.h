#pragma once
#include "gameNode.h"

enum 
{
	LEFT, UP, RIGHT, DOWN
};

class player : public gameNode
{
private:
	image * _arleIdle;
	image* _arleLeft;
	image* _arleRight;
	image* _hitBox;
	image * _hpBarTop;
	image* _hpBarBottom;
	image* _arleLost;
	image* _carbuncle;
	int _counter;
	int _frame;
	int _arleAlpha;
	int _hitBoxAlpha;
	int _playerDirection;
	int _maxHp;
	int _currentHp;
	int _radius;
	int _life;
	int _alphaControl;
	int _alphaCounter;
	int _carbuncleFrame;
	float _carbuncleSpeed;
	float _carbuncleAngle;
	float _carbuncleX;
	float _carbuncleY; 
	float _playerX;
	float _playerY;
	bool _focusMode;
	bool _isFire;
	bool _isDead;
	bool _canFire;
	bool _invincibility;
	bool _gameOver;
public:

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void counter(void);
	void control(void);
	void carbuncle(void);
	void playerDead(void);

	int getPlayerLife() { return _life; }
	float getPlayerX() { return _playerX; }
	float getPlayerY() { return _playerY; }
	bool getIsFire() { return _isFire; }
	bool getIsDead() { return _isDead; }
	bool getGameOver() { return _gameOver; }
	bool getInvincibility() { return _invincibility; }
	void setPlayerHp() { _currentHp -= 10; }

	player();
	~player();
};


#pragma once
#include "gameNode.h"

class player;

class UI
{
private:
	image * _start;
	image* _ui;
	image* _life;
	image* _pressEnter;
	image* _ready;
	player* _player;
	int _alpha1;
	int _alpha2;
	int _counter;
	int _frame1;
	int _type;
	bool _isStart;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc, int alpha);

	void setIsStart(bool isStart) { _isStart = isStart; }
	void setPlayerMemoryAddressLink(player* player) { _player = player; }
	void setPlayerType(int type) { _type = type; }

	UI();
	~UI();
};


#pragma once
#include "gameNode.h"

struct tagTREES
{
	float x;
	float y;
	float speed;
};

class background : public gameNode
{
private:
	image * _stage1background;
	image* _LtTree1;
	image* _LtTree2;
	image* _LtTree3;
	image* _RtTree1;
	image* _RtTree2;
	image* _RtTree3;
	image* _bossBackground1;
	image* _bossBackground2;
	tagTREES _tree[4][3];
	int _loopX;
	int _loopY;
	int _loopSpeed;
	int _alpha1;
	int _alpha2;
	int _alpha3;
	int _stage;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void setStage(int stage) { _stage = stage; }


	background();
	~background();
};


#include "stdafx.h"
#include "background.h"


background::background()
{
}


background::~background()
{

}

HRESULT background::init(void)
{
	_stage1background = IMAGEMANAGER->addImage("stage1background", ".\\images\\backgroundlarge.bmp", 1000, 750, true, RGB(255, 0, 255), true);
	_LtTree1 = IMAGEMANAGER->addImage("LtTree1", ".\\images\\lefttreelayer1.bmp", 211, 211, true, RGB(255, 0, 255), true);
	_LtTree2 = IMAGEMANAGER->addImage("LtTree2", ".\\images\\lefttreelayer2.bmp", 157, 157, true, RGB(255, 0, 255), true);
	_LtTree3 = IMAGEMANAGER->addImage("LtTree3", ".\\images\\lefttreelayer3.bmp", 105, 105, true, RGB(255, 0, 255), true);
	_RtTree1 = IMAGEMANAGER->addImage("RtTree1", ".\\images\\righttreelayer1.bmp", 211, 211, true, RGB(255, 0, 255), true);
	_RtTree2 = IMAGEMANAGER->addImage("RtTree2", ".\\images\\righttreelayer2.bmp", 157, 157, true, RGB(255, 0, 255), true);
	_RtTree3 = IMAGEMANAGER->addImage("RtTree3", ".\\images\\righttreelayer3.bmp", 105, 105, true, RGB(255, 0, 255), true);
	_bossBackground1 = IMAGEMANAGER->addImage("bossBackground1", ".\\images\\bossbackground1large.bmp", 1000, 750, true, RGB(255, 0, 255), true);
	_bossBackground2 = IMAGEMANAGER->addImage("bossBackground2", ".\\images\\bossbackground2large.bmp", 1000, 750, true, RGB(255, 0, 255), true);
	_loopX = _loopY = 0;
	_loopSpeed = 3;
	_alpha1 = 255;
	_alpha2 = 0;
	_alpha3 = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			_tree[i][j].x = (j * 250) + RND->getInt(100);
			_tree[i][j].y = (i - 1) * 250 + RND->getInt(100);
			_tree[i][j].speed = _loopSpeed;
		}
	}

	return S_OK;
}

void background::release(void)
{

}

void background::update(void) 
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			_tree[i][j].y += _loopSpeed;
			if (_tree[i][j].y > WINSIZEY)
			{
				_tree[i][j].x = (j * 250) + RND->getInt(100);
				_tree[i][j].y = -300 + RND->getInt(100);
			}
		}
	}
	_loopY -= _loopSpeed;
	if (_stage == 111 && _alpha2 > 0)
	{
		_alpha2 -= 3;
		_alpha3 += 3;
	}
	else if (_stage > 100 && _alpha1 > 0)
	{
		_alpha1 -= 3;
		_alpha2 += 3;
	}
	else if (_stage < 100 && _alpha3 > 0)
	{
		_alpha1 += 3;
		_alpha3 -= 3;
	}
}

void background::render(HDC hdc) 
{
	if (_alpha1 > 0)
	{
		_stage1background->alphaLoopRender(hdc, &RectMake(0, 0, WINSIZEX, WINSIZEY), _loopX, _loopY, _alpha1);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (j == 0)
				{
					_LtTree1->alphaRender(hdc, _tree[i][j].x, _tree[i][j].y, _alpha1 * 7 / 10);
				}
				else
				{
					_RtTree1->alphaRender(hdc, _tree[i][j].x, _tree[i][j].y, _alpha1 * 7 / 10);
				}
			}
		}
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (j == 0)
				{
					_LtTree2->alphaRender(hdc, _tree[i][j].x + 27, _tree[i][j].y - 40 + 80 * (_tree[i][j].y / WINSIZEY), _alpha1 * 4 / 5);
				}
				else
				{
					_RtTree2->alphaRender(hdc, _tree[i][j].x + 27, _tree[i][j].y - 40 + 80 * (_tree[i][j].y / WINSIZEY), _alpha1 * 4 / 5);
				}
			}
		}
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (j == 0)
				{
					_LtTree3->alphaRender(hdc, _tree[i][j].x + 53, _tree[i][j].y - 60 + 120 * (_tree[i][j].y / WINSIZEY), _alpha1);
				}
				else
				{
					_RtTree3->alphaRender(hdc, _tree[i][j].x + 53, _tree[i][j].y - 60 + 120 * (_tree[i][j].y / WINSIZEY), _alpha1);
				}
			}
		}
	}
	if (_alpha2 > 0) _bossBackground1->alphaLoopRender(hdc, &RectMake(0, 0, WINSIZEX, WINSIZEY), _loopX, _loopY, _alpha2);
	if (_alpha3 > 0) _bossBackground2->alphaLoopRender(hdc, &RectMake(0, 0, WINSIZEX, WINSIZEY), _loopX, _loopY, _alpha3);
}
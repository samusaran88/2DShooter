#include "stdafx.h"
#include "enemyManager.h"
#include "bulletManager.h"
#include "player.h"
#include "itemManager.h"


enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{

}

HRESULT enemyManager::init(void)  
{
	_minion[0] = IMAGEMANAGER->addFrameImage("minion1", ".\\images\\minion1.bmp", 192, 64, 3, 1, true, RGB(255, 0, 255), true);
	_minion[1] = IMAGEMANAGER->addFrameImage("minion2", ".\\images\\minion2.bmp", 234, 42, 6, 1, true, RGB(255, 0, 255), true);
	_minion[2] = IMAGEMANAGER->addFrameImage("minion3", ".\\images\\minion3.bmp", 264, 61, 8, 1, true, RGB(255, 0, 255), true);
	_hpBarTop = IMAGEMANAGER->addImage("hpBarTop", ".\\images\\hpbartop.bmp", 50, 10, true, RGB(255, 0, 255), true);
	_hpBarBottom = IMAGEMANAGER->addImage("hpBarBottom", ".\\images\\hpbarbottom.bmp", 69, 14, true, RGB(255, 0, 255), true);
	_explosion = IMAGEMANAGER->addFrameImage("explosion", ".\\images\\explosion.bmp", 1344, 48, 28, 1, true, RGB(255, 0, 255), true);
	_boss1Idle = IMAGEMANAGER->addFrameImage("boss1Idle", ".\\images\\boss1Idle.bmp", 280, 120, 4, 1, true, RGB(255, 0, 255), true);
	_boss1Attack = IMAGEMANAGER->addFrameImage("boss1Attack", ".\\images\\boss1Attack.bmp", 480, 102, 5, 1, true, RGB(255, 0, 255), true);
	_count = 0;
	_state = 0;
	_frameCount = 0;
	_frameIndex = 0;
	_frameIndex2 = 0;
	_stage = 0;
	_life = 0;
	_gameOver = false;
	return S_OK;
}

void enemyManager::release(void)  
{

}

void enemyManager::update(void)	  
{
	frameCount();
	removeEnemy();
	setStage();
	move();
}

void enemyManager::render(HDC hdc)
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		if (_viEnemy->isPresent == true && _viEnemy->type == 1)
		{
			_minion[0]->alphaFrameRender(hdc, _viEnemy->x - _viEnemy->radius, _viEnemy->y - _viEnemy->radius, _frameIndex % _viEnemy->frameX, 0, _viEnemy->alpha);
			_hpBarBottom->alphaRender(hdc, _viEnemy->x - 34, _viEnemy->y + 33, _viEnemy->alpha);
			_hpBarTop->alphaRender(hdc, _viEnemy->x - 19, _viEnemy->y + 35, 0, 0, 50 * _viEnemy->currentHp / _viEnemy->maxHp, 10, _viEnemy->alpha);
		}
		if (_viEnemy->isPresent == true && _viEnemy->type == 2)
		{
			_minion[1]->alphaFrameRender(hdc, _viEnemy->x - 19, _viEnemy->y - 21, _frameIndex % _viEnemy->frameX, 0, _viEnemy->alpha);
			_hpBarBottom->alphaRender(hdc, _viEnemy->x - 34, _viEnemy->y + 22, _viEnemy->alpha);
			_hpBarTop->alphaRender(hdc, _viEnemy->x - 19, _viEnemy->y + 24, 0, 0, 50 * _viEnemy->currentHp / _viEnemy->maxHp, 10, _viEnemy->alpha);
		}
		if (_viEnemy->isPresent == true && _viEnemy->type == 3)
		{
			_minion[2]->alphaFrameRender(hdc, _viEnemy->x - 16, _viEnemy->y - 30, _frameIndex % _viEnemy->frameX, 0, _viEnemy->alpha);
			_hpBarBottom->alphaRender(hdc, _viEnemy->x - 34, _viEnemy->y + 31, _viEnemy->alpha);
			_hpBarTop->alphaRender(hdc, _viEnemy->x - 19, _viEnemy->y + 33, 0, 0, 50 * _viEnemy->currentHp / _viEnemy->maxHp, 10, _viEnemy->alpha);
		}
		if (_viEnemy->isPresent == true && _viEnemy->type == 130551)
		{
			if (_state == 0) _boss1Idle->alphaFrameRender(hdc, _viEnemy->x - 16, _viEnemy->y - 30, _frameIndex % _viEnemy->frameX, 0, _viEnemy->alpha);
			if (_state == 1) _boss1Attack->alphaFrameRender(hdc, _viEnemy->x - 48, _viEnemy->y - 51, _frameIndex2, 0, _viEnemy->alpha);
		}
		if (_viEnemy->isDead == true)
		{
			if (_viEnemy->frameEx >= 0 && _viEnemy->frameEx < 28) _explosion->frameRender(hdc, _viEnemy->x - 24, _viEnemy->y - 24, _viEnemy->frameEx, 0);
			if (_viEnemy->frameEx >= 20 && _viEnemy->frameEx < 48) _explosion->frameRender(hdc, _viEnemy->x - 14, _viEnemy->y - 14, _viEnemy->frameEx - 20, 0);
			if (_viEnemy->frameEx >= 40 && _viEnemy->frameEx < 68) _explosion->frameRender(hdc, _viEnemy->x - 34, _viEnemy->y - 34, _viEnemy->frameEx - 40, 0);
			if (_viEnemy->frameEx == 66) _viEnemy->item = RND->getInt(5);
			if (_viEnemy->item == 0) _im->setItem(_viEnemy->x, _viEnemy->y, true);
			_viEnemy->frameEx++;
			if (_viEnemy->frameEx == 68)
			{
				_viEnemy->isDead = false;
				_viEnemy->isPresent = false;
				_viEnemy->remove = true;
			}
		}
	}
	if (_vEnemy.size() > 0) bossHpSetting(hdc);
}

void enemyManager::setEnemy(float x, float y, float direction, int type)
{
	tagENEMY temp;
	temp.direction = direction;
	temp.frameEx = 0;
	temp.isPresent = true;
	temp.type = type;
	temp.x = x;
	temp.y = y;
	temp.count = 0;
	temp.bulletCount = 0;
	temp.alpha = 255;
	temp.isStop = false;
	temp.isFire = false;
	temp.onScreen = false;
	temp.isDead = false;
	temp.remove = false;
	switch (type)
	{
	case(1):
		temp.radius = 32;
		temp.maxHp = 1000;
		temp.currentHp = 1000;
		temp.frameX = 3;
		temp.speed = 3;
		break;
	case(2):
		temp.radius = 20;
		temp.maxHp = 1000;
		temp.currentHp = 1000;
		temp.frameX = 6;
		temp.speed = 3;
		break;
	case(3):
		temp.radius = 17;
		temp.maxHp = 1000;
		temp.currentHp = 1000;
		temp.frameX = 8;
		temp.speed = 4;
		break;
	case(130551):
		temp.radius = 35;
		temp.maxHp = 10;
		temp.currentHp = 10;
		temp.frameX = 4;
		temp.speed = 5;
		temp.stage = 0;
		temp.percent = 0;
		temp.pattern = 0;
		break;
	default:
		break;
	}
	_vEnemy.push_back(temp);
}

void enemyManager::move(void)
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		_viEnemy->count++;
		if (_viEnemy->currentHp <= 0 && _viEnemy->isPresent == true && _life > 0)
		{
			_life--;
			_viEnemy->currentHp = 1;
			_viEnemy->onScreen = false;
			_viEnemy->stage = 0;
			_viEnemy->isStop = false;
		}
		if (_viEnemy->currentHp <= 0 && _viEnemy->isPresent == true && _life == 0)
		{
			_viEnemy->currentHp = 0;
			_viEnemy->onScreen = false;
			_viEnemy->isDead = true;
			_viEnemy->isFire = false;
			if (_viEnemy->alpha > 0) _viEnemy->alpha -= 15;
		}
		if (_viEnemy->isPresent == true && _viEnemy->isStop == false)
		{
			_viEnemy->x += _viEnemy->speed * cosf(_viEnemy->direction);
			_viEnemy->y -= _viEnemy->speed * sinf(_viEnemy->direction);
		}
		switch (_viEnemy->type)
		{
		case(1):
			if (_viEnemy->y > 200) _viEnemy->isStop = true;
			if (_viEnemy->y > 0 && _viEnemy->x > 0 && _viEnemy->x < 750) _viEnemy->onScreen = true;
			if (_viEnemy->isStop == true && _viEnemy->count % 50 == 0 && _viEnemy->isDead == false && _viEnemy->isPresent == true)
			{
				_viEnemy->isFire = true;
			}
			if (_viEnemy->count > 300 && _viEnemy->isStop == true)
			{
				_viEnemy->direction -= PI;
				_viEnemy->isStop = false;
				_viEnemy->isFire = false;
			}
			if (_viEnemy->count > 500) _viEnemy->remove = true;
			break;
		case(2):
			if (_viEnemy->direction > PI / 2) _viEnemy->direction -= 0.005f;
			if (_viEnemy->direction < PI / 2) _viEnemy->direction += 0.005f;
			if (_viEnemy->y < 100) _viEnemy->isStop = true;
			if (_viEnemy->y > 0 && _viEnemy->x > 0 && _viEnemy->x < 750) _viEnemy->onScreen = true;
			if (_viEnemy->isStop == true && _viEnemy->count % 40 == 0 && _viEnemy->isDead == false && _viEnemy->isPresent == true)
			{
				_viEnemy->isFire = true;
			}
			if (_viEnemy->count > 300 && _viEnemy->isStop == true)
			{
				_viEnemy->direction = PI / 2;
				_viEnemy->isStop = false;
				_viEnemy->isFire = false;
			}
			if (_viEnemy->count > 500) _viEnemy->remove = true;
			break;
		case(3):
			if (_viEnemy->count > 100) _viEnemy->isStop = true;
			if (_viEnemy->y > 0 && _viEnemy->x > 0 && _viEnemy->x < 750) _viEnemy->onScreen = true;
			else _viEnemy->onScreen = false;
			if (_viEnemy->isStop == true && _viEnemy->isDead == false && _viEnemy->isPresent == true)
			{
				_viEnemy->isFire = true;
			}
			if (_viEnemy->isFire == true)
			{
				_viEnemy->bulletCount++;
			}
			if (_viEnemy->count > 300 && _viEnemy->isStop == true)
			{
				_viEnemy->bulletCount = 0;
				_viEnemy->isStop = false;
				_viEnemy->isFire = false;
			}
			if (_viEnemy->count > 500) _viEnemy->remove = true;
			break;
		case(130551):
			if (_viEnemy->currentHp > 59999)
			{
				_viEnemy->onScreen = true;
			}
			if (_viEnemy->stage == 0 && _viEnemy->isStop == false && _viEnemy->y > 200)
			{
				_viEnemy->x = 375;
				_viEnemy->y = 200;
				_viEnemy->isStop = true;
			}
			if (_viEnemy->stage == 0 && _viEnemy->isStop == true)
			{
				_viEnemy->count++;
				if (_viEnemy->count > 100)
				{
					_viEnemy->count = 0;
					_viEnemy->stage++;
					_viEnemy->isStop = false;
				}
			}
			if (_viEnemy->stage > 0 && _viEnemy->isStop == true)
			{
				_state = 1;
				_viEnemy->count++;
				if (_viEnemy->count % 30 == 0)
				{
					if (_frameIndex2 < 4) _frameIndex2++;
					_viEnemy->isFire = true;
				}
				if (_viEnemy->count > 300)
				{
					_frameIndex2 = 0;
					_viEnemy->count = 0;
					_viEnemy->isStop = false;
					_viEnemy->isFire = false;
					_state = 0;
				}
			}
			if (_viEnemy->stage > 0 && _viEnemy->isStop == false)
			{
				if (_viEnemy->stage == 1) bezier(375, 200, 375, 100, 475, 100, _viEnemy->percent);
				if (_viEnemy->stage == 2) bezier(475, 100, 575, 100, 575, 200, _viEnemy->percent);
				if (_viEnemy->stage == 3) bezier(575, 200, 575, 300, 475, 300, _viEnemy->percent);
				if (_viEnemy->stage == 4) bezier(475, 300, 375, 300, 375, 200, _viEnemy->percent);
				if (_viEnemy->stage == 5) bezier(375, 200, 375, 100, 275, 100, _viEnemy->percent);
				if (_viEnemy->stage == 6) bezier(275, 100, 175, 100, 175, 200, _viEnemy->percent);
				if (_viEnemy->stage == 7) bezier(175, 200, 175, 300, 275, 300, _viEnemy->percent);
				if (_viEnemy->stage == 8) bezier(275, 300, 375, 300, 375, 200, _viEnemy->percent);
				if (_viEnemy->stage >= 1)
				{
					_viEnemy->x = bezierX;
					_viEnemy->y = bezierY;
					_viEnemy->percent += 0.02f;
				}
				if (_viEnemy->percent >= 1)
				{
					_viEnemy->percent = 0;
					_viEnemy->stage++;
				}
				if (_viEnemy->stage == 9) _viEnemy->stage = 1;
				_viEnemy->count++;
				if (_viEnemy->count > 200)
				{
					_viEnemy->count = 0;
					if (_life == 1) _viEnemy->pattern = RND->getInt(3);
					if (_life == 0) _viEnemy->pattern = RND->getInt(3) + 3;
					//_viEnemy->stage = 0;
					_eBullet->setBulletCount();
					_viEnemy->isStop = true;
				}
			}
			break;
		default:
			break;
		}
	}
}

void enemyManager::setStage(void)
{
	if (_player->getIsDead() == false)
	{
		_count++;
		if (_count > 300 && _stage == 0)
		{
			setEnemy(150, -50, PI * 3 / 2, 1);
			_count = 0;
			_stage++;
		}
		if (_count > 300 && _stage == 1)
		{
			setEnemy(250, -50, PI * 3 / 2, 1);
			setEnemy(600, -50, PI * 3 / 2, 1);
			_count = 0;
			_stage++;
		}
		if (_count > 300 && _stage == 2)
		{
			setEnemy(-50, 200, 0, 2);
			setEnemy(750 + 50, 200, PI, 2);
			_count = 0;
			_stage++;
		}
		if (_count > 300 && _stage == 3)
		{
			setEnemy(-35, 150, 0, 3);
			_count = 0;
			_stage++;
		}
		if (_count > 300 && _stage == 4)
		{
			setEnemy(-50, 200, 0, 2);
			setEnemy(-100, 200, 0, 2);
			setEnemy(-150, 200, 0, 2);
			_count = 0;
			_stage++;
		}
		if (_count > 300 && _stage == 5)
		{
			setEnemy(-35, 100, 0, 3);
			setEnemy(750 + 35, 200, PI, 3);
			_count = 0;
			_stage++;
		}
		if (_count > 300 && _stage == 6)
		{
			setEnemy(150, -50, PI * 3 / 2, 1);
			setEnemy(250, -50, PI * 3 / 2, 1);
			setEnemy(350, -50, PI * 3 / 2, 1);
			setEnemy(450, -50, PI * 3 / 2, 1);
			_count = 0;
			_stage++;
		}
		if (_count > 300 && _stage == 7)
		{
			setEnemy(-50, 200, 0, 2);
			setEnemy(-50, 300, 0, 2);
			setEnemy(750 + 50, 200, PI, 2);
			setEnemy(750 + 50, 300, PI, 2);
			_count = 0;
			_stage++;
		}

		if (_count > 450 && _stage == 8)
		{
			_stage += 100;
		}
		if (_count > 300 && _stage == 108)
		{
			setEnemy(750 / 2, -100, PI * 3 / 2, 130551);
			_life++;
			_count = 0;
			_stage++;
		}
		if (_stage == 109)
		{
			if (_vEnemy[0].currentHp < 60000)
			{
				_vEnemy[0].currentHp += 1000;
				_vEnemy[0].maxHp += 1000;
			}
			if (_vEnemy[0].currentHp > 59999)
			{
				_stage++;
			}
		}
		if (_stage == 110 && _life == 0)
		{
			_eBullet->removeAllBullets();
			if (_vEnemy[0].currentHp < 60000)
			{
				_vEnemy[0].currentHp += 1000;
				_vEnemy[0].maxHp += 1000;
			}
			if (_vEnemy[0].currentHp > 59999)
			{
				_stage++;
			}
		}
		if (_stage == 111)
		{
			if (_vEnemy.size() == 0)
			{
				_count = 0;
				_stage++;
			}
		}
		if (_count > 200 && _stage == 112)
		{
			_gameOver = true;
		}
	}
}

void enemyManager::frameCount(void)
{
		_frameCount++;
		if (_frameCount % 30 == 0)
		{
			_frameIndex++;
			_frameCount = 0;
		}
		if (_frameIndex > 23) _frameIndex = 0;
	
}

void enemyManager::removeEnemy(void)
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		if (_vEnemy[i].remove == true)
		{
			_vEnemy.erase(_vEnemy.begin() + i);
		}
	}
}

void enemyManager::bossHpSetting(HDC hdc)
{
	if (_stage > 100)
	{
		HPEN newPen, oldPen;
		if (_life == 1) newPen = CreatePen(PS_SOLID, 10, RGB(255, 165, 0));
		if (_life == 0) newPen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, newPen);
		MoveToEx(hdc, 750 / 2, 50, NULL);
		LineTo(hdc, 750 / 2 + 300 * _vEnemy[0].currentHp / 100000, 50);
		MoveToEx(hdc, 750 / 2, 50, NULL);
		LineTo(hdc, 750 / 2 - 300 * _vEnemy[0].currentHp / 100000, 50);
		SelectObject(hdc, oldPen);
		DeleteObject(newPen);
	}
}

float enemyManager::getPt(float n1, float n2, float perc)
{
	float diff = n2 - n1;

	return n1 + (diff * perc);
}

void enemyManager::bezier(float x1, float y1, float x2, float y2, float x3, float y3, float i)
{
	float Xa, Xb, Ya, Yb;
	Xa = getPt(x1, x2, i);
	Ya = getPt(y1, y2, i);
	Xb = getPt(x2, x3, i);
	Yb = getPt(y2, y3, i);

	bezierX = getPt(Xa, Xb, i);
	bezierY = getPt(Ya, Yb, i);
}
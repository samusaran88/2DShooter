#include "stdafx.h"
#include "ItemManager.h"
#include "player.h"
#include "enemyManager.h"
#include "bulletManager.h"
#include "UI.h"


itemManager::itemManager()
{
}


itemManager::~itemManager()
{

}

HRESULT itemManager::init(void)	 
{
	_item[0] = IMAGEMANAGER->addImage("itemRed", ".\\images\\itemRed.bmp", 63, 57, true, RGB(255, 0, 255), true);
	_item[1] = IMAGEMANAGER->addImage("itemBlue", ".\\images\\itemBlue.bmp", 58, 60, true, RGB(255, 0, 255), true);
	_item[2] = IMAGEMANAGER->addImage("itemGreen", ".\\images\\itemGreen.bmp", 61, 52, true, RGB(255, 0, 255), true);
	_y = 0;
	_x = 750 / 2;
	_type = 0;
	_speed = -5;
	_isPresent = false;
	return S_OK;
}
void itemManager::release(void)	 
{

}
void itemManager::update(void)	 
{
	if (_y > WINSIZEY + 30)
	{
		_isPresent = false;
		_speed = -5;
	}
	if (_isPresent == true)
	{
		_y += _speed;
		_speed += 0.2f;
		if (_speed > 3) _speed = 3;
		if (getDistance(_player->getPlayerX(), _player->getPlayerY(), _x, _y) <= 51)
		{
			_isPresent = false;
			_pBullet->setBulletType(_type);
			_ui->setPlayerType(_type);
		}
	}
}
void itemManager::render(HDC hdc)
{
	if (_isPresent == true)
	{
		switch (_type)
		{
		case(0):
			IMAGEMANAGER->findImage("itemRed")->render(hdc, _x - 31, _y - 28);
			break;
		case(1):
			IMAGEMANAGER->findImage("itemBlue")->render(hdc, _x - 29, _y - 30);
			break;
		case(2):
			IMAGEMANAGER->findImage("itemGreen")->render(hdc, _x - 30, _y - 26);
			break;
		default:
			break;
		}
	}
}


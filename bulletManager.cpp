#include "stdafx.h"
#include "bulletManager.h"
#include "player.h"
#include "enemyManager.h"

//////////////////////
// ÇÃ·¹ÀÌ¾î ÃÑ¾Ë		//
//////////////////////

playerBullet::playerBullet()
{
}


playerBullet::~playerBullet()
{

}

HRESULT playerBullet::init(void)
{
	_redBullet = IMAGEMANAGER->addImage("redBullet", ".\\images\\redBullet.bmp", 21, 21, true, RGB(255, 0, 255), true);
	_blueBullet = IMAGEMANAGER->addImage("blueBullet", ".\\images\\blueBullet.bmp", 21, 21, true, RGB(255, 0, 255), true);
	_greenBullet = IMAGEMANAGER->addImage("greenBullet", ".\\images\\greenBullet.bmp", 21, 21, true, RGB(255, 0, 255), true);
	_redBulletExplode = IMAGEMANAGER->addFrameImage("redBulletExplode", ".\\images\\redBulletExplode.bmp", 124, 31, 4, 1, true, RGB(255, 0, 255), true);
	_blueBulletExplode = IMAGEMANAGER->addFrameImage("blueBulletExplode", ".\\images\\blueBulletExplode.bmp", 124, 31, 4, 1, true, RGB(255, 0, 255), true);
	_greenBulletExplode = IMAGEMANAGER->addFrameImage("greenBulletExplode", ".\\images\\greenBulletExplode.bmp", 124, 31, 4, 1, true, RGB(255, 0, 255), true);
	_bulletType = RED;
	_counter = 5;
	_bulletCount = 0;
	for (int i = 0; i < 80; i++)
	{
		tagBULLET tempBullet;
		ZeroMemory(&tempBullet, sizeof(tempBullet));
		tempBullet.count = 0;
		tempBullet.frame = 0;
		tempBullet.directionAngle = PI / 2;
		tempBullet.spinAngle = PI;
		tempBullet.x = 0;
		tempBullet.y = 0;
		tempBullet.radius = 10;
		tempBullet.speed = 10;
		tempBullet.damage = 50;
		tempBullet.type = _bulletType;
		tempBullet.isFire = false;
		tempBullet.isDestroyed = true;
		_vPlayerBullet.push_back(tempBullet);
	}
	return S_OK;
}

void playerBullet::release(void)
{

}

void playerBullet::update(void)
{
	_counter++;
	pBulletSetting();
	pBulletMove();
	pBulletCollision();
}

void playerBullet::render(HDC hdc)
{
	for (_viPlayerBullet = _vPlayerBullet.begin(); _viPlayerBullet != _vPlayerBullet.end(); ++_viPlayerBullet)
	{
		if (_viPlayerBullet->isFire == true && _viPlayerBullet->isDestroyed == false)
		{
			switch (_viPlayerBullet->type)
			{
			case(RED):
				_redBullet->render(hdc, _viPlayerBullet->x - 10, _viPlayerBullet->y - 10);
				break;
			case(BLUE):
				_blueBullet->render(hdc, _viPlayerBullet->x - 10, _viPlayerBullet->y - 10);
				break;
			case(GREEN):
				_greenBullet->render(hdc, _viPlayerBullet->x - 10, _viPlayerBullet->y - 10);
				break;
			default:
				break;
			}
		}
		else if (_viPlayerBullet->isFire == false && _viPlayerBullet->isDestroyed == false)
		{
			switch (_viPlayerBullet->type)
			{
			case(RED):
				_redBulletExplode->frameRender(hdc, _viPlayerBullet->x - 15, _viPlayerBullet->y - 15, _viPlayerBullet->frame, 0);
				break;
			case(BLUE):
				_blueBulletExplode->frameRender(hdc, _viPlayerBullet->x - 15, _viPlayerBullet->y - 15, _viPlayerBullet->frame, 0);
				break;
			case(GREEN):
				_greenBulletExplode->frameRender(hdc, _viPlayerBullet->x - 15, _viPlayerBullet->y - 15, _viPlayerBullet->frame, 0);
				break;
			default:
				break;
			}
			_viPlayerBullet->count++;
			if (_viPlayerBullet->count % 10 == 0) _viPlayerBullet->frame++;
			if (_viPlayerBullet->frame > 3)
			{
				_viPlayerBullet->frame = 0;
				_viPlayerBullet->count = 0;
				_viPlayerBullet->isDestroyed = true;
			}
		}
	}
}

void playerBullet::pBulletMove(void)
{
	for (_viPlayerBullet = _vPlayerBullet.begin(); _viPlayerBullet != _vPlayerBullet.end(); ++_viPlayerBullet)
	{
		if (_viPlayerBullet->isFire == true && _viPlayerBullet->type == RED)
		{
			_viPlayerBullet->x += _viPlayerBullet->speed * cosf(_viPlayerBullet->directionAngle);
			_viPlayerBullet->y -= _viPlayerBullet->speed * sinf(_viPlayerBullet->directionAngle);
		}
		if (_viPlayerBullet->isFire == true && _viPlayerBullet->type == BLUE)
		{
			_viPlayerBullet->x += _viPlayerBullet->speed * cosf(_viPlayerBullet->directionAngle);
			_viPlayerBullet->y -= _viPlayerBullet->speed * sinf(_viPlayerBullet->directionAngle);
		}
		if (_viPlayerBullet->isFire == true && _viPlayerBullet->type == GREEN)
		{
			for (int i = 0; i < _em->getVEnemy().size(); i++)
			{
				if (_em->getVEnemy()[i].onScreen == true)
				{
					_viPlayerBullet->directionAngle = getAngle(_viPlayerBullet->x, _viPlayerBullet->y, _em->getVEnemy()[i].x, _em->getVEnemy()[i].y);
					break;
				}
				else
				{
					_viPlayerBullet->directionAngle = PI / 2;
					break;
				}
			}
			_viPlayerBullet->x += _viPlayerBullet->speed * cosf(_viPlayerBullet->directionAngle);
			_viPlayerBullet->y -= _viPlayerBullet->speed * sinf(_viPlayerBullet->directionAngle);
		}
		if (_viPlayerBullet->y < -10 || _viPlayerBullet->x > 760 || _viPlayerBullet->x < -10 || _viPlayerBullet->y > 760)
		{
			_viPlayerBullet->isFire = false;
			_viPlayerBullet->isDestroyed = true;
			_viPlayerBullet->spinAngle = PI;
		}
	}
}

void playerBullet::pBulletSetting(void)
{
	if (_player->getIsFire() && _counter > 2 && _bulletType == RED)
	{
		for (_viPlayerBullet = _vPlayerBullet.begin(); _viPlayerBullet != _vPlayerBullet.end();)
		{
			if (_viPlayerBullet->isFire == false && _viPlayerBullet->isDestroyed == true)
			{
				_viPlayerBullet->x = _player->getPlayerX() + (_bulletCount * 2 - 1) * 10;
				_viPlayerBullet->y = _player->getPlayerY() - 25;
				_viPlayerBullet->speed = 10;
				_viPlayerBullet->type = RED;
				_viPlayerBullet->directionAngle = PI / 2;
				_viPlayerBullet->damage = 100;
				_viPlayerBullet->isFire = true;
				_viPlayerBullet->isDestroyed = false;
				_bulletCount++;
				if (_bulletCount == 2)
				{
					_counter = 0;
					_bulletCount = 0;
					break;
				}
			}
			else  ++_viPlayerBullet;
		}
	}
	if (_player->getIsFire() && _counter > 6 && _bulletType == BLUE)
	{
		for (_viPlayerBullet = _vPlayerBullet.begin(); _viPlayerBullet != _vPlayerBullet.end();)
		{
			if (_viPlayerBullet->isFire == false && _viPlayerBullet->isDestroyed == true)
			{
				_viPlayerBullet->x = _player->getPlayerX();
				_viPlayerBullet->y = _player->getPlayerY();
				_viPlayerBullet->speed = 5;
				_viPlayerBullet->directionAngle = PI / 2 + (_bulletCount - 1) * PI / 6;
				_viPlayerBullet->type = BLUE;
				_viPlayerBullet->damage = 300;
				_viPlayerBullet->isFire = true;
				_viPlayerBullet->isDestroyed = false;
				_bulletCount++;
				if (_bulletCount == 3)
				{
					_counter = 0;
					_bulletCount = 0;
					break;
				}
			}
			else  ++_viPlayerBullet;
		}
	}
	if (_player->getIsFire() && _counter > 3 && _bulletType == GREEN)
	{
		for (_viPlayerBullet = _vPlayerBullet.begin(); _viPlayerBullet != _vPlayerBullet.end();)
		{
			if (_viPlayerBullet->isFire == false && _viPlayerBullet->isDestroyed == true)
			{
				_viPlayerBullet->x = _player->getPlayerX();
				_viPlayerBullet->y = _player->getPlayerY();
				_viPlayerBullet->speed = 8;
				_viPlayerBullet->type = GREEN;
				_viPlayerBullet->directionAngle = PI / 2;
				_viPlayerBullet->damage = 100;
				_viPlayerBullet->isFire = true;
				_viPlayerBullet->isDestroyed = false;
				_counter = 0;
				break;
			}
			else ++_viPlayerBullet;
		}
	}
}

void playerBullet::pBulletCollision(void)
{
	for (_viPlayerBullet = _vPlayerBullet.begin(); _viPlayerBullet != _vPlayerBullet.end(); ++_viPlayerBullet)
	{
		for (int i = 0; i < _em->getVEnemy().size(); i++)
		{
			if (_viPlayerBullet->isFire == true)
			{
				if (getDistance(_viPlayerBullet->x, _viPlayerBullet->y, _em->getVEnemy()[i].x, _em->getVEnemy()[i].y) < _viPlayerBullet->radius + _em->getVEnemy()[i].radius &&
					_em->getVEnemy()[i].isDead == false &&
					_em->getVEnemy()[i].isPresent == true && 
					_em->getVEnemy()[i].onScreen == true)
				{
					_em->setVEnemyHp(_viPlayerBullet->damage, i);
					_viPlayerBullet->isFire = false;
				}
			}
		}
	}
}

//////////////////
//	Àû ÃÑ¾Ë		//											
//////////////////

enemyBullet::enemyBullet() 
{

}

enemyBullet::~enemyBullet()
{

}

HRESULT enemyBullet::init(void)
{
	_yellowBullet = IMAGEMANAGER->addImage("yellowBullet", ".\\images\\yellowBullet.bmp", 21, 21, true, RGB(255, 0, 255), true);
	_purpleBullet = IMAGEMANAGER->addImage("purpleBullet", ".\\images\\purpleBullet.bmp", 21, 21, true, RGB(255, 0, 255), true);
	_damageImage = IMAGEMANAGER->addImage("damage", ".\\images\\damage.bmp", 750, 750, true, RGB(255, 0, 255), true);
	for (int i = 0; i < 500; i++)
	{
		tagBULLET tempBullet;
		ZeroMemory(&tempBullet, sizeof(tempBullet));
		tempBullet.directionAngle = PI * 3 / 2;
		tempBullet.spinAngle = PI;
		tempBullet.x = 0;
		tempBullet.y = 0;
		tempBullet.count = 0;
		tempBullet.radius = 10;
		tempBullet.speed = 9;
		tempBullet.damage = 5;
		tempBullet.type = YELLOW;
		tempBullet.type2 = 0;
		tempBullet.isFire = false;
		_vEnemyBullet.push_back(tempBullet);
	}
	_bulletCount = 0;
	_bulletCount2 = 0;
	_damage = 0;
	_tempX = RND->getInt(550);
	_tempY = RND->getInt(200);
	return S_OK;
}

void enemyBullet::release(void)
{

}

void enemyBullet::update(void)
{
	eBulletSetting();
	eBulletMove();
	eBulletCollision();
}

void enemyBullet::render(HDC hdc)
{
	for (_viEnemyBullet = _vEnemyBullet.begin(); _viEnemyBullet != _vEnemyBullet.end(); ++_viEnemyBullet)
	{
		if (_viEnemyBullet->isFire == true)
		{
			switch (_viEnemyBullet->type)
			{
			case(YELLOW):
				_yellowBullet->render(hdc, _viEnemyBullet->x - 10, _viEnemyBullet->y - 10);
				break;
			case(PURPLE):
				_purpleBullet->render(hdc, _viEnemyBullet->x - 10, _viEnemyBullet->y - 10);
				break;
			default:
				break;
			}
		}
	}
	if (_damage > 0)
	{
		_damageImage->alphaRender(hdc, 0, 0, _damage);
		_damage -= 15;
		if (_damage < 0) _damage = 0;
	}
}

void enemyBullet::eBulletMove(void)
{
	for (_viEnemyBullet = _vEnemyBullet.begin(); _viEnemyBullet != _vEnemyBullet.end(); ++_viEnemyBullet)
	{
		if (_viEnemyBullet->count == 1 && _viEnemyBullet->type2 == 1) _viEnemyBullet->directionAngle = getAngle(_viEnemyBullet->x, _viEnemyBullet->y, _player->getPlayerX(), _player->getPlayerY());
		if (_viEnemyBullet->count == 0 && _viEnemyBullet->type2 < 5)
		{
			if (_viEnemyBullet->isFire == true)
			{
				_viEnemyBullet->x += _viEnemyBullet->speed * cosf(_viEnemyBullet->directionAngle);
				_viEnemyBullet->y -= _viEnemyBullet->speed * sinf(_viEnemyBullet->directionAngle);
				if (_viEnemyBullet->speed > 2) _viEnemyBullet->speed -= 0.1f;
			}
			if (_viEnemyBullet->type2 == 2) _viEnemyBullet->directionAngle += 0.005;
			if (_viEnemyBullet->type2 == 3) _viEnemyBullet->directionAngle -= 0.005;
			if (_viEnemyBullet->type2 == 4) _viEnemyBullet->speed += 0.2;
			if (_viEnemyBullet->y > WINSIZEY + 10 || _viEnemyBullet->y < -10 || _viEnemyBullet->x > 750 + 10 || _viEnemyBullet->x < -10)
			{
				_viEnemyBullet->isFire = false;
			}
		}
		if (_viEnemyBullet->count > 0 && _viEnemyBullet->type2 < 5) _viEnemyBullet->count--;
		if (_viEnemyBullet->type2 >= 5)
		{
			_viEnemyBullet->count++;
			if (_viEnemyBullet->isFire == true && _viEnemyBullet->count < 50)
			{
				_viEnemyBullet->x += _viEnemyBullet->speed * cosf(_viEnemyBullet->directionAngle);
				_viEnemyBullet->y -= _viEnemyBullet->speed * sinf(_viEnemyBullet->directionAngle);
				if (_viEnemyBullet->speed > 2) _viEnemyBullet->speed -= 0.1f;
			}
			if (_viEnemyBullet->isFire == true && _viEnemyBullet->count == 50)
			{
				if (_viEnemyBullet->type2 == 6) _viEnemyBullet->directionAngle -= PI;
			}
			if (_viEnemyBullet->isFire == true && _viEnemyBullet->count > 100)
			{
				_viEnemyBullet->x += _viEnemyBullet->speed * cosf(_viEnemyBullet->directionAngle);
				_viEnemyBullet->y -= _viEnemyBullet->speed * sinf(_viEnemyBullet->directionAngle);
				if (_viEnemyBullet->speed > 2) _viEnemyBullet->speed -= 0.1f;
			}
			if (_viEnemyBullet->type2 == 5) _viEnemyBullet->directionAngle -= 0.005;
			if (_viEnemyBullet->type2 == 6) _viEnemyBullet->directionAngle -= 0.005;
			if (_viEnemyBullet->y > WINSIZEY + 10 || _viEnemyBullet->y < -10 || _viEnemyBullet->x > 750 + 10 || _viEnemyBullet->x < -10)
			{
				_viEnemyBullet->isFire = false;
			}
		}
	}
}

void enemyBullet::eBulletSetting(void)
{
	for (int i = 0; i < _em->getVEnemy().size(); i++)
	{
		if (_em->getVEnemy()[i].isFire == true && _em->getVEnemy()[i].isDead == false)
		{
			switch (_em->getVEnemy()[i].type)
			{
			case(1):
				for (_viEnemyBullet = _vEnemyBullet.begin(); _viEnemyBullet != _vEnemyBullet.end(); ++_viEnemyBullet)
				{
					if (_viEnemyBullet->isFire == false)
					{
						_viEnemyBullet->type2 = 0;
						_viEnemyBullet->type2 = 0;
						_viEnemyBullet->count = 0;
						_viEnemyBullet->x = _em->getVEnemy()[i].x;
						_viEnemyBullet->y = _em->getVEnemy()[i].y;
						_viEnemyBullet->speed = 9;
						_viEnemyBullet->damage = 5;
						_viEnemyBullet->directionAngle = getAngle(_viEnemyBullet->x, _viEnemyBullet->y, _player->getPlayerX(), _player->getPlayerY());
						_em->setVEnemyFire(false, i);
						_viEnemyBullet->isFire = true;
						break;
					}
				}
				break;
			case(2):
				for (_viEnemyBullet = _vEnemyBullet.begin(); _viEnemyBullet != _vEnemyBullet.end(); ++_viEnemyBullet)
				{
					if (_viEnemyBullet->isFire == false)
					{
						_viEnemyBullet->type = YELLOW;
						_viEnemyBullet->type2 = 0;
						_viEnemyBullet->count = 0;
						_viEnemyBullet->x = _em->getVEnemy()[i].x;
						_viEnemyBullet->y = _em->getVEnemy()[i].y;
						_viEnemyBullet->speed = 9;
						_viEnemyBullet->damage = 5;
						_viEnemyBullet->directionAngle = getAngle(_viEnemyBullet->x, _viEnemyBullet->y, _player->getPlayerX(), _player->getPlayerY()) + PI / 6 * (_bulletCount - 1);
						_em->setVEnemyFire(false, i);
						_viEnemyBullet->isFire = true;
						_bulletCount++;
					}
					if (_bulletCount > 2)
					{
						_bulletCount = 0;
						break;
					}
				}
				break;
			case(3):
				for (_viEnemyBullet = _vEnemyBullet.begin(); _viEnemyBullet != _vEnemyBullet.end(); ++_viEnemyBullet)
				{
					if (_viEnemyBullet->isFire == false && _em->getVEnemy()[i].bulletCount % 3 == 0)
					{
						_viEnemyBullet->type = YELLOW;
						_viEnemyBullet->type2 = 0;
						_viEnemyBullet->count = 0;
						_viEnemyBullet->x = _em->getVEnemy()[i].x;
						_viEnemyBullet->y = _em->getVEnemy()[i].y;
						_viEnemyBullet->speed = 9;
						_viEnemyBullet->damage = 5;
						_viEnemyBullet->directionAngle = PI + _em->getVEnemy()[i].bulletCount / 3 * PI / 18; 
						_viEnemyBullet->isFire = true;
						break;
					}
				}
				break;
			case(130551):
				switch (_em->getVEnemy()[i].pattern)
				{
				case(0):
					for (_viEnemyBullet = _vEnemyBullet.begin(); _viEnemyBullet != _vEnemyBullet.end(); ++_viEnemyBullet)
					{
						if (_viEnemyBullet->isFire == false)
						{
							_viEnemyBullet->type = YELLOW;
							_viEnemyBullet->type2 = 0;
							_viEnemyBullet->count = 0;
							_viEnemyBullet->x = 100 + _tempX;//_em->getVEnemy()[i].x;
							_viEnemyBullet->y = 50 + _tempY;//_em->getVEnemy()[i].y;
							_viEnemyBullet->speed = 9;
							_viEnemyBullet->damage = 5;
							_viEnemyBullet->directionAngle = PI / 20 * _bulletCount + PI / 72 * _bulletCount2;
							_viEnemyBullet->isFire = true;
							_bulletCount++;
						}
						if (_bulletCount > 39)
						{
							_tempX = RND->getInt(550);
							_tempY = RND->getInt(200);
							_bulletCount = 0;
							_bulletCount2++;
							if (_bulletCount2 > 71) _bulletCount2 = 0;
							_em->setVEnemyFire(false, i);
							break;
						}
					}
					break;
				case(1):
					for (_viEnemyBullet = _vEnemyBullet.begin(); _viEnemyBullet != _vEnemyBullet.end(); ++_viEnemyBullet)
					{
						if (_viEnemyBullet->isFire == false)
						{
							_viEnemyBullet->type = YELLOW;
							_viEnemyBullet->type2 = 0;
							_viEnemyBullet->count = 0;
							_viEnemyBullet->x = _em->getVEnemy()[i].x;
							_viEnemyBullet->y = _em->getVEnemy()[i].y;
							_viEnemyBullet->speed = 9;
							_viEnemyBullet->damage = 5;
							_viEnemyBullet->directionAngle = PI / 2 + (_bulletCount * 2 - 1) * PI / 137 * _bulletCount2;
							_viEnemyBullet->isFire = true;
							_bulletCount++;
						}
						if (_bulletCount > 1)
						{
							_bulletCount = 0;
							_bulletCount2++;
							break;
						}
					}
					break;
				case(2):
					for (_viEnemyBullet = _vEnemyBullet.begin(); _viEnemyBullet != _vEnemyBullet.end(); ++_viEnemyBullet)
					{
						if (_viEnemyBullet->isFire == false)
						{
							_viEnemyBullet->type = YELLOW;
							_viEnemyBullet->type2 = 1;
							_viEnemyBullet->x = _em->getVEnemy()[i].x + 150 * cosf(PI * 3 / 2 + (_bulletCount * 2 - 1) * PI / 20 * _bulletCount2);
							_viEnemyBullet->y = _em->getVEnemy()[i].y - 150 * sinf(PI * 3 / 2 + (_bulletCount * 2 - 1) * PI / 20 * _bulletCount2);
							_viEnemyBullet->speed = 12;
							_viEnemyBullet->damage = 10;
							_viEnemyBullet->directionAngle = PI / 2 + (_bulletCount * 2 - 1) * PI / 138 * _bulletCount2;
							_viEnemyBullet->count = 100;
							_viEnemyBullet->isFire = true;
							_bulletCount++;
						}
						if (_bulletCount > 1)
						{
							_bulletCount = 0;
							_bulletCount2++;
							_em->setVEnemyFire(false, i);
							break;
						}
					}
					break;
				case(3):
					for (_viEnemyBullet = _vEnemyBullet.begin(); _viEnemyBullet != _vEnemyBullet.end(); ++_viEnemyBullet)
					{
						if (_viEnemyBullet->isFire == false)
						{
							_viEnemyBullet->type = PURPLE;
							if (_bulletCount2 == 0) _viEnemyBullet->type2 = 2;
							if (_bulletCount2 == 1) _viEnemyBullet->type2 = 3;
							_viEnemyBullet->count = 0;
							_viEnemyBullet->x = _em->getVEnemy()[i].x;
							_viEnemyBullet->y = _em->getVEnemy()[i].y;
							_viEnemyBullet->speed = 9;
							_viEnemyBullet->damage = 10;
							_viEnemyBullet->directionAngle = PI * 3 / 2 + (_bulletCount2 * 2 - 1) * PI / 20 * _bulletCount;
							_viEnemyBullet->isFire = true;
							_bulletCount++;
						}
						if (_bulletCount > 19)
						{
							_bulletCount = 0;
							_bulletCount2++;
							if (_bulletCount2 > 1) _bulletCount2 = 0;
							_em->setVEnemyFire(false, i);
							break;
						}
					}
					break;
				case(4):
					for (_viEnemyBullet = _vEnemyBullet.begin(); _viEnemyBullet != _vEnemyBullet.end(); ++_viEnemyBullet)
					{
						if (_viEnemyBullet->isFire == false)
						{
							_viEnemyBullet->type = PURPLE;
							_viEnemyBullet->type2 = 4;
							_viEnemyBullet->count = 0;
							_viEnemyBullet->x = 100 + _tempX;//_em->getVEnemy()[i].x;
							_viEnemyBullet->y = 50; //_em->getVEnemy()[i].y;
							_viEnemyBullet->speed = 9 - _bulletCount2;
							_viEnemyBullet->damage = 10;
							_viEnemyBullet->directionAngle = getAngle(_viEnemyBullet->x, _viEnemyBullet->y, _player->getPlayerX(), _player->getPlayerY()) + PI / 8 * (_bulletCount - 1);
							_em->setVEnemyFire(false, i);
							_viEnemyBullet->isFire = true;
							_bulletCount++;
						}
						if (_bulletCount > 2)
						{
							_bulletCount = 0;
							_bulletCount2++;
						}
						if (_bulletCount2 > 8)
						{
							_tempX = RND->getInt(550);
							_tempY = RND->getInt(200);
							_bulletCount2 = 0;
							_em->setVEnemyFire(false, i);
							break;
						}
					}
					break;
				case(5):
					if (_bulletCount2 % 5 == 0)
					{
						for (_viEnemyBullet = _vEnemyBullet.begin(); _viEnemyBullet != _vEnemyBullet.end(); ++_viEnemyBullet)
						{
							if (_viEnemyBullet->isFire == false)
							{
								_viEnemyBullet->type = PURPLE;
								if ((_bulletCount2 / 5) % 2 == 0) _viEnemyBullet->type2 = 5;
								if ((_bulletCount2 / 5) % 2 == 1) _viEnemyBullet->type2 = 6;
								_viEnemyBullet->count = 0;
								_viEnemyBullet->x = _em->getVEnemy()[i].x;
								_viEnemyBullet->y = _em->getVEnemy()[i].y;
								_viEnemyBullet->speed = 9;
								_viEnemyBullet->damage = 10;
								_viEnemyBullet->directionAngle = PI * 2 / 5 * _bulletCount + PI / 36 * (_bulletCount2 / 5);
								_viEnemyBullet->isFire = true;
								_bulletCount++;
							}
							if (_bulletCount > 4)
							{
								_bulletCount = 0;
								break;
							}
						}
					}
					_bulletCount2++;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
	}
}

void enemyBullet::eBulletCollision(void)
{
	if (_player->getIsDead() == false && _player->getInvincibility() == false)
	{
		for (_viEnemyBullet = _vEnemyBullet.begin(); _viEnemyBullet != _vEnemyBullet.end(); ++_viEnemyBullet)
		{
			if (_viEnemyBullet->isFire == true)
			{
				if (getDistance(_viEnemyBullet->x, _viEnemyBullet->y, _player->getPlayerX(), _player->getPlayerY()) < 16)
				{
					_player->setPlayerHp();
					_damage = 150;
					_viEnemyBullet->isFire = false;
				}
			}
		}
	}
}

void enemyBullet::removeAllBullets(void)
{
	for (_viEnemyBullet = _vEnemyBullet.begin(); _viEnemyBullet != _vEnemyBullet.end(); ++_viEnemyBullet)
	{
		_viEnemyBullet->count = 0;
		_viEnemyBullet->type2 = 0;
		_viEnemyBullet->isFire = false;
	}
}
#include "stdafx.h"
#include "player.h"


player::player()
{
}


player::~player()
{

}

HRESULT player::init(void)	
{
	_arleIdle = IMAGEMANAGER->addFrameImage("arleIdle", ".\\images\\ArleNadjaIdle.bmp", 204, 78, 4, 1, true, RGB(255, 0, 255), true);
	_arleLeft = IMAGEMANAGER->addFrameImage("arleLeft", ".\\images\\ArleNadjaLeft.bmp", 204, 78, 4, 1, true, RGB(255, 0, 255), true);
	_arleRight = IMAGEMANAGER->addFrameImage("arleRight", ".\\images\\ArleNadjaRight.bmp", 204, 78, 4, 1, true, RGB(255, 0, 255), true);
	_carbuncle = IMAGEMANAGER->addFrameImage("carbuncle", ".\\images\\carbuncle.bmp", 1152, 32, 48, 1, true, RGB(255, 0, 255), true);
	_hitBox = IMAGEMANAGER->addImage("hitBox", ".\\images\\hitbox.bmp", 21, 21, true, RGB(255, 0, 255), true);
	_hpBarTop = IMAGEMANAGER->addImage("hpBarTop", ".\\images\\hpbartop.bmp", 50, 10, true, RGB(255, 0, 255), true);
	_hpBarBottom = IMAGEMANAGER->addImage("hpBarBottom", ".\\images\\hpbarbottom.bmp", 69, 14, true, RGB(255, 0, 255), true);
	_arleLost = IMAGEMANAGER->addFrameImage("arleLost", ".\\images\\ArleNadjaLost.bmp", 112, 59, 2, 1, true, RGB(255, 0, 255), true);
	_playerX = 750 / 2;
	_playerY = WINSIZEY - 100;
	_carbuncleFrame = 0;
	_carbuncleSpeed = 3;
	_carbuncleAngle = 0;
	_carbuncleX = 750 / 2 - 60;
	_carbuncleY = WINSIZEY - 100;
	_radius = 10;
	_counter = 0;
	_alphaCounter = 0;
	_frame = 0;
	_arleAlpha = 255;
	_alphaControl = 1;
	_hitBoxAlpha = 0;
	_focusMode = false;
	_playerDirection = UP;
	_isFire = false;
	_maxHp = 300;
	_currentHp = 300;
	_isDead = false;
	_canFire = true;
	_invincibility = false;
	_life = 3;
	_gameOver = false;
	return S_OK;
}

void player::release(void)	
{

}

void player::update(void)	
{
	counter();
	if (_canFire == true)
	{
		control();
	}
	carbuncle();
	playerDead();
	
}

void player::render(HDC hdc)
{
	if (_currentHp > 0)
	{
		if (_playerDirection == UP) _arleIdle->alphaFrameRender(hdc, _playerX - 25, _playerY - 46, _frame, 0, _arleAlpha);
		else if (_playerDirection == LEFT) _arleLeft->alphaFrameRender(hdc, _playerX - 25, _playerY - 46, _frame, 0, _arleAlpha);
		else if (_playerDirection == RIGHT) _arleRight->alphaFrameRender(hdc, _playerX - 25, _playerY - 46, _frame, 0, _arleAlpha);
	}
	else if (_isDead == true)
	{
		_arleLost->alphaFrameRender(hdc, _playerX - 28, _playerY - 29, _frame, 0, 255);
	}
	_carbuncle->alphaFrameRender(hdc, _carbuncleX - 12, _carbuncleY - 16, _carbuncleFrame, 0, 255);
	_hitBox->alphaRender(hdc, _playerX - 10, _playerY - 10, _hitBoxAlpha);
	_hpBarBottom->alphaRender(hdc, _playerX - 34, _playerY + 33, 255);
	_hpBarTop->alphaRender(hdc, _playerX - 19, _playerY + 35, 0, 0, 50 * _currentHp / _maxHp, 10, 255);
}

void player::counter(void)
{
	_counter++;
	if (_counter % 10 == 0 && _isDead == false)
	{
		_frame++;
		if (_frame > 3) _frame = 0;
	}
	if (_counter % 5 == 0)
	{
		_carbuncleFrame++;
		if (_carbuncleFrame > 47) _carbuncleFrame = 0;
	}
	if (_counter % 40 == 0 && _isDead == true)
	{
		_frame = 1;
	}
	if (_counter >= 40) _counter = 0;
}

void player::control(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _playerX >= 26 && _playerDirection != RIGHT)
	{
		_playerX -= 5;
		if (_focusMode == true) _playerX += 2;
		_playerDirection = LEFT;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _playerX <= 750 - 26 && _playerDirection != LEFT)
	{
		_playerX += 5;
		if (_focusMode == true) _playerX -= 2;
		_playerDirection = RIGHT;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_playerDirection = UP;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_playerDirection = UP;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _playerY >= 47)
	{
		_playerY -= 5;
		if (_focusMode == true) _playerY += 2;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _playerY <= WINSIZEY - 46)
	{
		_playerY += 5;
		if (_focusMode == true) _playerY -= 2;
	}
	if (KEYMANAGER->isStayKeyDown(VK_SHIFT))
	{
		_focusMode = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_SHIFT))
	{
		_focusMode = false;
	}
	if (KEYMANAGER->isStayKeyDown('Z'))
	{
		_isFire = true;
	}
	if (KEYMANAGER->isOnceKeyUp('Z'))
	{
		_isFire = false;
	}
	if (_focusMode == true && _arleAlpha > 150)
	{
		_arleAlpha -= 6;
		_hitBoxAlpha += 12;
	}
	else if (_focusMode == false && _arleAlpha < 255)
	{
		_arleAlpha += 6;
		_hitBoxAlpha -= 12;
	}
}

void player::carbuncle(void)
{
	if (getDistance(_playerX, _playerY, _carbuncleX, _carbuncleY) > 60)
	{
		_carbuncleAngle = getAngle(_carbuncleX, _carbuncleY, _playerX, _playerY) + RND->getFromFloatTo(-0.5, 0.5);
		_carbuncleSpeed += 0.01;
	}
	else
	{
		if (_carbuncleSpeed > 3) _carbuncleSpeed -= 0.01;
	}
	_carbuncleX += _carbuncleSpeed * cosf(_carbuncleAngle);
	_carbuncleY -= _carbuncleSpeed * sinf(_carbuncleAngle);
}

void player::playerDead(void)
{
	if (_currentHp <= 0 && _isDead == false)
	{
		_isDead = true;
		_canFire = false;
		_isFire = false;
		_focusMode = false;
		_counter = 0;
		_frame = 0;
		_life--;
	}
	if (_isDead == true && _currentHp <= 0)
	{
		if (_playerY < WINSIZEY + 100) _playerY += 3;
		else if (_life >= 0) _currentHp = _maxHp;
		else if (_life < 0) _gameOver = true;
	}
	if (_currentHp > 0 && _isDead == true)
	{
		_playerY -= 3;
		if (_playerY < WINSIZEY - 100)
		{
			_canFire = true;
			_invincibility = true;
			_isDead = false;
		}
	}
	if (_invincibility == true)
	{
		_alphaCounter++;
		if (_arleAlpha > 250) _alphaControl = -1;
		if (_arleAlpha < 5) _alphaControl = 1;
		_arleAlpha += _alphaControl * 15;
		if (_alphaCounter > 204)
		{
			_focusMode = false;
			_arleAlpha = 255;
			_hitBoxAlpha = 0;
			_alphaCounter = 0;
			_invincibility = false;
		}
	}
}
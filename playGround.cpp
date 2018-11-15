#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{

}


playGround::~playGround()
{

}

HRESULT playGround::init()
{
	gameNode::init(true);

	_gameStart = false;
	_gameOver = false;
	_alpha1 = 255;
	_gameOverImage = IMAGEMANAGER->addImage("gameOver", ".\\images\\gameover.bmp", 1000, 750, true, RGB(255, 0, 255), true);
	_ending = IMAGEMANAGER->addImage("ending", ".\\images\\ending.bmp", 1000, 750, true, RGB(255, 0, 255), true);
	_bg = new background;
	_bg->init();
	_player = new player;
	_player->init();
	_pBullet = new playerBullet;
	_pBullet->init();
	_em = new enemyManager;
	_em->init();
	_eBullet = new enemyBullet;
	_eBullet->init();
	_im = new itemManager;
	_im->init();
	_ui = new UI;
	_ui->init();

	_pBullet->setPlayerMemoryAddressLink(_player);
	_pBullet->setEnemyManagerMemoryAddressLink(_em);
	_eBullet->setPlayerMemoryAddressLink(_player);
	_eBullet->setEnemyManagerMemoryAddressLink(_em);
	_im->setEnemyManagerMemoryAddressLink(_em);
	_im->setPlayerMemoryAddressLink(_player);
	_im->setPlayerBulletMemoryAddressLink(_pBullet);
	_im->setUIMemoryAddressLink(_ui);
	_em->setEnemyBulletMemoryAddressLink(_eBullet);
	_em->setPlayerMemoryAddressLink(_player);
	_em->setItemManagerAddressLink(_im);
	_ui->setPlayerMemoryAddressLink(_player);
	return S_OK;
}

//메모리 관련 삭제
void playGround::release(void)
{
	gameNode::release();

}

//연산
void playGround::update(void)
{
	gameNode::update();

	gameStart();

	_bg->setStage(_em->getStage());
	_bg->update();
	_ui->update();
	if (_gameStart == true)
	{
		_player->update();
		_pBullet->update();
		_em->update();
		_eBullet->update();
		_im->update();
	}
}

//그리는거.......
void playGround::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================== 이 위는 손대지 마시오 =========================

	_bg->render(getMemDC());
	if (_gameStart == true)
	{
		_im->render(getMemDC());
		_em->render(getMemDC());
		_pBullet->render(getMemDC());
		_eBullet->render(getMemDC());
		_player->render(getMemDC());
	}
	_ui->render(getMemDC(), _alpha1);
	if (_player->getGameOver() == true)
	{
		_gameOver = true;
		_gameOverImage->render(getMemDC(), 0, 0);
	}
	if (_em->getGameOver() == true)
	{
		_gameOver = true;
		_ending->render(getMemDC(), 0, 0);
	}

	//wsprintf(test1, "%d", _gameOver);
	//TextOut(getMemDC(), 0, 0, test1, strlen(test1));

	

	//================== 이 아래는 손대지 마시오 ========================
	this->getBackBuffer()->render(getHDC(), 0, 0);//hdc영역에 그려준다 
}

void playGround::gameStart(void)
{
	if (_gameOver == false)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_gameStart = true;
			_alpha1 = 0;
			_ui->setIsStart(true);
		}
	}
	if (_gameOver == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			init();
		}
	}
}
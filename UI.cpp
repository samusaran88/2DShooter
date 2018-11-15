#include "stdafx.h"
#include "UI.h"
#include "player.h"

UI::UI()
{
}


UI::~UI()
{

}

HRESULT UI::init(void)	
{
	_start = IMAGEMANAGER->addImage("start", ".\\images\\Start.bmp", 1000, 750, true, RGB(255, 0, 255), true);
	_ui = IMAGEMANAGER->addImage("UI", ".\\images\\UI.bmp", 1000, 750, true, RGB(255, 0, 255), true);
	_life = IMAGEMANAGER->addImage("life", ".\\images\\life.bmp", 48, 48, true, RGB(255, 0, 255), true);
	_pressEnter = IMAGEMANAGER->addImage("pressEnter", ".\\images\\pressEnter.bmp", 1000, 750, true, RGB(255, 0, 255), true);
	_ready = IMAGEMANAGER->addFrameImage("ready", ".\\images\\ready.bmp", 4680, 130, 12, 1, true, RGB(255, 0, 255), true);
	_alpha1 = 255;
	_alpha2 = 0;
	_counter = 0;
	_frame1 = 0;
	_isStart = false;
	_type = 0;
	return S_OK;
}
void UI::release(void)	
{

}
void UI::update(void)	
{
	if (_isStart == false)
	{
		_alpha2++;
		if (_alpha2 > 255) _alpha2 = 0;
	}
	else if (_isStart == true && _counter < 200)
	{
		_counter++;
		if (_counter % 5 == 0 && _frame1 < 11) _frame1++;
	}
	
}
void UI::render(HDC hdc, int alpha)
{
	_alpha1 = alpha;
	if (_alpha1 > 0)
	{
		_start->alphaRender(hdc, 0, 0, _alpha1);
		_pressEnter->alphaRender(hdc, 0, 0, _alpha2);
	}
	_ui->alphaRender(hdc, 0, 0, 255);
	for (int i = 0; i < _player->getPlayerLife(); i++)
	{
		_life->render(hdc, 780 + 70 * i, 450);
	}
	if (_isStart == true && _counter < 200)
	{
		_ready->frameRender(hdc, 180, 200, _frame1, 0);
	}
	switch (_type)
	{
	case(0):
		IMAGEMANAGER->findImage("itemRed")->render(hdc, 850, 250);
		break;
	case(1):
		IMAGEMANAGER->findImage("itemBlue")->render(hdc, 850, 250);
		break;
	case(2):
		IMAGEMANAGER->findImage("itemGreen")->render(hdc, 850, 250);
		break;
	default:
		break;
	}
}
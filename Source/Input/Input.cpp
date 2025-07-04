#include "Input/Input.h"

Input* Input::instance = nullptr;

// コンストラクタ
Input::Input(HWND hWnd)
	: mouse(hWnd)
{
	instance = this;
}

// 更新処理
void Input::Update()
{
	gamePad.Update();
	mouse.Update();
}

POINT Input::GetMousePosition(HWND hWnd) const
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	return pt;
}
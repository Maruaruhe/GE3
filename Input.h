#pragma once
#include <Windows.h>

#include <dinput.h>

class Input
{
public:

	void Initialize(HINSTANCE hInstance, HWND hwnd);

	void Update();

private:
	ComPtr<IDirectInputDevice8> keyboard;
};


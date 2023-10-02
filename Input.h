#pragma once
#include <Windows.h>

#include <wrl.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

class Input
{
public:

	void Initialize(HINSTANCE hInstance, HWND hwnd);

	void Update();

private:
	template <class Type> using ComPtr = Microsoft::WRL::ComPtr<Type>;

	ComPtr<IDirectInputDevice8> keyboard;
};


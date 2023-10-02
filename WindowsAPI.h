#pragma once
#include <Windows.h>
#include <cstdint>

class WindowsAPI
{
public:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	void Initialize();

	void Update();
};


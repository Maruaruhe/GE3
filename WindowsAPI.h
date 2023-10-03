#pragma once
#include <Windows.h>
#include <cstdint>

class WindowsAPI
{
public:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	void Initialize();

	void Update();

	HWND GetHwnd()const { return hwnd; }
	HINSTANCE GetHInstance()const { return wc.hInstance; }

public:
	//ウインドウクラスの設定
	WNDCLASSEX wc{};

	//ウィンドウサイズ
	static const int kCliantWidth = 1280;
	static const int kCliantHeight = 720;

private:
	HWND hwnd = nullptr;
};


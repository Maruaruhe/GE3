#include "WindowsAPI.h"

LRESULT CALLBACK WindowsAPI::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	//メッセージに応じてゲーム固有の処理を行う
	switch (msg)
	{
	case WM_DESTROY:	//ウインドウが破棄された
		PostQuitMessage(0);		//OSに対して、アプリの終了を伝える
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);	//標準のメッセージ処理を行う
}

void WindowsAPI::Initialize() {
	//ウィンドウサイズ
	const int kCliantWidth = 1280;
	const int kCliantHeight = 720;

	//ウインドウクラスの設定
	WNDCLASSEX wc{};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WindowProc;	//ウインドウプロシージャ	
	wc.lpszClassName = L"DirectX";	//ウインドウクラス名（なんでもいい）
	wc.hInstance = GetModuleHandle(nullptr);	//インスタンスハンドル
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);	//カーソル

	//ウインドウクラスを登録する
	RegisterClassEx(&wc);
	//ウィンドウサイズ{X座標 Y座標 横幅 縦幅}
	RECT wrc = { 0,0,kCliantWidth,kCliantHeight };
	//自動でサイズを補正する
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	HWND hwnd = CreateWindow(
		wc.lpszClassName,		//利用するクラス名
		L"DirectX",			//タイトルバーの文字
		WS_OVERLAPPEDWINDOW,	//よく見るウインドウスタイル
		CW_USEDEFAULT,			//表示X座標（Windowsに任せる）
		CW_USEDEFAULT,			//表示Y座標（Windowsに任せる）
		wrc.right - wrc.left,	//ウインドウ横幅
		wrc.bottom - wrc.top,	//ウインドウ縦幅
		nullptr,				//ウインドウハンドル
		nullptr,				//メニューハンドル
		wc.hInstance,			//インスタンスハンドル
		nullptr
	);

	ShowWindow(hwnd, SW_SHOW);
}

void WindowsAPI::Update() {

}
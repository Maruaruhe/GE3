#pragma once
#include <Windows.h>

#include <wrl.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

class Input
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(HINSTANCE hInstance, HWND hwnd);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
/// <summary>
/// キーの押下をチェック
/// </summary>
	bool PushKey(BYTE keyNumber);
/// <summary>
/// キーのトリガーをチェック
/// </summary>
	bool TriggerKey(BYTE keyNumber);

private:
	template <class Type> using ComPtr = Microsoft::WRL::ComPtr<Type>;

	ComPtr<IDirectInput8> directInput = nullptr;

	ComPtr<IDirectInputDevice8> keyboard;

	//全キーの状態
	BYTE key[256] = {};
	BYTE preKey[256] = {};
};


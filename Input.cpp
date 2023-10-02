#include "Input.h"
#include <cassert>
#include <wrl.h>

using namespace Microsoft::WRL;

#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxgiod.lib")

void Input::Initialize(HINSTANCE hInstance, HWND hwnd) {
	HRESULT result;
	//DiretxInputのインスタンス生成
	// ComPtr<IDirectInput8> directInput = nullptr;
	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));
	//キーボードデバイス作成
	ComPtr<IDirectInputDevice8> keyboard;
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));
	//入力デーら形式のセット
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);
	assert(SUCCEEDED(result));
	//排他制御レベルのリセット
	result = keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void Input::Update() {
	//キーボード情報の取得開始
	keyboard->Acquire();
	BYTE key[256] = {};
	//全キーの入力情報を取得する
	keyboard->GetDeviceState(sizeof(key), key);
}
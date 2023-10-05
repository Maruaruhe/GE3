#include <Windows.h>

#include "Input.h"
#include "WindowsAPI.h"
#include "DirectXCommon.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//
	Input* input = nullptr;
	input = new Input();

	WindowsAPI* winAPI = nullptr;
	winAPI = new WindowsAPI();

	DirectXCommon* dxCommon = nullptr;
	dxCommon = new DirectXCommon;

	//
	winAPI->Initialize();
	input->Initialize(winAPI);
	dxCommon->Initialize(winAPI);
	//
	while (1) {
		if (winAPI->ProcessMessage()) {
			break;
		}
	}
	//
	delete input;
	delete dxCommon;

	winAPI->Finalize();
	delete winAPI;

	return 0;
}
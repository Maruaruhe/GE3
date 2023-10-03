#include <Windows.h>

#include "Input.h"
#include "WindowsAPI.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//
	Input* input = nullptr;
	input = new Input();

	WindowsAPI* winAPI = nullptr;
	winAPI = new WindowsAPI();

	//
	winAPI->Initialize();
	input->Initialize(winAPI);
	//
	while (1) {
		if (winAPI->ProcessMessage()) {
			break;
		}
	}
	//
	delete input;

	winAPI->Finalize();
	delete winAPI;

	return 0;
}
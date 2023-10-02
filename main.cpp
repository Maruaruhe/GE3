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
	//input->Initialize();
	winAPI->Initialize();

	//
	delete input;
	delete winAPI;

	return 0;
}
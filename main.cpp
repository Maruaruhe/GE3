#include <Windows.h>

#include "Input.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//
	Input* input = nullptr;
	input = new Input();

	//
	input->Initialize();

	//
	delete input;

	return 0;
}
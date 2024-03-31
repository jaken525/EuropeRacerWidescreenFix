#include "pch.h"
#include "../includes/CPatch.h"
#include "../includes/IniReader.h"

#include <iostream>
#include <Windows.h>

HWND hWnd;

const uint16_t PAD = 133;

uint16_t resolutionX;
uint16_t resolutionY;

DWORD jmpAddr;

void _declspec(naked) asm_46C709()
{
	_asm
	{
		mov CX, resolutionY
		mov word ptr ss : [EBP - 0x8] , CX
		mov DX, resolutionX
		mov word ptr ss : [EBP - 0x6] , DX

		mov jmpAddr, 0x46C711
		jmp jmpAddr
	}
}

void Init()
{
	resolutionX = 1280;
	resolutionY = 720;

	CPatch::RedirectJump(0x46C709, asm_46C709);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	if (reason == DLL_PROCESS_ATTACH)
		Init();

	return TRUE;
}
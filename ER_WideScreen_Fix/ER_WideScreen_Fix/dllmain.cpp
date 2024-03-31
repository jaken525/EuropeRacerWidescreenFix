#include "pch.h"
#include "Overlay.h"
#include "../includes/CPatch.h"
#include "../includes/IniReader.h"

#include <Windows.h>

HWND hWnd;

int resolutionX;
int resolutionY;

const int customVideoMemory = 134217728;

DWORD jmpAddr;

void _declspec(naked) asm_49A986()
{
	_asm
	{
		mov EAX, customVideoMemory
		mov DWORD PTR DS : [0x6A0520] , EAX

		mov jmpAddr, 0x49A98B
		jmp jmpAddr
	}
}

void _declspec(naked) asm_49DED2()
{
	_asm
	{
		mov ECX, customVideoMemory
		mov DWORD PTR DS : [0x6A0520] , ECX

		mov jmpAddr, 0x49DED8
		jmp jmpAddr
	}
}

void _declspec(naked) asm_50282D()
{
	_asm
	{
		mov ECX, resolutionX
		mov dword ptr ds : [0x61F0E8] , ECX
		mov ECX, 0x10
		mov EDX, resolutionY
		mov dword ptr ds : [0x61F0EC] , EDX
		mov EDX, 0x0

		mov jmpAddr, 0x502845
		jmp jmpAddr
	}
}

void SetOverlaysPaths16()
{
	CPatch::SetChar(OverlayOffsets::ovl_gen, 49);
	CPatch::SetChar(OverlayOffsets::ovl_othr, 49);
	CPatch::SetChar(OverlayOffsets::ovl_qraq, 49);
	CPatch::SetChar(OverlayOffsets::ovl_time, 49);
	CPatch::SetChar(OverlayOffsets::ovl_wait, 49);
}

void Init()
{
	HMONITOR monitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
	MONITORINFO info;
	info.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(monitor, &info);
	resolutionX = info.rcMonitor.right - info.rcMonitor.left;
	resolutionY = info.rcMonitor.bottom - info.rcMonitor.top;

	if (Overlay::GetRatio(resolutionX, resolutionY))
		SetOverlaysPaths16();

	CPatch::RedirectJump(0x50282D, asm_50282D);
	CPatch::RedirectJump(0x49A986, asm_49A986);
	//CPatch::RedirectJump(0x50282D, asm_50282D);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	if (reason == DLL_PROCESS_ATTACH)
		Init();

	return TRUE;
}
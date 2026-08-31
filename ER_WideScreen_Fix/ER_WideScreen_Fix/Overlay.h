#pragma once
#include <iostream>

#include "../includes/MemoryMgr.h"

namespace OverlayOffsets
{
	constexpr auto ovl_gen = 0x607D76;
	constexpr auto ovl_time = 0x607D83;
	constexpr auto ovl_qraq = 0x607D93;
	constexpr auto ovl_othr = 0x607DA3;
	constexpr auto ovl_wait = 0x607DFB;
	constexpr auto customVideoMemory = 0x6A0520;
}

struct Overlay
{
	static int GetRatio(int resolutionX, int resolutionY)
	{
		float aspectRatio = 16.0f / (static_cast<float>(resolutionX) / (static_cast<float>(resolutionY) / 9.0f));
		Memory::Patch<float>(0x67430F07, aspectRatio);
		Memory::Patch<float>(0x5D015D68, aspectRatio);
		Memory::Patch<float>(0x5D015D70, aspectRatio);
		Memory::Patch<float>(0x5D015D78, aspectRatio);
		Memory::Patch<float>(0x5D015D80, aspectRatio);
		Memory::Patch<float>(0x5D015D88, aspectRatio);
		if ((resolutionX / 4) == (resolutionY / 3))
			return 0;
		if ((resolutionX / 16) == (resolutionY / 9))
			return 1;
		if ((resolutionX / 16) == (resolutionY / 10))
			return 1;

		return -1;
	}
};
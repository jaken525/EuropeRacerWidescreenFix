#pragma once
#include <iostream>

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
		if ((resolutionX / 4) == (resolutionY / 3))
			return 0;
		if ((resolutionX / 16) == (resolutionY / 9))
			return 1;
		if ((resolutionX / 16) == (resolutionY / 10))
			return 1;

		return -1;
	}
};
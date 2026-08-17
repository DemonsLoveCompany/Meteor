#pragma once

#pragma once

#if PLATFORM_WINDOWS

#include "Windows/WindowsApplication.h"

class FDualMouseMessageHandler : public IWindowsMessageHandler
{
public:
	FDualMouseMessageHandler();
	virtual ~FDualMouseMessageHandler();

	virtual bool ProcessMessage(
		HWND Hwnd,
		uint32 Msg,
		WPARAM WParam,
		LPARAM LParam,
		int32& OutResult
	) override;

	void ConsumeRazerDelta(int32& OutX, int32& OutY);
	void ConsumeSteelSeriesDelta(int32& OutX, int32& OutY);

private:
	int32 RazerDeltaX = 0;
	int32 RazerDeltaY = 0;

	int32 SteelSeriesDeltaX = 0;
	int32 SteelSeriesDeltaY = 0;
};



#endif
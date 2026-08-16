#pragma once

#pragma once

#if PLATFORM_WINDOWS

#include "Windows/WindowsApplication.h"

class FDualMouseMessageHandler : public IWindowsMessageHandler
{
public:
	FDualMouseMessageHandler();
	~FDualMouseMessageHandler();

	virtual bool ProcessMessage(
		HWND Hwnd,
		uint32 Msg,
		WPARAM WParam,
		LPARAM LParam,
		int32& OutResult
	) override;
};

#endif
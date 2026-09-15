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

	void ConsumeMouse0Delta(int32& OutX, int32& OutY);
	void ConsumeMouse1Delta(int32& OutX, int32& OutY);

	bool IsLeftMouseFireHeld() const;
	bool IsRightMouseFireHeld() const;

private:
	FString GetDeviceName(HANDLE DeviceHandle) const;

	int32 RightMouseX = 0;
	int32 RightMouseY = 0;

	int32 LeftMouseX = 0;
	int32 LeftMouseY = 0;

	bool bLeftMouseFireHeld = false;
	bool bRightMouseFireHeld = false;
};

#endif
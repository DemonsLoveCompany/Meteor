#include "DualMouseMessageHandler.h"
#include "Windows/WindowsHWrapper.h"

#if PLATFORM_WINDOWS

FDualMouseMessageHandler::FDualMouseMessageHandler()
{
}

FDualMouseMessageHandler::~FDualMouseMessageHandler()
{
}

bool FDualMouseMessageHandler::ProcessMessage(
	HWND Hwnd,
	uint32 Msg,
	WPARAM WParam,
	LPARAM LParam,
	int32& OutResult
)
{
	if (Msg == WM_INPUT)
	{
		UE_LOG(LogTemp, Warning, TEXT("WM_INPUT received"));
	}

	return false;
}

#endif
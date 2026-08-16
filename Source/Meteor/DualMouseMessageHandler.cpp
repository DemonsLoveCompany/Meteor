#include "DualMouseMessageHandler.h"

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
	return false;
}

#endif
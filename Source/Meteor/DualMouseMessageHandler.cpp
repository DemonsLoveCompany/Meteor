#include "DualMouseMessageHandler.h"
#include "Windows/WindowsHWrapper.h"

void FDualMouseMessageHandler::ConsumeRazerDelta(
	int32& OutX,
	int32& OutY
)
{
	OutX = RazerDeltaX;
	OutY = RazerDeltaY;

	RazerDeltaX = 0;
	RazerDeltaY = 0;
}

void FDualMouseMessageHandler::ConsumeSteelSeriesDelta(
	int32& OutX,
	int32& OutY
)
{
	OutX = SteelSeriesDeltaX;
	OutY = SteelSeriesDeltaY;

	SteelSeriesDeltaX = 0;
	SteelSeriesDeltaY = 0;
}

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
		UINT DataSize = 0;

		GetRawInputData(
			reinterpret_cast<HRAWINPUT>(LParam),
			RID_INPUT,
			nullptr,
			&DataSize,
			sizeof(RAWINPUTHEADER)
		);

		if (DataSize > 0)
		{
			TArray<uint8> RawData;
			RawData.SetNumUninitialized(DataSize);

			UINT BytesRead = GetRawInputData(
				reinterpret_cast<HRAWINPUT>(LParam),
				RID_INPUT,
				RawData.GetData(),
				&DataSize,
				sizeof(RAWINPUTHEADER)
			);

			if (BytesRead != static_cast<UINT>(-1))
			{
				RAWINPUT* RawInput =
					reinterpret_cast<RAWINPUT*>(RawData.GetData());

				if (RawInput->header.dwType == RIM_TYPEMOUSE)
				{

					const HANDLE RazerHandle = reinterpret_cast<HANDLE>(0x1003F);
					const HANDLE SteelSeriesHandle = reinterpret_cast<HANDLE>(0x10039); //Hard-coding mouse

					if (RawInput->header.dwType == RIM_TYPEMOUSE)
					{
						if (RawInput->header.hDevice == RazerHandle)
						{
							RazerDeltaX += RawInput->data.mouse.lLastX;
							RazerDeltaY += RawInput->data.mouse.lLastY;
						}
						else if (RawInput->header.hDevice == SteelSeriesHandle)
						{
							SteelSeriesDeltaX += RawInput->data.mouse.lLastX;
							SteelSeriesDeltaY += RawInput->data.mouse.lLastY;
						}
					}

				}
			}
		}
	}

	return false;
}

#endif
#include "DualMouseMessageHandler.h"
#include "Windows/WindowsHWrapper.h"

void FDualMouseMessageHandler::ConsumeMouse0Delta(
	int32& OutX,
	int32& OutY
)
{
	OutX = LeftMouseX;
	OutY = LeftMouseY;

	LeftMouseX = 0;
	LeftMouseY = 0;
}

void FDualMouseMessageHandler::ConsumeMouse1Delta(
	int32& OutX,
	int32& OutY
)
{
	OutX = RightMouseX;
	OutY = RightMouseY;

	RightMouseX = 0;
	RightMouseY = 0;
}

bool FDualMouseMessageHandler::IsLeftMouseFireHeld() const
{
	return bLeftMouseFireHeld;
}

bool FDualMouseMessageHandler::IsRightMouseFireHeld() const
{
	return bRightMouseFireHeld;
}

FString FDualMouseMessageHandler::GetDeviceName(HANDLE DeviceHandle) const
{
	UINT NameSize = 0;

	GetRawInputDeviceInfo(
		DeviceHandle,
		RIDI_DEVICENAME,
		nullptr,
		&NameSize
	);

	if (NameSize == 0)
	{
		return FString();
	}

	TArray<TCHAR> DeviceNameBuffer;
	DeviceNameBuffer.SetNumZeroed(NameSize + 1);

	UINT Result = GetRawInputDeviceInfo(
		DeviceHandle,
		RIDI_DEVICENAME,
		DeviceNameBuffer.GetData(),
		&NameSize
	);

	if (Result == static_cast<UINT>(-1))
	{
		return FString();
	}

	return FString(DeviceNameBuffer.GetData());
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
					const FString DeviceName =
						GetDeviceName(RawInput->header.hDevice);

					//temporary debugging
					if (DeviceName.Contains(TEXT("VID_1532")))
					{
						UE_LOG(
							LogTemp,
							Warning,
							TEXT("RAZER RAW INPUT DEVICE: %s"),
							*DeviceName
						);
					}

					const int32 DeltaX = RawInput->data.mouse.lLastX;
					const int32 DeltaY = RawInput->data.mouse.lLastY;

					const USHORT ButtonFlags = RawInput->data.mouse.usButtonFlags;

					if (
						//Ducky Frozen Feather Mouse ~ Left Reticule
						DeviceName.Contains(TEXT("VID_3233")) &&
						DeviceName.Contains(TEXT("PID_0009"))
						)
					{
						LeftMouseX += DeltaX;
						LeftMouseY += DeltaY;

						if (ButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN)
						{
							bLeftMouseFireHeld = true;
						}

						if (ButtonFlags & RI_MOUSE_RIGHT_BUTTON_UP)
						{
							bLeftMouseFireHeld = false;
						}
					}
					else if (
						//Razer Wireless Mouse ~ Right Reticule
						DeviceName.Contains(TEXT("VID_1532")) &&
						DeviceName.Contains(TEXT("PID_00BE"))
						)
					{
						
						RightMouseX += DeltaX;
						RightMouseY += DeltaY;

						if (ButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN)
						{
							bRightMouseFireHeld = true;
						}

						if (ButtonFlags & RI_MOUSE_LEFT_BUTTON_UP)
						{
							bRightMouseFireHeld = false;
						}
					}









					//OLD MOUSE CONSOLE LOGGING CODE
					//const HANDLE RazerHandle = reinterpret_cast<HANDLE>(0x1003F);
					//const HANDLE SteelSeriesHandle = reinterpret_cast<HANDLE>(0x10039); //Hard-coding mouse

					//if (RawInput->header.dwType == RIM_TYPEMOUSE)
					//{
					//	if (RawInput->header.hDevice == RazerHandle)
					//	{
					//		RazerDeltaX += RawInput->data.mouse.lLastX;
					//		RazerDeltaY += RawInput->data.mouse.lLastY;
					//	}
					//	else if (RawInput->header.hDevice == SteelSeriesHandle)
					//	{
					//		SteelSeriesDeltaX += RawInput->data.mouse.lLastX;
					//		SteelSeriesDeltaY += RawInput->data.mouse.lLastY;
					//	}
					//}

					//Noisy device name print
					
					
					//const FString DeviceName =
					//	GetDeviceName(RawInput->header.hDevice);

					//UE_LOG(
					//	LogTemp,
					//	Warning,
					//	TEXT("Mouse Device=%p Name=%s"),
					//	RawInput->header.hDevice,
					//	*DeviceName
					//);

				}
			}
		}
	}

	return false;
}

#endif
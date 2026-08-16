// Fill out your copyright notice in the Description page of Project Settings.

#include "Meteor.h"
#include "Modules/ModuleManager.h"

#if PLATFORM_WINDOWS
#include "DualMouseMessageHandler.h"
#include "Framework/Application/SlateApplication.h"
#include "Windows/WindowsApplication.h"
#endif

IMPLEMENT_PRIMARY_GAME_MODULE(FMeteorModule, Meteor, "Meteor");

void FMeteorModule::StartupModule()
{
	FDefaultGameModuleImpl::StartupModule();

#if PLATFORM_WINDOWS
	if (FSlateApplication::IsInitialized())
	{
		TSharedPtr<GenericApplication> PlatformApplication =
			FSlateApplication::Get().GetPlatformApplication();

		FWindowsApplication* WindowsApplication =
			static_cast<FWindowsApplication*>(PlatformApplication.Get());

		DualMouseMessageHandler = MakeShared<FDualMouseMessageHandler>();
		WindowsApplication->AddMessageHandler(*DualMouseMessageHandler);
		

		UE_LOG(LogTemp, Warning, TEXT("Dual mouse Windows message handler registered."));
	}
#endif
}

void FMeteorModule::ShutdownModule()
{
#if PLATFORM_WINDOWS
	if (DualMouseMessageHandler.IsValid() &&
		FSlateApplication::IsInitialized())
	{
		TSharedPtr<GenericApplication> PlatformApplication =
			FSlateApplication::Get().GetPlatformApplication();

		FWindowsApplication* WindowsApplication =
			static_cast<FWindowsApplication*>(PlatformApplication.Get());



		WindowsApplication->RemoveMessageHandler(*DualMouseMessageHandler);
	

		DualMouseMessageHandler.Reset();
	}
#endif

	FDefaultGameModuleImpl::ShutdownModule();
}

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FDualMouseMessageHandler;

class FMeteorModule : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void ConsumeMouse0Delta(int32& OutX, int32& OutY);
	void ConsumeMouse1Delta(int32& OutX, int32& OutY);

private:
	TSharedPtr<FDualMouseMessageHandler> DualMouseMessageHandler;
};
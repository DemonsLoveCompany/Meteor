#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FDualMouseMessageHandler;

class FMeteorModule : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void ConsumeRazerDelta(int32& OutX, int32& OutY);
	void ConsumeSteelSeriesDelta(int32& OutX, int32& OutY);

private:
	TSharedPtr<FDualMouseMessageHandler> DualMouseMessageHandler;
};
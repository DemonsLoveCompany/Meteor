#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FDualMouseMessageHandler;

class FMeteorModule : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedPtr<FDualMouseMessageHandler> DualMouseMessageHandler;
};
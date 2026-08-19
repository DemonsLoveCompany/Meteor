// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DualMouseInputComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class METEOR_API UDualMouseInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDualMouseInputComponent();

	UFUNCTION(BlueprintCallable, Category = "Dual Mouse Input")
	void GetMouse0Delta(int32& X, int32& Y);

	UFUNCTION(BlueprintCallable, Category = "Dual Mouse Input")
	void GetMouse1Delta(int32& X, int32& Y);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

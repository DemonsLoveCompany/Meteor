// Fill out your copyright notice in the Description page of Project Settings.


#include "DualMouseInputComponent.h"
#include "Meteor.h"
#include "Modules/ModuleManager.h"

// Sets default values for this component's properties
UDualMouseInputComponent::UDualMouseInputComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDualMouseInputComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UDualMouseInputComponent::GetMouse0Delta(int32& X, int32& Y)
{
	FMeteorModule& MeteorModule =
		FModuleManager::LoadModuleChecked<FMeteorModule>("Meteor");

	MeteorModule.ConsumeMouse0Delta(X, Y);
}

void UDualMouseInputComponent::GetMouse1Delta(int32& X, int32& Y)
{
	FMeteorModule& MeteorModule =
		FModuleManager::LoadModuleChecked<FMeteorModule>("Meteor");

	MeteorModule.ConsumeMouse1Delta(X, Y);
}


// Called every frame
void UDualMouseInputComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


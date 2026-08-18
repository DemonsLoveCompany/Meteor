// Fill out your copyright notice in the Description page of Project Settings.


#include "DualMouseTest.h"
#include "Meteor.h"
#include "Modules/ModuleManager.h"
#include "GameFramework/Pawn.h"

// Sets default values
ADualMouseTest::ADualMouseTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADualMouseTest::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("DualMouseTest is ....!"));
}

// Called every frame
void ADualMouseTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FMeteorModule& MeteorModule =
		FModuleManager::LoadModuleChecked<FMeteorModule>("Meteor");

	int32 RazerX = 0;
	int32 RazerY = 0;

	int32 SteelSeriesX = 0;
	int32 SteelSeriesY = 0;

	MeteorModule.ConsumeMouse0Delta(RazerX, RazerY);
	MeteorModule.ConsumeMouse1Delta(SteelSeriesX, SteelSeriesY);

	if (RazerTargetActor && (RazerX != 0 || RazerY != 0))
	{
		APawn* RazerPawn = Cast<APawn>(RazerTargetActor);

		if (RazerPawn)
		{
			RazerPawn->AddControllerYawInput(
				RazerX * MouseSensitivity
			);

			RazerPawn->AddControllerPitchInput(
				-RazerY * MouseSensitivity
			);
		}
	}



	if (SteelSeriesTargetActor &&
		(SteelSeriesX != 0 || SteelSeriesY != 0))
	{
		const FRotator RotationDelta(
			-SteelSeriesY * MouseSensitivity,
			SteelSeriesX * MouseSensitivity,
			0.0f
		);

		SteelSeriesTargetActor->AddActorLocalRotation(RotationDelta);
	}

}


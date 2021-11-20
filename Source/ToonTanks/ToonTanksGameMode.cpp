// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();

		if (APlayerController* TankPlayerController = Tank->GetTankPlayerController())
		{
			Tank->DisableInput(TankPlayerController);
			Tank->GetTankPlayerController()->bShowMouseCursor = false;
		}	
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay(); // This way we get parent functionality

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}
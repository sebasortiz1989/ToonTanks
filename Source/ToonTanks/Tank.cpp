// Fill out your copyright notice in the Description page of Project Settings.
#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent); // This is so we don't miss any functionality implemented in the parent version

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAxis(TEXT("RotateTurretGamepad"), this, &ATank::RotateWithGamepad);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TankPlayerController && UseMouseForTurretRotation)
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
		RotateTurret(HitResult.ImpactPoint);
	}
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankPlayerController = Cast<APlayerController>(GetController());
}

void ATank::Move(float Value)
{
	FVector DeltaLocation = FVector::ZeroVector;
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	DeltaLocation.X = Value * Speed * DeltaTime;

	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	DeltaRotation.Yaw = Value * RotationSpeed * DeltaTime;
	AddActorLocalRotation(DeltaRotation, true);
}

void ATank::RotateWithGamepad(float Value) // The mouse function currently overrides this one, but it works
{
	if (!UseMouseForTurretRotation)
	{
		FRotator DeltaRotation = FRotator::ZeroRotator;
		float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
		DeltaRotation.Yaw = Value * TurretRotationSpeed * DeltaTime;

		GetTurretMesh()->AddLocalRotation(DeltaRotation, true);
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	void Move(float Value);
	void Turn(float Value);
	void RotateWithGamepad(float Value);

	UPROPERTY(EditAnywhere, Category = "Movement", BlueprintReadWrite, meta = (AllowPrivateAccess = "true")) // Remember for graph you use the meta
	float Speed = 1000.f;
	
	UPROPERTY(EditAnywhere, Category = "Movement", BlueprintReadWrite, meta = (AllowPrivateAccess = "true")) // Remember for graph you use the meta
	float RotationSpeed = 90.f;

	UPROPERTY(EditAnywhere, Category = "Movement", BlueprintReadWrite, meta = (AllowPrivateAccess = "true")) // Remember for graph you use the meta
	float TurretRotationSpeed = 90.f;
	
	APlayerController* PlayerControllerRef;

};

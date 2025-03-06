// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestCharacter.generated.h"

UCLASS()
class LEARNEDITOR_API ATestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATestCharacter();
public:
UPROPERTY(EditAnywhere)
class UDH_WeaponDataAsset * DA;
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

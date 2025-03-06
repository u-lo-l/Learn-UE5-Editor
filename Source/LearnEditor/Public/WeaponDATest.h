// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DH_WeaponDataAsset.h"
#include "WeaponDATest.generated.h"

UCLASS()
class LEARNEDITOR_API AWeaponDATest : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	UDH_WeaponDataAsset * DAWeapon = nullptr;

	AWeaponDATest();
	protected:
	void BeginPlay() override;
};

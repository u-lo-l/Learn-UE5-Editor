// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DHWeaponBase.h"
#include "DHSwordBase.generated.h"

/**
 * 
 */
UCLASS()
class LEARNEDITOR_API ADHSwordBase : public ADHWeaponBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SkeletalMesh2;
	ADHSwordBase();
protected:
};

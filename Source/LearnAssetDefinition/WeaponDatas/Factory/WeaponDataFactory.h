// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorFactories/ActorFactory.h"
#include "WeaponDataFactory.generated.h"

/**
 * 
 */
UCLASS()
class LEARNASSETDEFINITION_API UWeaponDataFactory : public UFactory
{
	GENERATED_BODY()
	
	UWeaponDataFactory();
	
	virtual UObject * FactoryCreateNew
	(
		UClass * InClass,
		UObject * InParent,
		FName InName,
		EObjectFlags Flags,
		UObject * Context,
		FFeedbackContext * Warn,
		FName CallingContext
	) override;
};

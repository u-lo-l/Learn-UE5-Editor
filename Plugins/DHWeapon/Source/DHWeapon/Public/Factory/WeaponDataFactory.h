#pragma once

#include "CoreMinimal.h"
#include "WeaponDataFactory.generated.h"

/**
 * 
 */
UCLASS()
class DHWEAPON_API UWeaponDataFactory : public UFactory
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

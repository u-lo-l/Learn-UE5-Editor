#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DHWeaponBase.generated.h"

UCLASS(Abstract, NotPlaceable)
class DHWEAPON_API ADHWeaponBase : public AActor
{
	GENERATED_BODY()
public:
	ADHWeaponBase();
protected:
	virtual void BeginPlay() override;
};

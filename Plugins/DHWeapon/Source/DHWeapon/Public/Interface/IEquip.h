#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IEquip.generated.h"

DECLARE_MULTICAST_DELEGATE(FEquipmentDelegate);

UINTERFACE()
class UIEquip : public UInterface
{
	GENERATED_BODY()
};

class DHWEAPON_API IIEquip
{
	GENERATED_BODY()
public:
	virtual void RequestEquip(FEquipmentDelegate OnMontageBlendingOut = {}) = 0;
	virtual void RequestUnequip(FEquipmentDelegate OnMontageBlendingOut = {}) = 0;
};

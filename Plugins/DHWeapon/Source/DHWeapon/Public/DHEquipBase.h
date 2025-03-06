#pragma once

#include "CoreMinimal.h"
#include "Interface/IEquip.h"
#include "UObject/Object.h"
#include "DHEquipBase.generated.h"

struct FDH_EquipmentData;
class UDH_WeaponDataAsset;

DECLARE_MULTICAST_DELEGATE(FEquipmentBeginEquip);
DECLARE_MULTICAST_DELEGATE(FEquipmentEndEquip);
DECLARE_MULTICAST_DELEGATE(FEquipmentUnequip);

UCLASS(Abstract, Blueprintable)
class DHWEAPON_API UDHEquipBase : public UObject, public IIEquip
{
	GENERATED_BODY()
	friend UDH_WeaponDataAsset;

protected:
	void Init
	(
		ACharacter* InOwnerCharacter,
		FDH_EquipmentData* InEquipData,
		FDH_EquipmentData* InUnequipData
	);
protected:
	FEquipmentBeginEquip OnEquipmentBeginEquip;
	FEquipmentBeginEquip OnEquipmentEndEquip;
	FEquipmentUnequip OnEquipmentUnequip;

	UPROPERTY()
	ACharacter * OwnerCharacter;
	FDH_EquipmentData * EquipData;
	FDH_EquipmentData * UnequipData;
};

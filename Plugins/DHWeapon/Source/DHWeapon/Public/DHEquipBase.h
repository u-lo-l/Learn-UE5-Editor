#pragma once

#include "CoreMinimal.h"
#include "Interface/IEquip.h"
#include "UObject/Object.h"
#include "DHEquipBase.generated.h"

struct FDH_EquipmentData;
class UDH_WeaponDataAsset;


UCLASS(Abstract, Blueprintable)
class DHWEAPON_API UDHEquipBase : public UObject, public IIEquip
{
	GENERATED_BODY()
	friend UDH_WeaponDataAsset;

public:
	virtual void RequestEquip( FEquipmentDelegate OnMontageBlendingOut = {} ) override;
	virtual void RequestUnequip(FEquipmentDelegate OnMontageBlendingOut = {}) override;
	void BroadcastEquipDelegates();
	void BroadcastUnequipDelegates();
	void LinkAnimLayer();
	void Init
	(
		ACharacter* InOwnerCharacter,
		const FDH_EquipmentData* InEquipData,
		TSubclassOf<UAnimInstance> EquipAnimLayerClass
	);
	
	FEquipmentDelegate OnEquipWeapon;
	FEquipmentDelegate OnUnequipWeapon;

protected:
	UPROPERTY()
	ACharacter * OwnerCharacter;
	UPROPERTY()
	UAnimInstance * AnimInstance;
	UPROPERTY()
	TSubclassOf<UAnimInstance> EquipAnimLayer;
	
	const FDH_EquipmentData * EquipData;
};

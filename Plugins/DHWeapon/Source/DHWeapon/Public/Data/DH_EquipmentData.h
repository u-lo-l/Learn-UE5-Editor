#pragma once

#include "CoreMinimal.h"
#include "DH_EquipmentData.generated.h"

USTRUCT()
struct FDH_EquipmentData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Equip")
	bool bUseEquipMontage = true;
	UPROPERTY(EditAnywhere, Category = "Equip")
	TObjectPtr<UAnimMontage> EquipMontage;
	UPROPERTY(EditAnywhere, Category = "Equip")
	bool CanMoveOnEquip = true;

	UPROPERTY(EditAnywhere, Category = "Unequip")
	bool bUseUnequipMontage = false;
	UPROPERTY(EditAnywhere, Category = "Unequip")
	TObjectPtr<UAnimMontage> UnequipMontage;
	UPROPERTY(EditAnywhere, Category = "Unequip")
	bool CanMoveOnUnequip = false;
};

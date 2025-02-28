#pragma once

#include "CoreMinimal.h"
#include "EquipmentData.generated.h"

USTRUCT()
struct FEquipmentData
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

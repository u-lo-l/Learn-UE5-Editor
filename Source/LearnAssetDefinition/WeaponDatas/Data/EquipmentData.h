#pragma once

#include "CoreMinimal.h"
#include "EquipmentData.generated.h"
USTRUCT()
struct FEquipmentData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	bool bUseEquipMontage = true;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> EquipMontage;
	UPROPERTY(EditAnywhere)
	bool CanMoveOnEquip = true;

	UPROPERTY(EditAnywhere)
	bool bUseUnequipMontage = false;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> UnequipMontage;
	UPROPERTY(EditAnywhere)
	bool CanMoveOnUnequip = false;
};

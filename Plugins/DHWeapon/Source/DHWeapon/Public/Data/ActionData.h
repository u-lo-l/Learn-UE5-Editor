#pragma once

#include "CoreMinimal.h"
#include "DamageData.h"
#include "ActionData.generated.h"

USTRUCT()
struct FActionData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Action")
	TObjectPtr<UAnimMontage> ActionMontage;
	UPROPERTY(EditAnywhere, Category = "Action")
	bool bCanMoveOnAction = false;
	UPROPERTY(EditAnywhere, Category = "Action")
	bool bFixCameraOnAction = false;

	UPROPERTY(EditAnywhere, Category = "Damage Datas")
	TArray<FDamageData> DamageData;
};

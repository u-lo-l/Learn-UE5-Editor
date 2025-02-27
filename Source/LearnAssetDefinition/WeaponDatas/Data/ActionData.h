#pragma once

#include "CoreMinimal.h"
#include "DamageData.h"
#include "ActionData.generated.h"

USTRUCT()
struct FActionData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> ActionMontage;
	UPROPERTY(EditAnywhere)
	bool bCanMoveOnAction = false;
	UPROPERTY(EditAnywhere)
	bool bFixCameraOnAction = false;

	UPROPERTY(EditAnywhere)
	TArray<FDamageData> DamageData;
};

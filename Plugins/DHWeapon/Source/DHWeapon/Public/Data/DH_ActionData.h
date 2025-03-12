#pragma once

#include "CoreMinimal.h"
#include "DH_DamageData.h"
#include "DH_ActionData.generated.h"

USTRUCT()
struct FDH_ActionData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Action")
	UAnimMontage * ActionMontage;
	UPROPERTY(EditAnywhere, Category = "Action")
	bool bCanMoveOnAction = false;
	UPROPERTY(EditAnywhere, Category = "Action")
	bool bFixCameraOnAction = false;

	UPROPERTY(EditAnywhere, Category = "Damage Datas")
	TArray<FDH_DamageData> DamageData;
};

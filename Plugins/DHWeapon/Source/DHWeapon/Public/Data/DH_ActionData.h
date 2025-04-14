#pragma once

#include "CoreMinimal.h"
#include "DH_DamageData.h"
#include "DH_ActionData.generated.h"

UENUM()
enum class EDHActionType : uint8
{
	Triggering = 0,
	Holding = 1,
};

USTRUCT()
struct FDH_ActionData
{
	GENERATED_BODY()
	DHWEAPON_API const static FName HoldingSectionIn;
	DHWEAPON_API const static FName HoldingSectionLoop;
	DHWEAPON_API const static FName HoldingSectionOut;
	DHWEAPON_API const static FName HoldingSectionBreak;
	
	UPROPERTY(EditAnywhere, Category = "Action")
	EDHActionType ActionType = EDHActionType::Triggering;
	UPROPERTY(EditAnywhere, Category = "Action")
	UAnimMontage * ActionMontage = nullptr;
	UPROPERTY(EditAnywhere, Category = "Action")
	bool bCanMoveOnAction = false;
	UPROPERTY(EditAnywhere, Category = "Action")
	bool bFixCameraOnAction = false;

	UPROPERTY(EditAnywhere, Category = "Damage Datas")
	TArray<FDH_DamageData> DamageData;
};


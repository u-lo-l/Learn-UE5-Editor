#pragma once

#include "CoreMinimal.h"
#include "ActionData.h"
#include "EquipmentData.h"
#include "WeaponDataAsset.generated.h"

UCLASS()
class LEARNASSETDEFINITION_API UWeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<AActor>> WeaponActors;
	UPROPERTY(EditAnywhere)
	FEquipmentData EquipmentData;
	UPROPERTY(EditAnywhere)
	TArray<FActionData> LightActions;

	UPROPERTY(EditAnywhere)
	TArray<FActionData> GuardActions;
	
	UPROPERTY(EditAnywhere)
	FActionData Finisher;

	UPROPERTY(EditAnywhere)
	TArray<FActionData> AirActions;
};

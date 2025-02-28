#pragma once

#include "CoreMinimal.h"
#include "ActionData.h"
#include "EquipmentData.h"
#include "WeaponDataAsset.generated.h"

class ADHWeaponBase;

UCLASS()
class DHWEAPON_API UWeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category="Actor")
	TArray<TSubclassOf<ADHWeaponBase>> WeaponActors;
	UPROPERTY(EditAnywhere, Category="Equipment")
	FEquipmentData EquipmentData;
	UPROPERTY(EditAnywhere, Category="Action|LightAction")
	TArray<FActionData> LightActions;

	UPROPERTY(EditAnywhere, Category="Action|Guard")
	TArray<FActionData> GuardActions;
	
	UPROPERTY(EditAnywhere, Category="Action|Finisher")
	FActionData Finisher;

	UPROPERTY(EditAnywhere, Category="Action|AirCombo")
	TArray<FActionData> AirActions;
};

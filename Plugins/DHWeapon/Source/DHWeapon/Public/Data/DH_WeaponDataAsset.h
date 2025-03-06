#pragma once

#include "CoreMinimal.h"
#include "DH_ActionData.h"
#include "DH_EquipmentData.h"
#include "DH_WeaponActorData.h"
#include "DH_WeaponDataAsset.generated.h"

class UDHEquipBase;
class UDHActionBase;
class ADHWeaponBase;
class FWeaponDataAssetDetailCustomization;
struct FDH_WeaponActorData;

UCLASS()
class DHWEAPON_API UDH_WeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	friend FWeaponDataAssetDetailCustomization;
public:
	void Init(UWorld * InWorld);
private:
	UPROPERTY(EditAnywhere, Category="ActorData")
	TArray<TSubclassOf<ADHWeaponBase>> WeaponActors;
	UPROPERTY(EditAnywhere, Category="ActorData")
	TArray<FDH_WeaponActorData> ActorDatas;

	UPROPERTY(EditAnywhere, Category="EquipmentData")
	TSubclassOf<UDHEquipBase> EquipmentClass;
	UPROPERTY(EditAnywhere, Category="Equipment")
	FDH_EquipmentData EquipmentData;
	
	UPROPERTY(EditAnywhere, Category="Action|Light")
	TSubclassOf<UDHActionBase> LightActionClass;
	UPROPERTY(EditAnywhere, Category="Action|Light")
	TArray<FDH_ActionData> LightActions;

	UPROPERTY(EditAnywhere, Category="Action|Guard")
	TSubclassOf<UDHActionBase> GuardActionClass;
	UPROPERTY(EditAnywhere, Category="Action|Guard")
	FDH_ActionData GuardAction;

	UPROPERTY(EditAnywhere, Category="Action|Finisher")
	TSubclassOf<UDHActionBase> FinisherActionClass;
	UPROPERTY(EditAnywhere, Category="Action|Finisher")
	FDH_ActionData Finisher;
	
	UPROPERTY(EditAnywhere, Category="Action|Air")
	TSubclassOf<UDHActionBase> AirActionClass;
	UPROPERTY(EditAnywhere, Category="Action|Air")
	TArray<FDH_ActionData> AirActions;

private:
	TMap<TObjectPtr<ADHWeaponBase>, FDH_WeaponActorData *> WeaponTable;
};

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

/*
 * Data는 DataAsset에서 참조하고, WeaponActor, Action, Equip같은 UObject들은 각각의 ADHWeaponBase에서 생성한다.
 * -> Spawn Per Actor
 */
UCLASS()
class DHWEAPON_API UDH_WeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	friend FWeaponDataAssetDetailCustomization;
	// ~ Begin UPrimaryDataAsset Interface
public:
	UDH_WeaponDataAsset();
	virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;
	// ~ End UPrimaryDataAsset Interface

	UClass * GetAWeaponClass(int32 Index) const;
	const FDH_WeaponActorData & GetAWeaponData(const UClass * InWeaponActorClass) const;
	const FDH_EquipmentData & GetEquipmentData() const;
	const FDH_ActionData & GetLightActionData(int32 Index) const;
	const FDH_ActionData & GetGuardActionData() const;
	const FDH_ActionData & GetFinisherActionData() const;
	const FDH_ActionData & GetAirActionData(int32 Index) const;
	int32 GetAWeaponClassNum() const;
	int32 GetLightActionDataNum() const;
	int32 GetAirActionDataNum() const;
private:
	void SetWeaponDataTable();
	
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

	//TODO : Hit And Dead Montage
	
private:
	TMap<UClass *, FDH_WeaponActorData *> WeaponDataTable;
};

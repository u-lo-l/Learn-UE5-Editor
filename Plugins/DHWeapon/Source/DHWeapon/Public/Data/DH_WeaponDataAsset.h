#pragma once

#include "CoreMinimal.h"
#include "DH_ActionData.h"
#include "DH_EquipmentData.h"
#include "DH_WeaponActorData.h"
#include "DH_WeaponDataAsset.generated.h"

class UAnimLayerInterface;
class UDHEquipBase;
class UDHActionBase;
class UDHTriggeringActionBase;
class ADHWeaponBase;
class FWeaponDataAssetDetailCustomization;
struct FDH_WeaponActorData;

USTRUCT(BlueprintType)
struct FDirectionalMontages
{
	GENERATED_BODY()
	DHWEAPON_API UAnimMontage * GetMontage(const FVector & Forward, const FVector & Right, const FVector & Direction) const;
	UPROPERTY(EditAnywhere, Category = "Montage")
	UAnimMontage * ForwardMontage;
	UPROPERTY(EditAnywhere, Category = "Montage")
	UAnimMontage * BackwardMontage;
	UPROPERTY(EditAnywhere, Category = "Montage")
	UAnimMontage * RightMontage;
	UPROPERTY(EditAnywhere, Category = "Montage")
	UAnimMontage * LeftMontage;
};

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
	UClass * GetAnimLayer() const;
	UClass * GetAWeaponClass(int32 Index) const;
	UClass * GetEquipClass() const;
	UClass * GetLightActionClass() const;
	UClass * GetHeavyActionClass() const;
	UClass * GetAirActionClass() const;
	UClass * GetDefenseActionClass() const;
	UClass * GetFinisherActionClass() const;

	UAnimMontage * GetDodgeMontage(const FVector & Forward, const FVector & Right, const FVector & Direction) const;

	void GetAWeaponData(const UClass * InWeaponActorClass, const FDH_WeaponActorData * & OutWeaponData) const;
	const FDH_EquipmentData * GetEquipmentData() const;
	const FDH_ActionData * GetLightActionData(int32 Index) const;
	const TArray<FDH_ActionData> * GetLightActionDatas() const;
	const FDH_ActionData * GetHeavyActionData(int32 Index) const;
	const TArray<FDH_ActionData> * GetHeavyActionDatas() const;
	const FDH_ActionData * GetDefenseActionData() const;
	const FDH_ActionData * GetFinisherActionData() const;
	const FDH_ActionData * GetAirActionData(int32 Index) const;
	const TArray<FDH_ActionData> * GetAirActionDatas() const;
	int32 GetAWeaponClassNum() const;
	int32 GetLightActionDataNum() const;
	int32 GetAirActionDataNum() const;

	UAnimMontage * GetHitMontage(const FVector & Forward, const FVector & Right, const FVector & Direction) const;
	UAnimMontage * GetHeavyHitMontage_Thrust() const;
	UAnimMontage * GetHeavyHitMontage_Air() const;
	UAnimMontage * GetRecoverMontage() const;
	UAnimMontage * GetDieMontage() const;
private:
	void SetWeaponDataTable();

private:
	UPROPERTY(EditAnywhere, Category="Movement | Locomotion")
	TSubclassOf<UAnimInstance> AnimLayer;
	UPROPERTY(EditAnywhere, Category="Movement | Dodge")
	FDirectionalMontages DodgeMontages;
	
	UPROPERTY(EditAnywhere, Category="ActorData")
	TArray<TSubclassOf<ADHWeaponBase>> WeaponActorClasses;
	UPROPERTY(EditAnywhere, Category="ActorData")
	TArray<FDH_WeaponActorData> ActorDatas;

	UPROPERTY(EditAnywhere, Category="EquipmentData")
	TSubclassOf<UDHEquipBase> EquipmentClass;
	UPROPERTY(EditAnywhere, Category="Equipment")
	FDH_EquipmentData EquipmentData;
	
	UPROPERTY(EditAnywhere, Category="Action|Light")
	TSubclassOf<UDHTriggeringActionBase> LightActionClass;
	UPROPERTY(EditAnywhere, Category="Action|Light")
	TArray<FDH_ActionData> LightActionDatas;

	UPROPERTY(EditAnywhere, Category="Action|Heavy")
	TSubclassOf<UDHTriggeringActionBase> HeavyActionClass;
	UPROPERTY(EditAnywhere, Category="Action|Heavy")
	TArray<FDH_ActionData> HeavyActionDatas;
	
	UPROPERTY(EditAnywhere, Category="Action|Guard")
	TSubclassOf<UDHActionBase> DefenseActionClass;
	UPROPERTY(EditAnywhere, Category="Action|Guard")
	FDH_ActionData DefenseActionData;

	UPROPERTY(EditAnywhere, Category="Action|FinisherData")
	TSubclassOf<UDHTriggeringActionBase> FinisherActionClass;
	UPROPERTY(EditAnywhere, Category="Action|FinisherData")
	FDH_ActionData FinisherData;
	
	UPROPERTY(EditAnywhere, Category="Action|Air")
	TSubclassOf<UDHTriggeringActionBase> AirActionClass;
	UPROPERTY(EditAnywhere, Category="Action|Air")
	TArray<FDH_ActionData> AirActionDatas;

	UPROPERTY(EditAnywhere, Category="Hit|LightDamage")
	FDirectionalMontages LightDamage;
	UPROPERTY(EditAnywhere, Category="Hit|HeavyDamage")
	UAnimMontage * HeavyDamage_Thrust;
	UPROPERTY(EditAnywhere, Category="Hit|HeavyDamage")
	UAnimMontage * HeavyDamage_Air;
	UPROPERTY(EditAnywhere, Category="Hit|HeavyDamage")
	UAnimMontage * Recover;
	UPROPERTY(EditAnywhere, Category="Hit|Die")
	UAnimMontage * Die;
	
private:
	UPROPERTY()
	TMap<UClass *, FDH_WeaponActorData> WeaponDataTable;
};

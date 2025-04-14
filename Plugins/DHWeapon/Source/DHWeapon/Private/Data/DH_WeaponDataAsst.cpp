#include "DHTriggeringActionBase.h"
#include "DHEquipBase.h"
#include "DHWeaponBase.h"
#include "Data/DH_WeaponDataAsset.h"
#include "UObject/ObjectSaveContext.h"

UAnimMontage * FDirectionalMontages::GetMontage( const FVector & Forward, const FVector & Right, const FVector & Direction ) const
{
	const float DotForward = FVector::DotProduct(Direction, Forward);
	const float DotRight = FVector::DotProduct(Direction, Right);
	if (FMath::Abs(DotForward) > FMath::Acos(FMath::DegreesToRadians(45)))
	{
		return DotForward > 0 ? ForwardMontage : BackwardMontage;
	}
	return DotRight > 0 ? RightMontage : LeftMontage;
}

UDH_WeaponDataAsset::UDH_WeaponDataAsset() { }

void UDH_WeaponDataAsset::PreSave( FObjectPreSaveContext ObjectSaveContext )
{
	Super::PreSave(ObjectSaveContext);
	SetWeaponDataTable();
	for (FDH_WeaponActorData & ActorData : ActorDatas)
	{
		ActorData.UpdateSocketMapOnPreSave();
	}
}

UClass * UDH_WeaponDataAsset::GetAnimLayer() const
{
	return AnimLayer;
}

UClass * UDH_WeaponDataAsset::GetAWeaponClass( int32 Index ) const
{
	if(WeaponActorClasses.IsValidIndex(Index) == false)
		return nullptr;
	return WeaponActorClasses[Index];
}

UClass * UDH_WeaponDataAsset::GetEquipClass() const
{
	return EquipmentClass;
}

UClass * UDH_WeaponDataAsset::GetLightActionClass() const
{
	return LightActionClass;
}

UClass * UDH_WeaponDataAsset::GetHeavyActionClass() const
{
	return HeavyActionClass;
}

UClass * UDH_WeaponDataAsset::GetAirActionClass() const
{
	return AirActionClass;
}

UClass * UDH_WeaponDataAsset::GetDefenseActionClass() const
{
	return DefenseActionClass;
}

UClass * UDH_WeaponDataAsset::GetFinisherActionClass() const
{
	return FinisherActionClass;
}

UAnimMontage * UDH_WeaponDataAsset::GetDodgeMontage( const FVector & Forward, const FVector & Right, const FVector & Direction ) const
{
	return DodgeMontages.GetMontage(Forward, Right, Direction);
}

void UDH_WeaponDataAsset::SetWeaponDataTable()
{
	GLog->Logf(TEXT("%s | Initialization called %p"), *GetName(), this);
	if (WeaponActorClasses.Num() != ActorDatas.Num())
	{
		GLog->Log("Array sizes do not match");
		return ;
	}
	WeaponDataTable.Empty();
	for (int32 i = 0; i < WeaponActorClasses.Num(); i++)
	{
		WeaponDataTable.Add(WeaponActorClasses[i], ActorDatas[i]);
	}
}

void UDH_WeaponDataAsset::GetAWeaponData( const UClass * InWeaponActorClass, const FDH_WeaponActorData * & OutWeaponData ) const
{
	if(WeaponDataTable.Contains(InWeaponActorClass) == false)
		OutWeaponData = nullptr;
	OutWeaponData = &WeaponDataTable[InWeaponActorClass];
}


const FDH_EquipmentData * UDH_WeaponDataAsset::GetEquipmentData() const
{
	return &EquipmentData;
}

const FDH_ActionData * UDH_WeaponDataAsset::GetLightActionData( int32 Index ) const
{
	checkf(LightActionDatas.IsValidIndex(Index), TEXT("LightAction | Invalid Index"));
	return &LightActionDatas[Index];
}

const TArray<FDH_ActionData> * UDH_WeaponDataAsset::GetLightActionDatas() const
{
	return &LightActionDatas;
}

const FDH_ActionData * UDH_WeaponDataAsset::GetHeavyActionData( int32 Index ) const
{
	checkf(HeavyActionDatas.IsValidIndex(Index), TEXT("HeavyAction | Invalid Index"));
	return &HeavyActionDatas[Index];
}

const TArray<FDH_ActionData> * UDH_WeaponDataAsset::GetHeavyActionDatas() const
{
	return &HeavyActionDatas;
}

const FDH_ActionData * UDH_WeaponDataAsset::GetDefenseActionData() const
{
	return &DefenseActionData;
}

const FDH_ActionData * UDH_WeaponDataAsset::GetFinisherActionData() const
{
	return &FinisherData;
}

const FDH_ActionData * UDH_WeaponDataAsset::GetAirActionData( int32 Index ) const
{
	checkf(AirActionDatas.IsValidIndex(Index), TEXT("AirAction | Invalid Index"))
	return &AirActionDatas[Index];
}

const TArray<FDH_ActionData> * UDH_WeaponDataAsset::GetAirActionDatas() const
{
	return &AirActionDatas;
}

int32 UDH_WeaponDataAsset::GetAWeaponClassNum() const
{
	return WeaponActorClasses.Num();
}

int32 UDH_WeaponDataAsset::GetLightActionDataNum() const
{
	return LightActionDatas.Num();
}

int32 UDH_WeaponDataAsset::GetAirActionDataNum() const
{
	return AirActionDatas.Num();
}

UAnimMontage * UDH_WeaponDataAsset::GetHitMontage( const FVector & Forward, const FVector & Right, const FVector & Direction ) const
{
	return LightDamage.GetMontage(Forward, Right, Direction);
}

UAnimMontage * UDH_WeaponDataAsset::GetHeavyHitMontage_Thrust() const
{
	return HeavyDamage_Thrust;
}

UAnimMontage * UDH_WeaponDataAsset::GetHeavyHitMontage_Air() const
{
	return HeavyDamage_Air;
}

UAnimMontage * UDH_WeaponDataAsset::GetRecoverMontage() const
{
	return Recover;
}

UAnimMontage * UDH_WeaponDataAsset::GetDieMontage() const
{
	return Die;
}


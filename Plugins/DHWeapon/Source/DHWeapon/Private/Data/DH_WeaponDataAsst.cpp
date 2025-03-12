#include "DHActionBase.h"
#include "DHEquipBase.h"
#include "DHWeaponBase.h"
#include "Data/DH_WeaponDataAsset.h"
#include "UObject/ObjectSaveContext.h"

UAnimMontage * FDirectionalMontages::GetMontage( const FVector & Forward, const FVector & Right, const FVector & Direction )
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

UClass * UDH_WeaponDataAsset::GetAirActionClass() const
{
	return AirActionClass;
}

UClass * UDH_WeaponDataAsset::GetGuardActionClass() const
{
	return GuardActionClass;
}

UClass * UDH_WeaponDataAsset::GetFinisherActionClass() const
{
	return FinisherActionClass;
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
	checkf(LightActions.IsValidIndex(Index), TEXT("LightAction | Invalid Index"));
	return &LightActions[Index];
}

const TArray<FDH_ActionData> * UDH_WeaponDataAsset::GetLightActionDatas() const
{
	return &LightActions;
}

const FDH_ActionData * UDH_WeaponDataAsset::GetGuardActionData() const
{
	return &GuardAction;
}

const FDH_ActionData * UDH_WeaponDataAsset::GetFinisherActionData() const
{
	return &Finisher;
}

const FDH_ActionData * UDH_WeaponDataAsset::GetAirActionData( int32 Index ) const
{
	checkf(AirActions.IsValidIndex(Index), TEXT("AirAction | Invalid Index"))
	return &AirActions[Index];
}

const TArray<FDH_ActionData> * UDH_WeaponDataAsset::GetAirActionDatas() const
{
	return &AirActions;
}

int32 UDH_WeaponDataAsset::GetAWeaponClassNum() const
{
	return WeaponActorClasses.Num();
}

int32 UDH_WeaponDataAsset::GetLightActionDataNum() const
{
	return LightActions.Num();
}

int32 UDH_WeaponDataAsset::GetAirActionDataNum() const
{
	return AirActions.Num();
}


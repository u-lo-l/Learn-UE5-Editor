#include "DHWeaponBase.h"
#include "Data/DH_WeaponDataAsset.h"
#include "UObject/ObjectSaveContext.h"

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

UClass * UDH_WeaponDataAsset::GetAWeaponClass( int32 Index ) const
{
	check(WeaponActors.IsValidIndex(Index))
	return WeaponActors[Index];
}

void UDH_WeaponDataAsset::SetWeaponDataTable()
{
	GLog->Logf(TEXT("%s | Initialization called %p"), *GetName(), this);
	if (WeaponActors.Num() != ActorDatas.Num())
	{
		GLog->Log("Array sizes do not match");
		return ;
	}
	WeaponDataTable.Empty();
	for (int32 i = 0; i < WeaponActors.Num(); i++)
	{
		WeaponDataTable.Add(WeaponActors[i]->StaticClass(), &ActorDatas[i]);
	}
}

const FDH_WeaponActorData & UDH_WeaponDataAsset::GetAWeaponData( const UClass * InWeaponActorClass ) const
{
	check(WeaponDataTable.Contains(InWeaponActorClass))
	return *WeaponDataTable[InWeaponActorClass];
}


const FDH_EquipmentData & UDH_WeaponDataAsset::GetEquipmentData() const
{
	return EquipmentData;
}

const FDH_ActionData & UDH_WeaponDataAsset::GetLightActionData( int32 Index ) const
{
	checkf(LightActions.IsValidIndex(Index), TEXT("LightAction | Invalid Index"));
	return LightActions[Index];
}

const FDH_ActionData & UDH_WeaponDataAsset::GetGuardActionData() const
{
	return GuardAction;
}

const FDH_ActionData & UDH_WeaponDataAsset::GetFinisherActionData() const
{
	return Finisher;
}

const FDH_ActionData & UDH_WeaponDataAsset::GetAirActionData( int32 Index ) const
{
	checkf(AirActions.IsValidIndex(Index), TEXT("AirAction | Invalid Index"))
	return AirActions[Index];
}

int32 UDH_WeaponDataAsset::GetAWeaponClassNum() const
{
	return WeaponActors.Num();
}

int32 UDH_WeaponDataAsset::GetLightActionDataNum() const
{
	return LightActions.Num();
}

int32 UDH_WeaponDataAsset::GetAirActionDataNum() const
{
	return AirActions.Num();
}


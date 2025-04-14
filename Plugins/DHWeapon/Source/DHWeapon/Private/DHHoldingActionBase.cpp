
#include "DHHoldingActionBase.h"
#include "DHWeapon.h"

void UDHHoldingActionBase::Init( ACharacter * InOwnerCharacter,  ADHWeaponBase * InWeaponActor, const TArray<FDH_ActionData> * InActionDatas )
{
	if (InOwnerCharacter == nullptr)
	{
		UE_LOG(
			Log_DHWeapon,
			Error,
			TEXT("%hs | OwnerCharacter Not Valid"),
			__FUNCTION__
		);
		return ;
	}
	if (InActionDatas == nullptr)
	{
		UE_LOG(
			Log_DHWeapon,
			Error,
			TEXT("%hs | ActionDatas Not Valid"),
			__FUNCTION__
		);
		return ;
	}
	if (InActionDatas->IsEmpty())
	{
		UE_LOG(
			Log_DHWeapon,
			Error,
			TEXT("%hs | ActionDatas is Empty"),
			__FUNCTION__
		);
		return ;
	}
	if (InActionDatas->Num() > 1)
	{
		UE_LOG(
			Log_DHWeapon,
			Error,
			TEXT("%hs | Only One ActionData Allowed"),
			__FUNCTION__
		);
		return ;
	}
	WeaponActor = InWeaponActor;
	OwnerCharacter = InOwnerCharacter;
	ActionData = (*InActionDatas)[0];
}

void UDHHoldingActionBase::Init( ACharacter * InOwnerCharacter, ADHWeaponBase * InWeaponActor, const FDH_ActionData * InActionData )
{
	if (InOwnerCharacter == nullptr)
	{
		UE_LOG(
			Log_DHWeapon,
			Error,
			TEXT("%hs | OwnerCharacter Not Valid"),
			__FUNCTION__
		);
		return ;
	}
	if (InActionData == nullptr)
	{
		UE_LOG(
			Log_DHWeapon,
			Error,
			TEXT("%hs | ActionDatas is Empty"),
			__FUNCTION__
		);
		return ;
	}
	WeaponActor = InWeaponActor;
	OwnerCharacter = InOwnerCharacter;
	ActionData = *InActionData;
}

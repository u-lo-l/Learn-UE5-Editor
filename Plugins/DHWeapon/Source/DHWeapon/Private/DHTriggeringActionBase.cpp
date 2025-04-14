#include "DHTriggeringActionBase.h"
#include "DHWeapon.h"

void UDHTriggeringActionBase::Init( ACharacter * InOwnerCharacter, ADHWeaponBase * InWeaponActor,  const TArray<FDH_ActionData> * InActionDatas )
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
	WeaponActor = InWeaponActor;
	OwnerCharacter = InOwnerCharacter;
	ActionDatas = InActionDatas;
}

void UDHTriggeringActionBase::Init( ACharacter * InOwnerCharacter, ADHWeaponBase * InWeaponActor, const FDH_ActionData * InActionData )
{
	Super::Init(InOwnerCharacter, InWeaponActor, InActionData);
	WeaponActor = InWeaponActor;
	OwnerCharacter = InOwnerCharacter;
}


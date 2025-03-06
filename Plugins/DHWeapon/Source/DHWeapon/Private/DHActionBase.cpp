#include "DHActionBase.h"
#include "DHWeapon.h"

void UDHActionBase::Init( ACharacter * InOwnerCharacter, TArray<FDH_ActionData> * InActionDatas )
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
	OwnerCharacter = InOwnerCharacter;
	ActionDatas = InActionDatas;
}

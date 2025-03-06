#include "DHEquipBase.h"

#include "DHWeapon.h"

void UDHEquipBase::Init
(
	ACharacter * InOwnerCharacter,
	FDH_EquipmentData * InEquipData,
	FDH_EquipmentData * InUnequipData
)
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
	if (InEquipData == nullptr)
	{
		UE_LOG(
			Log_DHWeapon,
			Error,
			TEXT("%hs | EquipData Not Valid"),
			__FUNCTION__
		);
		return ;
	}
	if (InUnequipData == nullptr)
	{
		UE_LOG(
			Log_DHWeapon,
			Error,
			TEXT("%hs | UnequipData Not Valid"),
			__FUNCTION__
		);
		return ;
	}
	OwnerCharacter = InOwnerCharacter;
	EquipData = InEquipData;
	UnequipData = InUnequipData;
}

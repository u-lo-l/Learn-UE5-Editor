#include "DHEquipBase.h"

#include "DHWeapon.h"
#include "Data/DH_EquipmentData.h"
#include "GameFramework/Character.h"

void UDHEquipBase::RequestEquip(FEquipmentDelegate OnMontageBlendingOut)
{
	check(!!OwnerCharacter && !!EquipData)
	
	if (EquipData->bUseEquipMontage == false || EquipData->EquipMontage == nullptr)
	{
		BroadcastEquipDelegates();
		return;
	}
	
	OwnerCharacter->PlayAnimMontage(EquipData->EquipMontage);

 	FOnMontageBlendingOutStarted OnEquipEnd;
	OnEquipEnd.BindLambda([OnMontageBlendingOut](UAnimMontage * Montage, bool bInterrupted) {
		if (OnMontageBlendingOut.IsBound() == true)
			OnMontageBlendingOut.Broadcast();
	});
	AnimInstance->Montage_SetBlendingOutDelegate(OnEquipEnd);
}

void UDHEquipBase::RequestUnequip(FEquipmentDelegate OnMontageBlendingOut)
{
	check(!!OwnerCharacter && !!EquipData)
	if (EquipData->bUseUnequipMontage == false || EquipData->UnequipMontage == nullptr)
	{
		BroadcastUnequipDelegates();
		return;
	}
	
	OwnerCharacter->PlayAnimMontage(EquipData->UnequipMontage);

	FOnMontageBlendingOutStarted OnUnequipEnd;
	OnUnequipEnd.BindLambda([OnMontageBlendingOut](UAnimMontage * Montage, bool bInterrupted) {
		if (OnMontageBlendingOut.IsBound() == true)
			OnMontageBlendingOut.Broadcast();
	});
	AnimInstance->Montage_SetBlendingOutDelegate(OnUnequipEnd);
}

void UDHEquipBase::BroadcastEquipDelegates()
{
	if (OnEquipWeapon.IsBound() == true)
		OnEquipWeapon.Broadcast();
}

void UDHEquipBase::BroadcastUnequipDelegates()
{
	if (OnUnequipWeapon.IsBound() == true)
		OnUnequipWeapon.Broadcast();
}

void UDHEquipBase::LinkAnimLayer()
{
	if (!!AnimInstance)
		AnimInstance->LinkAnimClassLayers(EquipAnimLayer);
}

void UDHEquipBase::Init
(
	ACharacter * InOwnerCharacter,
	const FDH_EquipmentData * InEquipData,
	TSubclassOf<UAnimInstance> EquipAnimLayerClass
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

	OwnerCharacter = InOwnerCharacter;
	EquipData = InEquipData;
	EquipAnimLayer = EquipAnimLayerClass;
	AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
}


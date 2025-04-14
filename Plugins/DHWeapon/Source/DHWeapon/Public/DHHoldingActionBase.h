// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DHActionBase.h"
#include "DHTriggeringActionBase.h"
#include "DHHoldingActionBase.generated.h"

UCLASS(Abstract, Blueprintable)
class DHWEAPON_API UDHHoldingActionBase : public UDHActionBase
{
	GENERATED_BODY()
	friend UDH_WeaponDataAsset;
public:
	virtual void Init(ACharacter * InOwnerCharacter, ADHWeaponBase * InWeaponActor, const TArray<FDH_ActionData> * InActionDatas) override;
	virtual void Init(ACharacter * InOwnerCharacter, ADHWeaponBase * InWeaponActor, const FDH_ActionData * InActionData) override;
	virtual void BeginAction() override {}
	virtual void EndAction() override {}
	
protected:
	FDH_ActionData ActionData;

private:
	virtual void RequestAction(int32 Index = 0) override final {checkf(false, TEXT("%s : Not Triggering Action"), __FILE__);}
	virtual void RequestSubAction(int32 Index = 0) override final {checkf(false, TEXT("%s : Not Triggering Action"), __FILE__);}
};

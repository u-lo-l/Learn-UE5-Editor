#pragma once

#include "CoreMinimal.h"
#include "Interface/IAction.h"
#include "UObject/Object.h"
#include "DHActionBase.generated.h"

class UDH_WeaponDataAsset;

UCLASS(Abstract, Blueprintable)
class DHWEAPON_API UDHActionBase : public UObject, public IIAction
{
	GENERATED_BODY()
	friend UDH_WeaponDataAsset;
public:
	virtual void Init(ACharacter * InOwnerCharacter, ADHWeaponBase * InWeaponActor, const TArray<FDH_ActionData> * InActionDatas) override {};
	virtual void Init(ACharacter * InOwnerCharacter, ADHWeaponBase * InWeaponActor, const FDH_ActionData * InActionData) override {};
		
// protected:
	virtual void RequestAction(int32 Index = 0) override {}
	virtual void RequestSubAction(int32 Index = 0) override {}
	virtual void BeginAction() override {}
	virtual void EndAction() override {}
protected:
	UPROPERTY()
	ACharacter * OwnerCharacter;
	UPROPERTY()
	ADHWeaponBase * WeaponActor = nullptr;
};

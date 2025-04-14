#pragma once

#include "CoreMinimal.h"
#include "DHActionBase.h"
#include "Data/DH_ActionData.h"
#include "UObject/Object.h"
#include "Interface/IAction.h"
#include "DHTriggeringActionBase.generated.h"

class UDH_WeaponDataAsset;

UCLASS(Abstract, Blueprintable)
class DHWEAPON_API UDHTriggeringActionBase : public UDHActionBase
{
	GENERATED_BODY()
	friend UDH_WeaponDataAsset;
public:
	virtual void Init(ACharacter * InOwnerCharacter, ADHWeaponBase * InWeaponActor, const TArray<FDH_ActionData> * InActionDatas) override;
	virtual void Init(ACharacter * InOwnerCharacter, ADHWeaponBase * InWeaponActor, const FDH_ActionData * InActionData) override;
	virtual void RequestAction(int32 Index = 0) override {}
	virtual void RequestSubAction(int32 Index = 0) override {}
	virtual void SetDamageIndex(int32 Index) {}
protected:
	const TArray<FDH_ActionData> * ActionDatas;
	int32 DamageIndex = 0;
private:
	virtual void BeginAction() override final {checkf(false, TEXT("%s : Not HoldingAction"), __FILE__);}
	virtual void EndAction() override final {checkf(false, TEXT("%s : Not HoldingAction"), __FILE__);}
};

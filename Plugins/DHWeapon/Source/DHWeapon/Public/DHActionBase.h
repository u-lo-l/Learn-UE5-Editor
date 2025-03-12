#pragma once

#include "CoreMinimal.h"
#include "Data/DH_ActionData.h"
#include "UObject/Object.h"
#include "Interface/IAction.h"
#include "DHActionBase.generated.h"

class UDH_WeaponDataAsset;

UCLASS(Abstract, Blueprintable)
class DHWEAPON_API UDHActionBase : public UObject, public IIAction
{
	GENERATED_BODY()
	friend UDH_WeaponDataAsset;
public:
	virtual void Init(ACharacter * InOwnerCharacter, const TArray<FDH_ActionData> * InActionDatas) override;
	virtual void RequestAction() override {};
	virtual void OnWeaponBeginOverlap(AActor * HitActor) override {}
	virtual void OnWeaponEndOverlap(AActor * HitActor) override {}
protected:
	UPROPERTY()
	ACharacter * OwnerCharacter;
	const TArray<FDH_ActionData> * ActionDatas;
};

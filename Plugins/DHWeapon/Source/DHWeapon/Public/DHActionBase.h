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
	
protected:
	void Init(ACharacter * InOwnerCharacter, TArray<FDH_ActionData> * InActionDatas);

protected:
	UPROPERTY()
	ACharacter * OwnerCharacter;
	
	TArray<FDH_ActionData> * ActionDatas;
};

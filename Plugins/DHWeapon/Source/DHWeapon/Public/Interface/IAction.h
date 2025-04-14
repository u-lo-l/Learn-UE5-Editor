#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IAction.generated.h"

struct FDH_ActionData;
class ADHWeaponBase;

UINTERFACE()
class UIAction : public UInterface
{
	GENERATED_BODY()
};

class DHWEAPON_API IIAction
{
	GENERATED_BODY()
public:
	virtual void Init(ACharacter * InOwnerCharacter, ADHWeaponBase * InWeaponActor, const TArray<FDH_ActionData> * InActionDatas) = 0;
	virtual void Init(ACharacter * InOwnerCharacter, ADHWeaponBase * InWeaponActor, const FDH_ActionData * InActionData) = 0;
	virtual void RequestAction(int32 Index = 0) = 0;
	virtual void RequestSubAction(int32 Index = 0) = 0;
	virtual void BeginAction() = 0;
	virtual void EndAction() = 0;
};

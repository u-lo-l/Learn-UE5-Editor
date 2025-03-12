#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IAction.generated.h"

UINTERFACE()
class UIAction : public UInterface
{
	GENERATED_BODY()
};

class DHWEAPON_API IIAction
{
	GENERATED_BODY()
public:
	virtual void Init(ACharacter * InOwnerCharacter, const TArray<FDH_ActionData> * InActionDatas) = 0;
	virtual void RequestAction() = 0;
	virtual void OnWeaponBeginOverlap(AActor * HitActor) = 0;
	virtual void OnWeaponEndOverlap(AActor * HitActor) = 0;
	// UFUNCTION()
	// virtual bool TryAction();
	// UFUNCTION()
	// virtual void ExecuteAction();
	// UFUNCTION()
	// virtual void BeginAction();
	// UFUNCTION()
	// virtual void EndAction();
	// UFUNCTION()
	// virtual void OnWeaponBeginOverlap(class ACharacter* InAttacker, AActor* InAttackCauser, class ACharacter* InOther);
	// UFUNCTION()
	// virtual void OnWeaponEndOverlap(class ACharacter* InAttacker, class ACharacter* InOther);
	// UFUNCTION()
	// virtual void OnEquipmentBeginEquip();
	// UFUNCTION()
	// virtual void OnEquipmentEndEquip();
	// UFUNCTION()
	// virtual void OnEquipmentUnequip();
	//
	// virtual void Tick(float DeltaTime);
};

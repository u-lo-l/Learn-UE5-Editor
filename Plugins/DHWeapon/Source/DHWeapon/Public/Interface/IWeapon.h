#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IWeapon.generated.h"

UENUM()
enum EWeaponComponentType : uint8
{
	Mesh, Shape
};

UINTERFACE()
class UIWeapon : public UInterface
{
	GENERATED_BODY()
};

class DHWEAPON_API IIWeapon
{
	GENERATED_BODY()
public:
	virtual const TArray<UMeshComponent *> & GetMeshComponents() const = 0;

	virtual const TArray<UShapeComponent *> & GetColliderComponents() const = 0;

	virtual const UMeshComponent * GetMeshComponent(int32) const = 0;
	virtual UMeshComponent * GetMeshComponent(int32) = 0;
	
	virtual const UShapeComponent * GetColliderComponent(int32) const = 0;
	virtual UShapeComponent * GetColliderComponent(int32) = 0;
	
	virtual void EnableCollision(EWeaponComponentType Type, int32 Index) = 0;
	virtual void DisableCollision(EWeaponComponentType Type, int32 Index) = 0;
	
	virtual void EnableVisibility() = 0;
	virtual void DisableVisibility() = 0;
	
	virtual const FName & GetEquipMeshSocketName(int32 Index) const = 0;
	virtual const FName & GetUnequipMeshSocketName(int32 Index) const = 0;
	virtual const FName & GetColliderSocketName(int32 Index) const = 0;

	virtual void OnEquip() = 0;
	virtual void OnUnequip() = 0;
};

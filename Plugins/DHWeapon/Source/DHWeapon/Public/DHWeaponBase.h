#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/IWeapon.h"
#include "DHWeaponBase.generated.h"

struct FDH_WeaponActorData;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnWeaponOverlap, AActor */*VictimActor*/)

USTRUCT()
struct FShapesInMesh
{
	GENERATED_BODY()
	TArray<UShapeComponent *> Colliders;
};

UCLASS(Abstract, NotPlaceable)
class DHWEAPON_API ADHWeaponBase : public AActor, public IIWeapon
{
	GENERATED_BODY()
public:
	ADHWeaponBase();
protected:
	virtual void BeginPlay() override;

// ~Begin IWeapon
public :
	void Init(ACharacter * InOwnerCharacter, const FDH_WeaponActorData * InActorData);
	
	virtual const TArray<UMeshComponent *> & GetMeshComponents() const override;
	
	virtual const TArray<UShapeComponent *> & GetColliderComponents() const override final;

	virtual const UMeshComponent * GetMeshComponent(int32) const override final;
	virtual UMeshComponent * GetMeshComponent(int32) override final;
	
	virtual const UShapeComponent * GetColliderComponent(int32) const override final;
	virtual UShapeComponent * GetColliderComponent(int32) override final;
	
	virtual void EnableCollision(EWeaponComponentType Type, int32 Index) override;
	virtual void DisableCollision(EWeaponComponentType Type, int32 Index) override;
	
	virtual void EnableVisibility() override final;
	virtual void DisableVisibility() override final;
	
	virtual const FName & GetEquipMeshSocketName(int32 Index) const override final;
	virtual const FName & GetUnequipMeshSocketName(int32 Index) const override final;
	virtual const FName & GetColliderSocketName(int32 Index) const override final;

	UFUNCTION()
	virtual void OnBeginOverlap
	(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
	UFUNCTION()
	virtual void OnEndOverlap
	(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

	/** Attach Components and Set Visibility true if Mesh */
	virtual void OnEquip() override;
	/** Attach Components and Set Visibility false if Mesh */
	virtual void OnUnequip() override;

	FOnWeaponOverlap OnWeaponBeginOverlap;
	FOnWeaponOverlap OnWeaponEndOverlap;
// ~End IWeapon
protected:
	UPROPERTY()
	ACharacter * OwnerCharacter;

	const FDH_WeaponActorData * ActorData;
private:
	UPROPERTY()
	TArray<UMeshComponent *> MeshComponents;
	UPROPERTY()
	TArray<UShapeComponent *> ColliderComponents;
	UPROPERTY()
	TMap<UMeshComponent *, FShapesInMesh> MeshCollidersTable;

	static FAttachmentTransformRules AttachRule;

	UPROPERTY()
	TSet<AActor *> AlreadyOverlapped;
};

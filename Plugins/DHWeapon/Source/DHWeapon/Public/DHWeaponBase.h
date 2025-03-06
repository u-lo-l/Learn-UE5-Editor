#pragma once

#include "CoreMinimal.h"
#include "Data/DH_WeaponActorData.h"
#include "GameFramework/Actor.h"
#include "DHWeaponBase.generated.h"

class FDHWeaponBaseDetailCustomization;
class FWeaponDataAssetDetailCustomization;

UCLASS(NotPlaceable)
class DHWEAPON_API ADHWeaponBase : public AActor
{
	GENERATED_BODY()
	friend FWeaponDataAssetDetailCustomization;
	friend FDHWeaponBaseDetailCustomization;
public:
	// Sets default values for this actor's properties
	ADHWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick( float DeltaTime ) override;
	
public :
	// FORCEINLINE const FDH_WeaponActorData & GetActorData() const { return ActorData; }
public :
	// UPROPERTY(EditAnywhere, NotBlueprintable)
	// FDH_WeaponActorData ActorData;
	
protected:
	// UPROPERTY(EditAnywhere)
	// TArray<FName> MeshSocketNames;
	// UPROPERTY(EditAnywhere)
	// TArray<UMeshComponent*> MeshComponents;
	//
	// UPROPERTY(EditAnywhere)
	// TArray<FName> ColliderSocketNames;
	// UPROPERTY(EditAnywhere)
	// TArray<UShapeComponent*> ColliderComponents;

	UPROPERTY(EditAnywhere)
	TMap<UMeshComponent*, FName> MeshComponents;
	UPROPERTY(EditAnywhere)
	TMap<UShapeComponent*, FName> ColliderComponents;
};

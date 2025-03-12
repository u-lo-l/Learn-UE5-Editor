#pragma once

#include "CoreMinimal.h"
#include "DH_WeaponActorData.generated.h"

// class UDH_WeaponDataAsset;

UENUM()
enum class EDH_ColliderAttachType : uint8
{
	Mesh, Socket
};

USTRUCT()
struct DHWEAPON_API FDH_WeaponActorData
{
	GENERATED_BODY()
private:
	friend class UDH_WeaponDataAsset;
public:
	UPROPERTY(EditAnywhere, Category = "Mesh")
	TArray<FName> MeshNames;
	UPROPERTY(EditAnywhere, Category = "Mesh")
	TArray<FName> MeshUnequipSocketNames;
	UPROPERTY(EditAnywhere, Category = "Mesh")
	TArray<FName> MeshEquipSocketNames;
	UPROPERTY(EditAnywhere, Category = "Collision")
	TArray<FName> ColliderNames;
	UPROPERTY(EditAnywhere, Category = "Collision")
	TArray<FName> ColliderSocketNames;
	
public:
	const FName & GetMeshUnequipSocket(const FName & MeshName) const;
	const FName & GetMeshEquipSocket(const FName & MeshName) const;
	const FName & GetColliderSocket(const FName & MeshName) const;
private:
	void UpdateSocketMapOnPreSave();
	UPROPERTY()
	TMap<FName, FName> MeshUnequipSocketsTable;
	UPROPERTY()
	TMap<FName, FName> MeshEquipSocketsTable;
	UPROPERTY()
	TMap<FName, FName> ColliderSocketsTable;
public:
	const static FName NoNamed;
};

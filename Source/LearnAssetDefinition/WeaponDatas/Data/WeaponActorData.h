#pragma once

#include "CoreMinimal.h"
#include "WeaponActorData.generated.h"

UENUM()
enum class EColliderAttachType : uint8
{
	Mesh, Socket
};

USTRUCT()
struct FWeaponActorData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<USkeletalMesh>> WeaponMeshes;
	UPROPERTY(EditAnywhere)
	TArray<FName> SocketNameToAttachMesh;
	
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UShapeComponent>> Colliders;
	UPROPERTY(EditAnywhere)
	EColliderAttachType AttachType = EColliderAttachType::Mesh;
	UPROPERTY(EditAnywhere)
	TArray<FName> MeshOrSocketNamesToAttachCollider;
	UPROPERTY(EditAnywhere)
	TArray<FVector> SocketLocation;
	UPROPERTY(EditAnywhere)
	TArray<FRotator> SocketRotation;
};

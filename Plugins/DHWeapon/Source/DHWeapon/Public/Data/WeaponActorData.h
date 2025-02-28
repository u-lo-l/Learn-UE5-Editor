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
	
	UPROPERTY(EditAnywhere, Category = "Mesh")
	TArray<TObjectPtr<USkeletalMesh>> WeaponMeshes;
	UPROPERTY(EditAnywhere, Category = "Mesh|Attachment")
	TArray<FName> SocketNameToAttachMesh;
	
	UPROPERTY(EditAnywhere, Category = "Collision")
	TArray<TObjectPtr<UShapeComponent>> Colliders;
	UPROPERTY(EditAnywhere, Category = "Collision")
	EColliderAttachType AttachType = EColliderAttachType::Mesh;
	UPROPERTY(EditAnywhere, Category = "Collision|Attachment", meta = (ToolTip = "MeshName or SocketName to attach"))
	TArray<FName> MeshOrSocketNamesToAttachCollider;
	UPROPERTY(EditAnywhere, Category = "Collision|Attachment")
	TArray<FVector> SocketLocation;
	UPROPERTY(EditAnywhere, Category = "Collision|Attachment")
	TArray<FRotator> SocketRotation;
};

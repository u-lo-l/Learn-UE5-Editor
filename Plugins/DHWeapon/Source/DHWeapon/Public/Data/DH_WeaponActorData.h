#pragma once

#include "CoreMinimal.h"
#include "DH_WeaponActorData.generated.h"

UENUM()
enum class EDH_ColliderAttachType : uint8
{
	Mesh, Socket
};

USTRUCT()
struct FDH_WeaponActorData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category = "Mesh")
	TArray<FName> MeshNames;
	UPROPERTY(EditAnywhere, Category = "Mesh")
	TArray<FName> MeshSocketNames;
	UPROPERTY(EditAnywhere, Category = "Collision")
	TArray<FName> ColliderNames;
	UPROPERTY(EditAnywhere, Category = "Collision")
	TArray<FName> ColliderSocketNames;
};

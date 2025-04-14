#include "DHWeaponBase.h"

#include "DHWeapon.h"
#include "Components/ShapeComponent.h"
#include "Data/DH_WeaponActorData.h"
#include "GameFramework/Character.h"

FAttachmentTransformRules ADHWeaponBase::AttachRule { EAttachmentRule::KeepRelative, true};

// Sets default values
ADHWeaponBase::ADHWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
	this->SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
}

void ADHWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	TArray<USceneComponent*> Components;
	GetRootComponent()->GetChildrenComponents(false, Components);
	for ( USceneComponent* Component : Components )
	{
		if (Component->IsA(UMeshComponent::StaticClass()))
		{
			UMeshComponent* Mesh = Cast<UMeshComponent>(Component);
			MeshComponents.Add(Mesh);
			TArray<USceneComponent*> ChildrenComps;
			Mesh->GetChildrenComponents(true, ChildrenComps);
			FShapesInMesh CollidersInMesh;
			for (USceneComponent * Child : ChildrenComps)
			{
				UShapeComponent * Shape = Cast<UShapeComponent>(Child);
				if (Shape != nullptr)
				{
					Shape->SetCollisionEnabled(ECollisionEnabled::NoCollision);
					Shape->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBeginOverlap);
					Shape->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnEndOverlap);
					CollidersInMesh.Colliders.Add(Shape);
				}
			}
			MeshCollidersTable.Add(Mesh, CollidersInMesh);
		}
		if (Component->IsA(UShapeComponent::StaticClass()))
		{
			UShapeComponent * Shape = Cast<UShapeComponent>(Component);
			Shape->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			Shape->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBeginOverlap);
			Shape->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnEndOverlap);
			ColliderComponents.Add(Shape);
		}
	}
}

void ADHWeaponBase::Init( ACharacter * InOwnerCharacter, const FDH_WeaponActorData * InActorData )
{
	OwnerCharacter = InOwnerCharacter;
	SetInstigator(OwnerCharacter);
	this->ActorData = InActorData;
}

const TArray<UMeshComponent *> & ADHWeaponBase::GetMeshComponents() const
{
	if(!OwnerCharacter || !ActorData)
	{
		UE_LOG(Log_DHWeapon, Warning, TEXT("No Owner or No ActorData"));
	// 	return ;
	}
	
	return MeshComponents;
}

const TArray<UShapeComponent *> & ADHWeaponBase::GetColliderComponents() const
{
	if(!OwnerCharacter || !ActorData)
	{
		UE_LOG(Log_DHWeapon, Warning, TEXT("No Owner or No ActorData"));
	}
	return ColliderComponents;
}

const UMeshComponent * ADHWeaponBase::GetMeshComponent( int32 Index ) const
{
	if(!OwnerCharacter || !ActorData)
	{
		UE_LOG(Log_DHWeapon, Warning, TEXT("No Owner or No ActorData"));
	}
	
	return MeshComponents[Index];
}

UMeshComponent * ADHWeaponBase::GetMeshComponent( int32 Index )
{
	if(!OwnerCharacter || !ActorData)
	{
		UE_LOG(Log_DHWeapon, Warning, TEXT("No Owner or No ActorData"));
		return nullptr;
	}
	
	return MeshComponents[Index];
}

const UShapeComponent * ADHWeaponBase::GetColliderComponent( int32 Index ) const
{
	if(!OwnerCharacter || !ActorData)
	{
		UE_LOG(Log_DHWeapon, Warning, TEXT("No Owner or No ActorData"));
		return nullptr;
	}
	
	return ColliderComponents[Index];
}

UShapeComponent * ADHWeaponBase::GetColliderComponent( int32 Index )
{
	if(!OwnerCharacter || !ActorData)
	{
		UE_LOG(Log_DHWeapon, Warning, TEXT("No Owner or No ActorData"));
		return nullptr;
	}
	
	return ColliderComponents[Index];
}

void ADHWeaponBase::EnableCollision( EWeaponComponentType Type, int32 Index )
{
	if(!OwnerCharacter || !ActorData)
	{
		UE_LOG(Log_DHWeapon, Warning, TEXT("No Owner or No ActorData"));
		return ;
	}
	AlreadyOverlapped.Empty();
	if (Type == Mesh && MeshComponents.IsValidIndex(Index))
	{
		FShapesInMesh & CollidersInMesh = MeshCollidersTable[MeshComponents[Index]];
		for (UShapeComponent* Collider : CollidersInMesh.Colliders)
		{
			Collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
	}
	else if (Type == Shape && ColliderComponents.IsValidIndex(Index))
	{
		ColliderComponents[Index]->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void ADHWeaponBase::DisableCollision( EWeaponComponentType Type, int32 Index )
{
	AlreadyOverlapped.Empty();
	if (Type == Mesh && MeshComponents.IsValidIndex(Index))
	{
		FShapesInMesh & CollidersInMesh = MeshCollidersTable[MeshComponents[Index]];
		for (UShapeComponent* Collider : CollidersInMesh.Colliders)
		{
			Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
	else if (Type == Shape && ColliderComponents.IsValidIndex(Index))
	{
		ColliderComponents[Index]->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ADHWeaponBase::EnableVisibility()
{
	if(!OwnerCharacter || !ActorData)
	{
		UE_LOG(Log_DHWeapon, Warning, TEXT("No Owner or No ActorData"));
		return ;
	}
	
	if (RootComponent != nullptr)
		RootComponent->SetVisibility(true, true);
}

void ADHWeaponBase::DisableVisibility()
{
	if(!OwnerCharacter || !ActorData)
	{
		UE_LOG(Log_DHWeapon, Warning, TEXT("No Owner or No ActorData"));
		return ;
	}
	
	if (RootComponent != nullptr)
		RootComponent->SetVisibility(false, true);
}

const FName & ADHWeaponBase::GetEquipMeshSocketName( int32 Index ) const
{
	if(!OwnerCharacter || !ActorData)
	{
		UE_LOG(Log_DHWeapon, Warning, TEXT("No Owner or No ActorData"));
		return FDH_WeaponActorData::NoNamed;
	}
	
	if (MeshComponents.IsValidIndex(Index) == false)
		return FDH_WeaponActorData::NoNamed;
	return ActorData->GetMeshEquipSocket(MeshComponents[Index]->GetFName());
}

const FName & ADHWeaponBase::GetUnequipMeshSocketName( int32 Index ) const
{
	if(!OwnerCharacter || !ActorData)
	{
		UE_LOG(Log_DHWeapon, Warning, TEXT("No Owner or No ActorData"));
		return FDH_WeaponActorData::NoNamed;
	}
	
	if (MeshComponents.IsValidIndex(Index) == false)
		return FDH_WeaponActorData::NoNamed;
	return ActorData->GetMeshUnequipSocket(MeshComponents[Index]->GetFName());
}

const FName & ADHWeaponBase::GetColliderSocketName( int32 Index ) const
{
	if(!OwnerCharacter || !ActorData)
	{
		UE_LOG(Log_DHWeapon, Warning, TEXT("No Owner or No ActorData"));
		return FDH_WeaponActorData::NoNamed;
	}
	
	if (ColliderComponents.IsValidIndex(Index) == false)
		return FDH_WeaponActorData::NoNamed;
	return ActorData->GetColliderSocket(ColliderComponents[Index]->GetFName());
}

void ADHWeaponBase::OnBeginOverlap
(
	UPrimitiveComponent * OverlappedComponent,
	AActor * OtherActor,
	UPrimitiveComponent * OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult & SweepResult
)
{
	if (OtherActor == OwnerCharacter)
	{
		return ;
	}
	if (AlreadyOverlapped.Contains(OtherActor))
	{
		return;
	}
	AlreadyOverlapped.Add(OtherActor);
	if (OnWeaponBeginOverlap.IsBound() == true)
	{
		OnWeaponBeginOverlap.Broadcast(OtherActor);
	}
}

void ADHWeaponBase::OnEndOverlap
(
	UPrimitiveComponent * OverlappedComponent,
	AActor * OtherActor,
	UPrimitiveComponent * OtherComp,
	int32 OtherBodyIndex
)
{
	if (OtherActor == OwnerCharacter)
	{
		return ;
	}
	if (OnWeaponEndOverlap.IsBound() == true)
		OnWeaponEndOverlap.Broadcast(OtherActor);
}

void ADHWeaponBase::OnEquip()
{
	const TArray<UMeshComponent*> & MeshComps = GetMeshComponents();
	USkeletalMeshComponent * OwnerMesh = OwnerCharacter->GetMesh();
	for (UMeshComponent* Mesh : MeshComps)
	{
		const FName & SocketName = ActorData->GetMeshEquipSocket(Mesh->GetFName());
		Mesh->SetVisibility(SocketName != NAME_None);
		if (SocketName != NAME_None)
		{
			Mesh->AttachToComponent(OwnerMesh, AttachRule, SocketName);
		}
	}
}

void ADHWeaponBase::OnUnequip()
{
	const TArray<UMeshComponent*> & MeshComps = GetMeshComponents();
	USkeletalMeshComponent * OwnerMesh = OwnerCharacter->GetMesh();
	for (UMeshComponent* Mesh : MeshComps)
	{
		const FName & SocketName = ActorData->GetMeshUnequipSocket(Mesh->GetFName());
		Mesh->SetVisibility(SocketName != NAME_None);
		if (SocketName != NAME_None)
		{
			Mesh->AttachToComponent(OwnerMesh, AttachRule, SocketName);
		}
	}
}

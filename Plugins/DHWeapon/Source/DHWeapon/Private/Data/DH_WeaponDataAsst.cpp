#include "DHWeaponBase.h"
#include "Data/DH_WeaponDataAsset.h"

void UDH_WeaponDataAsset::Init(UWorld * InWorld)
{
	// Weapon, Action, Equip간의 델리게이트 연결

	if (WeaponActors.Num() != ActorDatas.Num())
	{
		GLog->Log("Array sizes do not match");
		return ;
	}
	WeaponTable.Empty();
	const uint32 Size = WeaponActors.Num();
	for (uint32 i = 0 ; i < Size ; i++)
	{
		FActorSpawnParameters params;
        params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		UWorld* World = GetWorld();
        ADHWeaponBase * Weapon = InWorld->SpawnActor<ADHWeaponBase>(WeaponActors[i], params);
		WeaponTable.Add(Weapon, &ActorDatas[i]);
	}
	for (auto & Pair : WeaponTable)
	{
		ADHWeaponBase * Weapon = Pair.Key;
		FDH_WeaponActorData * Data = Pair.Value;

		TArray<USceneComponent*> Children;
		Weapon->GetComponents(Children);

		GLog->Log(FString::Printf(TEXT("Total Components : %d"), Size));
		for (const FName & MeshName : Data->MeshNames)
		{
			GLog->Log(FString::Printf(TEXT("Mesh Components : %s"), *MeshName.ToString()));
		}
		for (const FName & ColliderName : Data->ColliderNames)
		{
			GLog->Log(FString::Printf(TEXT("ColliderName Components : %s"), *ColliderName.ToString()));
		}
		TArray<USceneComponent*> ValidComps;
		for (USceneComponent * Comp : Children)
		{
			GLog->Log(FString::Printf(TEXT("Current Components : %s"), *Comp->GetName()));
			if (Data->MeshNames.Contains(Comp->GetFName()))
				ValidComps.Add(Comp);
			else if (Data->ColliderNames.Contains(Comp->GetFName()))
				ValidComps.Add(Comp);
		}

		GLog->Log(TEXT("Component Founds"));
		for (const USceneComponent * Comp : ValidComps)
		{
			GLog->Log(Comp->GetName());
		}
	}
}
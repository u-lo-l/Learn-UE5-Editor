#include "Data/DH_WeaponActorData.h"

const FName FDH_WeaponActorData::NoNamed = NAME_None;

const FName & FDH_WeaponActorData::GetMeshUnequipSocket( const FName & MeshName ) const
{
	if (MeshUnequipSocketsTable.Contains(MeshName) == false)
		return NoNamed;
	return MeshUnequipSocketsTable[MeshName];
}

const FName & FDH_WeaponActorData::GetMeshEquipSocket( const FName & MeshName ) const
{
	if (MeshEquipSocketsTable.Contains(MeshName) == false)
		return NoNamed;
	return MeshEquipSocketsTable[MeshName];
}

const FName & FDH_WeaponActorData::GetColliderSocket( const FName & ColliderName ) const
{
	if (ColliderSocketsTable.Contains(ColliderName) == false)
		return NoNamed;
	return ColliderSocketsTable[ColliderName];
}

void FDH_WeaponActorData::UpdateSocketMapOnPreSave()
{
	MeshEquipSocketsTable.Empty();
	MeshUnequipSocketsTable.Empty();
	ColliderSocketsTable.Empty();

	if ((MeshNames.Num() != MeshUnequipSocketNames.Num()) || (MeshNames.Num() != MeshEquipSocketNames.Num()))
	{
		MeshNames.Empty();
		MeshUnequipSocketNames.Empty();
		MeshEquipSocketNames.Empty();
	}
	uint32 Size = MeshNames.Num();
	for (uint32 i = 0 ; i < Size ; i++)
	{
		MeshUnequipSocketsTable.Add(MeshNames[i], MeshUnequipSocketNames[i]); 
		MeshEquipSocketsTable.Add(MeshNames[i], MeshEquipSocketNames[i]); 
	}

	if (ColliderNames.Num() != ColliderSocketNames.Num())
	{
		ColliderNames.Empty();
		ColliderSocketNames.Empty();
	}
	Size = ColliderNames.Num();
	for (uint32 i = 0 ; i < Size ; i++)
	{
		ColliderSocketsTable.Add(ColliderNames[i], ColliderSocketNames[i]);
	}
}

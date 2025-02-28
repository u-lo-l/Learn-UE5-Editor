#include "DHWeapon.h"

#include "AssetToolsModule.h"

#include "Data/ActionData.h"
#include "Data/WeaponActorData.h"
#include "Data/WeaponDataAsset.h"

#include "Tab/Details/WeaponDataAssetDetailCustomization.h"
#include "Tab/Details/PropertyCustomization/ActionDataInfoDetails.h"
#include "Tab/Details/PropertyCustomization/ActorDataInfoDetails.h"
#include "Tab/Details/PropertyCustomization/DamageDataInfoDetails.h"
#include "Tab/Details/PropertyCustomization/EquipmentDataInfoDetails.h"

#define LOCTEXT_NAMESPACE "FDHWeaponModule"

FDHWeaponModule::FDHWeaponModule()
	: PropertyEditorModule(FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor"))
{
}

void FDHWeaponModule::StartupModule()
{
	GLog->Log("FDHWeaponModule is Starting");
	
	const FName WeaponDataAssetName = UWeaponDataAsset::StaticClass()->GetFName();
	FOnGetDetailCustomizationInstance WeaponDataAssetClassInstance;
	WeaponDataAssetClassInstance.BindStatic(&FWeaponDataAssetDetailCustomization::MakeInstance);
	PropertyEditorModule.RegisterCustomClassLayout
	(
		WeaponDataAssetName,
		WeaponDataAssetClassInstance
	);

	const FName ActionDataName = FActionData::StaticStruct()->GetFName();
	FOnGetPropertyTypeCustomizationInstance ActionDataPropInstance;
	ActionDataPropInstance.BindStatic(&FActionDataInfoDetails::MakeInstance);
	PropertyEditorModule.RegisterCustomPropertyTypeLayout
	(
		ActionDataName,
		ActionDataPropInstance
	);

	const FName ActorDataName = FWeaponActorData::StaticStruct()->GetFName();
	FOnGetPropertyTypeCustomizationInstance ActorDataPropInstance;
	ActorDataPropInstance.BindStatic(&FActorDataInfoDetails::MakeInstance);
	PropertyEditorModule.RegisterCustomPropertyTypeLayout
	(
		ActorDataName,
		ActorDataPropInstance
	);

	const FName EquipmentDataName = FEquipmentData::StaticStruct()->GetFName();
	FOnGetPropertyTypeCustomizationInstance EquipmentDataPropInstance;
	EquipmentDataPropInstance.BindStatic(&FEquipmentDataInfoDetails::MakeInstance);
	PropertyEditorModule.RegisterCustomPropertyTypeLayout
	(
		EquipmentDataName,
		EquipmentDataPropInstance
	);
	
	const FName DamageDataName = FDamageData::StaticStruct()->GetFName();
	FOnGetPropertyTypeCustomizationInstance DamageDataPropInstance;
	DamageDataPropInstance.BindStatic(&FDamageDataInfoDetails::MakeInstance);
	PropertyEditorModule.RegisterCustomPropertyTypeLayout
	(
		DamageDataName,
		DamageDataPropInstance
	);
}

void FDHWeaponModule::ShutdownModule()
{
	GLog->Log("FDHWeaponModule is Finishing");
	const FName PropertyName = UWeaponDataAsset::StaticClass()->GetFName();
	PropertyEditorModule.UnregisterCustomClassLayout(PropertyName);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDHWeaponModule, DHWeapon)
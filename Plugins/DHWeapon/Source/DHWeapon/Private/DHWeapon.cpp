#include "DHWeapon.h"

#include "DHWeaponBase.h"

#include "Data/DH_ActionData.h"
#include "Data/DH_WeaponActorData.h"
#include "Data/DH_WeaponDataAsset.h"

#include "Tab/Details/DHWeaponBaseDetailCustomization.h"
#include "Tab/Details/WeaponDataAssetDetailCustomization.h"
#include "Tab/Details/PropertyCustomization/ActionDataInfoDetails.h"
#include "Tab/Details/PropertyCustomization/ActorDataInfoDetails.h"
#include "Tab/Details/PropertyCustomization/DamageDataInfoDetails.h"
#include "Tab/Details/PropertyCustomization/EquipmentDataInfoDetails.h"

#define LOCTEXT_NAMESPACE "FDHWeaponModule"

DEFINE_LOG_CATEGORY(Log_DHWeapon);

FDHWeaponModule::FDHWeaponModule()
	: PropertyEditorModule(FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor"))
{
}

void FDHWeaponModule::StartupModule()
{
	GLog->Log("FDHWeaponModule is Starting");
	
	const FName WeaponDataAssetName = UDH_WeaponDataAsset::StaticClass()->GetFName();
	FOnGetDetailCustomizationInstance WeaponDataAssetClassInstance;
	WeaponDataAssetClassInstance.BindStatic(&FWeaponDataAssetDetailCustomization::MakeInstance);
	PropertyEditorModule.RegisterCustomClassLayout
	(
		WeaponDataAssetName,
		WeaponDataAssetClassInstance
	);

	const FName WeaponBaseName = ADHWeaponBase::StaticClass()->GetFName();
	FOnGetDetailCustomizationInstance WeaponBaseClassInstance;
	WeaponDataAssetClassInstance.BindStatic(&FDHWeaponBaseDetailCustomization::MakeInstance);
	PropertyEditorModule.RegisterCustomClassLayout
	(
		WeaponBaseName,
		WeaponBaseClassInstance
	);

	const FName ActionDataName = FDH_ActionData::StaticStruct()->GetFName();
	FOnGetPropertyTypeCustomizationInstance ActionDataPropInstance;
	ActionDataPropInstance.BindStatic(&FActionDataInfoDetails::MakeInstance);
	PropertyEditorModule.RegisterCustomPropertyTypeLayout
	(
		ActionDataName,
		ActionDataPropInstance
	);

	const FName ActorDataName = FDH_WeaponActorData::StaticStruct()->GetFName();
	FOnGetPropertyTypeCustomizationInstance ActorDataPropInstance;
	ActorDataPropInstance.BindStatic(&FActorDataInfoDetails::MakeInstance);
	PropertyEditorModule.RegisterCustomPropertyTypeLayout
	(
		ActorDataName,
		ActorDataPropInstance
	);

	const FName EquipmentDataName = FDH_EquipmentData::StaticStruct()->GetFName();
	FOnGetPropertyTypeCustomizationInstance EquipmentDataPropInstance;
	EquipmentDataPropInstance.BindStatic(&FEquipmentDataInfoDetails::MakeInstance);
	PropertyEditorModule.RegisterCustomPropertyTypeLayout
	(
		EquipmentDataName,
		EquipmentDataPropInstance
	);
	
	const FName DamageDataName = FDH_DamageData::StaticStruct()->GetFName();
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
	PropertyEditorModule.UnregisterCustomClassLayout(UDH_WeaponDataAsset::StaticClass()->GetFName());
	PropertyEditorModule.UnregisterCustomClassLayout(ADHWeaponBase::StaticClass()->GetFName());

	PropertyEditorModule.UnregisterCustomPropertyTypeLayout(FDH_WeaponActorData::StaticStruct()->GetFName());
	PropertyEditorModule.UnregisterCustomPropertyTypeLayout(FDH_ActionData::StaticStruct()->GetFName());
	PropertyEditorModule.UnregisterCustomPropertyTypeLayout(FDH_EquipmentData::StaticStruct()->GetFName());
	PropertyEditorModule.UnregisterCustomPropertyTypeLayout(FDH_DamageData::StaticStruct()->GetFName());
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDHWeaponModule, DHWeapon)
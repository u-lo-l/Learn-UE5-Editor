#include "LearnAssetDefinition.h"
#include "AssetToolsModule.h"

#include "WeaponDatas/Data/ActionData.h"
#include "WeaponDatas/Data/WeaponActorData.h"
#include "WeaponDatas/Data/WeaponDataAsset.h"

#include "WeaponDatas/Tab/Details/WeaponDataAssetDetailCustomization.h"
#include "WeaponDatas/Tab/Details/PropertyCustomization/ActionDataInfoDetails.h"
#include "WeaponDatas/Tab/Details/PropertyCustomization/ActorDataInfoDetails.h"
#include "WeaponDatas/Tab/Details/PropertyCustomization/DamageDataInfoDetails.h"
#include "WeaponDatas/Tab/Details/PropertyCustomization/EquipmentDataInfoDetails.h"

#define LOCTEXT_NAMESPACE "FLearnAssetDefinitionModule"

FLearnAssetDefinitionModule::FLearnAssetDefinitionModule()
	: AssetTools(FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get())
	, PropertyEditorModule(FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor"))
{
}

void FLearnAssetDefinitionModule::StartupModule()
{
	GLog->Log("LearnAssetDefinitionModule is Starting");
	
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

void FLearnAssetDefinitionModule::ShutdownModule()
{
	GLog->Log("LearnAssetDefinitionModule is Finishing");
	const FName PropertyName = UWeaponDataAsset::StaticClass()->GetFName();
	PropertyEditorModule.UnregisterCustomClassLayout(PropertyName);
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FLearnAssetDefinitionModule, LearnAssetDefinition)
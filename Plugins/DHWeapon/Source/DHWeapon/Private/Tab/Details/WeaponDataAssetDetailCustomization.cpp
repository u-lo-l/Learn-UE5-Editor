#include "Tab/Details/WeaponDataAssetDetailCustomization.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "Data/WeaponDataAsset.h"

TSharedRef<IDetailCustomization> FWeaponDataAssetDetailCustomization::MakeInstance()
{
	return MakeShareable(new FWeaponDataAssetDetailCustomization());
}

void FWeaponDataAssetDetailCustomization::CustomizeDetails( IDetailLayoutBuilder & DetailBuilder )
{
	IDetailCategoryBuilder& WeaponActorDataCategory = DetailBuilder.EditCategory("WeaponActorData", FText::FromString("Weapon Actor Data"));
    
	WeaponActorDataCategory.AddProperty(GET_MEMBER_NAME_CHECKED(UWeaponDataAsset, WeaponActors))
		.DisplayName(FText::FromString("Weapon Actor Data"))
		.ToolTip(FText::FromString("Data for the weapon actor"));
    
	// EquipmentData 섹션
	IDetailCategoryBuilder& EquipmentDataCategory = DetailBuilder.EditCategory("EquipmentData", FText::FromString("Equipment Data"));
    
	EquipmentDataCategory.AddProperty(GET_MEMBER_NAME_CHECKED(UWeaponDataAsset, EquipmentData))
		.DisplayName(FText::FromString("Equipment Data"))
		.ToolTip(FText::FromString("Data for the equipment"));
    
	// LightActions 배열 섹션
	IDetailCategoryBuilder& LightActionsCategory = DetailBuilder.EditCategory("LightActions", FText::FromString("Light Actions"));
    
	LightActionsCategory.AddProperty(GET_MEMBER_NAME_CHECKED(UWeaponDataAsset, LightActions))
		.DisplayName(FText::FromString("Light Actions"))
		.ToolTip(FText::FromString("Array of light actions"));

	// GuaredActions 배열 섹션
	IDetailCategoryBuilder& GuardActionsCategory = DetailBuilder.EditCategory("GuardActions", FText::FromString("Guard Actions"));
    
	GuardActionsCategory.AddProperty(GET_MEMBER_NAME_CHECKED(UWeaponDataAsset, GuardActions))
		.DisplayName(FText::FromString("Guard Actions"))
		.ToolTip(FText::FromString("Array of guard actions"));
	
	// Finisher 섹션
	IDetailCategoryBuilder& FinisherCategory = DetailBuilder.EditCategory("Finisher", FText::FromString("Finisher Action"));
    
	FinisherCategory.AddProperty(GET_MEMBER_NAME_CHECKED(UWeaponDataAsset, Finisher))
		.DisplayName(FText::FromString("Finisher"))
		.ToolTip(FText::FromString("Finisher action"));

	// AirActions 배열 섹션
	IDetailCategoryBuilder& AirActionsCategory = DetailBuilder.EditCategory("AirActions", FText::FromString("Air Actions"));
    
	AirActionsCategory.AddProperty(GET_MEMBER_NAME_CHECKED(UWeaponDataAsset, AirActions))
		.DisplayName(FText::FromString("Air Actions"))
		.ToolTip(FText::FromString("Array of air actions"));
	
}

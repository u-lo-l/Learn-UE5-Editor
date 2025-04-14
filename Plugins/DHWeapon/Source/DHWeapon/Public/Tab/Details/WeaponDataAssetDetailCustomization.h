#pragma once

#include "CoreMinimal.h"
#include "DetailLayoutBuilder.h"
#include "IDetailCustomization.h"

class IDetailCategoryBuilder;

class DHWEAPON_API FWeaponDataAssetDetailCustomization final
	: public IDetailCustomization
{
	using ThisClass = FWeaponDataAssetDetailCustomization;
public:
	static TSharedRef<IDetailCustomization> MakeInstance();
	virtual void CustomizeDetails( IDetailLayoutBuilder & DetailBuilder ) override;
private:
	static void CreateActorCategory
	(
		IDetailCategoryBuilder & DetailCategoryBuilder,
		IDetailLayoutBuilder & DetailBuilder,
		const TSharedRef<IPropertyHandle> & InActorHandle,
		const TSharedRef<IPropertyHandle> & InActorDataHandle,
		const FString & InCategoryName
	);
	static void CreateEquipmentCategory
	(
		IDetailCategoryBuilder & DetailCategoryBuilder,
		IDetailLayoutBuilder & DetailBuilder,
		const TSharedRef<IPropertyHandle> & InClassHandle,
		const TSharedRef<IPropertyHandle> & InEquipmentHandle,
		const FString & InCategoryName
	);
	static void CreateActionCategory
	(
		IDetailCategoryBuilder & DetailCategoryBuilder,
		IDetailLayoutBuilder & DetailBuilder,
		const TSharedRef<IPropertyHandle> & InClassHandle,
		const TSharedRef<IPropertyHandle> & InActionHandle,
		const FString & InCategoryName
	);
private:
	FWeaponDataAssetDetailCustomization() {}
	static FSlateFontInfo GetBoldFont( float InSize = 9 );
	static FSlateFontInfo GetDetailFont( float InSize = 9 );
	static FSimpleDelegate OnPropertyChanged(IDetailLayoutBuilder & DetailBuilder);

	static TSharedRef<SVerticalBox> CreateActorInfo
	(
		const TSharedRef<IPropertyHandle> & InActorPropertyHandle,
		const TSharedRef<IPropertyHandle> & InActorDataHandle
	);
	static void FindDefaultRootMeshComponentsFromClass
	(
		UClass * InClass,
		const TSharedRef<IPropertyHandleArray> & InMeshArrayHandle,
		const TSharedRef<IPropertyHandleArray> & InMeshUnequipSocketArrayHandle,
		const TSharedRef<IPropertyHandleArray> & InMeshEquipSocketArrayHandle
	);
	static void AddRootMeshesSlateToVerticalBox
	(
		const TSharedRef<SVerticalBox> & InVerticalBox,
		const TSharedRef<IPropertyHandleArray> & InMeshArrayHandle,
		const TSharedRef<IPropertyHandleArray> & InMeshUnequipSocketArrayHandle,
		const TSharedRef<IPropertyHandleArray> & InMeshEquipSocketArrayHandle
	);
	static void FindDefaultRootColliderComponentsFromClass
	(
		UClass * InClass,
		const TSharedRef<IPropertyHandleArray> & InColliderArrayHandle,
		const TSharedRef<IPropertyHandleArray> & InColliderDataArrayHandle
	);
	static void AddRootCollidersSlateToVerticalBox
	(
		const TSharedRef<SVerticalBox> & InVerticalBox,
		const TSharedRef<IPropertyHandleArray> & InColliderArrayHandle,
		const TSharedRef<IPropertyHandleArray> & InColliderDataArrayHandle
	);
};

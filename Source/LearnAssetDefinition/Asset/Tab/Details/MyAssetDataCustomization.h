// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

class LEARNASSETDEFINITION_API FWeaponDataAssetDetailCustomization final
	: public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();
	
	virtual void CustomizeHeader
	(
		TSharedRef<IPropertyHandle> PropertyHandle,
		FDetailWidgetRow & HeaderRow,
		IPropertyTypeCustomizationUtils & CustomizationUtils
	) override;

	virtual void CustomizeChildren
	(
		TSharedRef<IPropertyHandle> PropertyHandle,
		IDetailChildrenBuilder & ChildBuilder,
		IPropertyTypeCustomizationUtils & CustomizationUtils
	) override;
private:
	FWeaponDataAssetDetailCustomization()
	{
		GLog->Log("FMyAssetDataCustomization");
	}
public:
	virtual ~FWeaponDataAssetDetailCustomization() override
	{
		GLog->Log("~FMyAssetDataCustomization");
	}
	
};

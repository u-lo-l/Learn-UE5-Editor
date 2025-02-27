#pragma once

#include "CoreMinimal.h"

class LEARNASSETDEFINITION_API FDamageDataInfoDetails final
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
	void DamageSection( const TSharedRef<IPropertyHandle> & PropertyHandle, IDetailChildrenBuilder & ChildBuilder);
	void LaunchSection( const TSharedRef<IPropertyHandle> & PropertyHandle, IDetailChildrenBuilder & ChildBuilder);
	void SoundSection( const TSharedRef<IPropertyHandle> & PropertyHandle, IDetailChildrenBuilder & ChildBuilder);
	void EffectSection( const TSharedRef<IPropertyHandle> & PropertyHandle, IDetailChildrenBuilder & ChildBuilder);
	void CameraShakeSection( const TSharedRef<IPropertyHandle> & PropertyHandle, IDetailChildrenBuilder & ChildBuilder);
};

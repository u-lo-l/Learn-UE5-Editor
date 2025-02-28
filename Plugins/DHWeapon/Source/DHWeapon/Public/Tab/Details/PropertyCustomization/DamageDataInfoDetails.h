#pragma once

#include "CoreMinimal.h"

class DHWEAPON_API FDamageDataInfoDetails final
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

public:
	static TSharedRef<SWidget> HeaderNameContent( const TSharedRef<IPropertyHandle> & PropertyHandle, IPropertyTypeCustomizationUtils & CustomizationUtils);
	static TSharedRef<SWidget> HeaderValueContent( const TSharedRef<IPropertyHandle> & PropertyHandle, IPropertyTypeCustomizationUtils & CustomizationUtils);

	static TSharedRef<SWidget> DamageNameContent(const TSharedRef<IPropertyHandle> & PropertyHandle);
	static TSharedRef<SWidget> DamageValueContent(const TSharedRef<IPropertyHandle> & PropertyHandle);

	static TSharedRef<SWidget> LaunchNameContent(const TSharedRef<IPropertyHandle> & PropertyHandle);
	static TSharedRef<SWidget> LaunchValueContent(const TSharedRef<IPropertyHandle> & PropertyHandle);

	static TSharedRef<SWidget> SoundNameContent(const TSharedRef<IPropertyHandle> & PropertyHandle);
	static TSharedRef<SWidget> SoundValueContent(const TSharedRef<IPropertyHandle> & PropertyHandle);

	static TSharedRef<SWidget> EffectNameContent(const TSharedRef<IPropertyHandle> & PropertyHandle);
	static TSharedRef<SWidget> EffectValueContent(const TSharedRef<IPropertyHandle> & PropertyHandle);

	static TSharedRef<SWidget> CameraShakeNameContent(const TSharedRef<IPropertyHandle> & PropertyHandle);
	static TSharedRef<SWidget> CameraShakeValueContent(const TSharedRef<IPropertyHandle> & PropertyHandle);
	
private:
	void DamageSection( const TSharedRef<IPropertyHandle> & PropertyHandle, IDetailChildrenBuilder & ChildBuilder);
	void LaunchSection( const TSharedRef<IPropertyHandle> & PropertyHandle, IDetailChildrenBuilder & ChildBuilder);
	void SoundSection( const TSharedRef<IPropertyHandle> & PropertyHandle, IDetailChildrenBuilder & ChildBuilder);
	void EffectSection( const TSharedRef<IPropertyHandle> & PropertyHandle, IDetailChildrenBuilder & ChildBuilder);
	void CameraShakeSection( const TSharedRef<IPropertyHandle> & PropertyHandle, IDetailChildrenBuilder & ChildBuilder);
};

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

class DHWEAPON_API FDHActionDataInfoDetails final
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
	static TSharedRef<SWidget> SDamageData( const TSharedRef<IPropertyHandle> & ElementHandle, IPropertyTypeCustomizationUtils & CustomizationUtils);
};

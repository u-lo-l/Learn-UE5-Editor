#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

class LEARNASSETDEFINITION_API FActionDataInfoDetails final
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
};

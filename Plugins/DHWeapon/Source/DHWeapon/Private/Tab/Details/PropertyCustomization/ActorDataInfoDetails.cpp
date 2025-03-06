#include "Tab/Details/PropertyCustomization/ActorDataInfoDetails.h"

TSharedRef<IPropertyTypeCustomization> FActorDataInfoDetails::MakeInstance()
{
	return MakeShareable(new FActorDataInfoDetails);
}

void FActorDataInfoDetails::CustomizeHeader( TSharedRef<IPropertyHandle> PropertyHandle,
	FDetailWidgetRow & HeaderRow,
	IPropertyTypeCustomizationUtils & CustomizationUtils )
{
}

void FActorDataInfoDetails::CustomizeChildren( TSharedRef<IPropertyHandle> PropertyHandle,
	IDetailChildrenBuilder & ChildBuilder,
	IPropertyTypeCustomizationUtils & CustomizationUtils )
{
}
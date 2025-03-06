#include "Tab/Details/DHWeaponBaseDetailCustomization.h"

TSharedRef<IDetailCustomization> FDHWeaponBaseDetailCustomization::MakeInstance()
{
	return MakeShareable(new FDHWeaponBaseDetailCustomization());
}

void FDHWeaponBaseDetailCustomization::CustomizeDetails( IDetailLayoutBuilder & DetailBuilder )
{
}

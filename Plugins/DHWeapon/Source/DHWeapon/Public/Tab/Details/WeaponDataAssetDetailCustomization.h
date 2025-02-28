#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class DHWEAPON_API FWeaponDataAssetDetailCustomization final
	: public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();
	virtual void CustomizeDetails( IDetailLayoutBuilder & DetailBuilder ) override;
};

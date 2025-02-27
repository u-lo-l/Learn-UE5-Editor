#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class LEARNASSETDEFINITION_API FWeaponDataAssetDetailCustomization final
	: public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();
	virtual void CustomizeDetails( IDetailLayoutBuilder & DetailBuilder ) override;
private:
	FWeaponDataAssetDetailCustomization() {}
};

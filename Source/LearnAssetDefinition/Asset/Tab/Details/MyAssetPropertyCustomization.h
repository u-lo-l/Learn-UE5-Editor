#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class LEARNASSETDEFINITION_API FMyAssetPropertyCustomization final
	: public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();
	virtual void CustomizeDetails( IDetailLayoutBuilder & DetailBuilder ) override;
private:
	FMyAssetPropertyCustomization() {}
};

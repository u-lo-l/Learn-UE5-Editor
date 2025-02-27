#include "MyAssetFactory.h"
#include "Asset/MyAsset.h"

UMyAssetFactory::UMyAssetFactory()
{
	bCreateNew = true;
	SupportedClass = UMyAsset::StaticClass();
}

UObject* UMyAssetFactory::FactoryCreateNew
(
	UClass* InClass,
	UObject* InParent,
	FName InName,
	EObjectFlags Flags,
	UObject* Context,
	FFeedbackContext* Warn,
	FName CallingContext
)
{
	return NewObject<UMyAsset>(InParent, InClass, InName, Flags);
}

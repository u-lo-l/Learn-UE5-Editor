#include "Factory/WeaponDataFactory.h"

#include "Data/WeaponDataAsset.h"

UWeaponDataFactory::UWeaponDataFactory()
{
	bCreateNew = true;
	SupportedClass = UWeaponDataAsset::StaticClass();
}

UObject* UWeaponDataFactory::FactoryCreateNew
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
	return NewObject<UWeaponDataAsset>(InParent, InClass, InName, Flags);
}

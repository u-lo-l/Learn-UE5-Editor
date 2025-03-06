#include "Factory/WeaponDataFactory.h"

#include "Data/DH_WeaponDataAsset.h"

UWeaponDataFactory::UWeaponDataFactory()
{
	bCreateNew = true;
	SupportedClass = UDH_WeaponDataAsset::StaticClass();
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
	return NewObject<UDH_WeaponDataAsset>(InParent, InClass, InName, Flags);
}

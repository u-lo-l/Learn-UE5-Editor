#include "DHWeaponBase.h"

// Sets default values
ADHWeaponBase::ADHWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
	this->SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
}

void ADHWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

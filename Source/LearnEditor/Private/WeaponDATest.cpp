// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponDATest.h"

AWeaponDATest::AWeaponDATest()
{

}

void AWeaponDATest::BeginPlay()
{
	Super::BeginPlay();
	if (DAWeapon == nullptr)
		return ;

	DAWeapon->Init(GetWorld());
}

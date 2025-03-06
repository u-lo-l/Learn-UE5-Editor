// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"

#include "Data/DH_WeaponDataAsset.h"

// Sets default values
ATestCharacter::ATestCharacter(): DA(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


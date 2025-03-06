// Fill out your copyright notice in the Description page of Project Settings.


#include "DHSwordBase.h"

ADHSwordBase::ADHSwordBase()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SkeletalMesh2 = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	if (RootComponent)
	{
		SkeletalMesh->SetupAttachment(RootComponent);
		SkeletalMesh2->SetupAttachment(RootComponent);
	}
}

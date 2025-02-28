#pragma once

#include "CoreMinimal.h"
#include "DamageData.generated.h"

class UFXSystemAsset;

USTRUCT()
struct FDamageData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Type")
	bool bIsFinisher = false;

	UPROPERTY(EditAnywhere, Category = "Type")
	bool bIsNonBlockable = false;
	
	UPROPERTY(EditAnywhere, Category = "Damage", meta = (ClampMin = "0", ClampMax = "1000", UIMin = "0", UIMax = "1000", SliderExponent = "2", Delta = "0.1"))
	float Damage = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Launch")
	bool bUseLaunch = false;
	UPROPERTY(EditAnywhere, Category = "Launch", meta = (ClampMin = "0", ClampMax = "300", UIMin = "0", UIMax = "300", SliderExponent = "2", Delta = "0.1"))
	float LaunchPower = 0.0f;
	UPROPERTY(EditAnywhere, Category = "Launch")
	FVector LaunchDirection = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Sound")
	bool bUseSound = false;
	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundWave> Sound;

	UPROPERTY(EditAnywhere, Category = "Effect")
	bool bUseEffect = false;
	UPROPERTY(EditAnywhere, Category = "Effect")
	TObjectPtr<UFXSystemAsset> Effect;
	UPROPERTY(EditAnywhere, Category = "Effect")
	FVector EffectOffset = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, Category = "Effect")
	FVector EffectScale = FVector::OneVector;

	UPROPERTY(EditAnywhere, Category = "CameraShake")
	bool bUseCameraShake = false;
	UPROPERTY(EditAnywhere, Category = "CameraShake")
	TObjectPtr<UCameraShakeBase> CameraShake;
};

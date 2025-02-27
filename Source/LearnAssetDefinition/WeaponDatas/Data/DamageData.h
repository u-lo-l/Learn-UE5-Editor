#pragma once

#include "CoreMinimal.h"
#include "DamageData.generated.h"

class UFXSystemAsset;

USTRUCT()
struct FDamageData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	bool bIsFinisher = false;

	UPROPERTY(EditAnywhere)
	bool bIsNonBlockable = false;
	
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", ClampMax = "1000", UIMin = "0", UIMax = "1000", SliderExponent = "2", Delta = "0.1"))
	float Damage = 0.0f;

	UPROPERTY(EditAnywhere)
	bool bUseLaunch = false;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", ClampMax = "300", UIMin = "0", UIMax = "300", SliderExponent = "2", Delta = "0.1"))
	float LaunchPower = 0.0f;
	UPROPERTY(EditAnywhere)
	FVector LaunchDirection = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
	bool bUseSound = false;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundWave> Sound;

	UPROPERTY(EditAnywhere)
	bool bUseEffect = false;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UFXSystemAsset> Effect;
	UPROPERTY(EditAnywhere)
	FVector EffectOffset = FVector::ZeroVector;
	UPROPERTY(EditAnywhere)
	FVector EffectScale = FVector::OneVector;

	UPROPERTY(EditAnywhere)
	bool bUseCameraShake = false;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraShakeBase> CameraShake;
};

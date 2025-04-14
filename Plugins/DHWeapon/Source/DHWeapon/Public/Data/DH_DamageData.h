#pragma once

#include "CoreMinimal.h"
#include "DH_DamageData.generated.h"

class UFXSystemAsset;

UENUM()
enum class ELaunchType : uint8
{
	Air,
	Thrust,
};

UENUM()
enum class ELaunchPower : uint32
{
	None = 0,
	Light = 200,
	Middle = 400,
	Heavy = 800
};

USTRUCT()
struct FDH_DamageData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Type")
	bool bIsFinisher = false;

	UPROPERTY(EditAnywhere, Category = "Type")
	bool bIsNonBlockable = false;
	
	UPROPERTY(EditAnywhere, Category = "Damage", meta = (ClampMin = "0", ClampMax = "250", UIMin = "0", UIMax = "250", SliderExponent = "3", Delta = "0.5"))
	float Damage = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Launch")
	bool bUseLaunch = false;
	UPROPERTY(EditAnywhere, Category = "Launch")
	ELaunchPower LaunchPower = ELaunchPower::None;
	UPROPERTY(EditAnywhere, Category = "Launch")
	ELaunchType LaunchType = ELaunchType::Thrust;

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
	TSubclassOf<UCameraShakeBase> CameraShakeClass;
};

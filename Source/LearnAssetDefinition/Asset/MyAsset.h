#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MyAsset.generated.h"

USTRUCT(BlueprintType)
struct FTestData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName Name = "TestData";
	UPROPERTY(EditAnywhere)
	float Value = 123.f;
	UPROPERTY(EditAnywhere, NotBlueprintable)
	bool bUseMontage = true;
	UPROPERTY(EditAnywhere)
	UAnimMontage* Montage = nullptr;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.1", ClampMax = "3.0", UIMin = "0.1", UIMax = "3.0", StepSize = "0.1"))
	float PlayRate = 1.f;
};

UCLASS()
class LEARNASSETDEFINITION_API UMyAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FTestData Data;
};

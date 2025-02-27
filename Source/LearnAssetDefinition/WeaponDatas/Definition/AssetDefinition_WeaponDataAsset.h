#pragma once

#include "CoreMinimal.h"
#include "AssetDefinition.h"
#include "AssetDefinition_WeaponDataAsset.generated.h"

class UWeaponDataAsset;
class FWeaponDataEditor;

UCLASS()
class LEARNASSETDEFINITION_API UAssetDefinition_WeaponDataAsset : public UAssetDefinition
{
	GENERATED_BODY()
public:
	const static FText CategoryPath;
	const static FText DisplayName;
	const static FLinearColor AssetColor;
	
	static void AddAssetCategoryPath(const FString & Path);
	static void AddAssetCategoryPaths(const TArray<FString> & Paths);
private:
	static TArray<FAssetCategoryPath> CategoryPaths;
	
public:
	virtual FText GetAssetDisplayName() const override;
	virtual TSoftClassPtr<> GetAssetClass() const override;
	virtual FLinearColor GetAssetColor() const override;
	virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;
	virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;

private:
	static UWeaponDataAsset * FindCompatibleEditedAsset();
	static FWeaponDataEditor * FindExistingEditor(UWeaponDataAsset * CompatibleEditedAsset);
};

#pragma once

#include "CoreMinimal.h"
#include "AssetDefinition.h"
#include "Asset/MyAsset.h"
#include "Asset/Editor/MyAssetEditor.h"
#include "MyAssetDefinition.generated.h"

class UMyAsset;

UCLASS()
class LEARNASSETDEFINITION_API UMyAssetDefinition : public UAssetDefinition
{
	GENERATED_BODY()
public:
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
	static UMyAsset * FindCompatibleEditedAsset();
	static FMyAssetEditor * FindExistingEditor(UMyAsset * CompatibleEditedAsset);
};

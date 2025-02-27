#pragma once

class UMyAsset;

struct FMyAssetRowData
{
	static TSharedRef<FMyAssetRowData> New
	(
		int32 InNumber, const FString & InName, UMyAsset* InAsset
	);

	int Number;
	FString Name;
	UMyAsset * Asset;
	
private:
	FMyAssetRowData
	(
		int32 InNumber, const FString & InName, UMyAsset * InAsset
	);
};

/*=====================================================================*/

class LEARNASSETDEFINITION_API SWeaponTableRow final
	: public SMultiColumnTableRow<TSharedPtr<FMyAssetRowData>>
{
	SLATE_BEGIN_ARGS(SWeaponTableRow) {}
		SLATE_ARGUMENT(TSharedPtr<FMyAssetRowData>, RowData)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView);

protected:
	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;

private:
	TSharedPtr<FMyAssetRowData> AssetDataPtr;
};


#include "MyAsset_ListRowData.h"

TSharedRef<FMyAssetRowData> FMyAssetRowData::New( int32 InNumber, const FString & InName, class UMyAsset * InAsset )
{
	return MakeShareable(new FMyAssetRowData(InNumber, InName, InAsset));
}

FMyAssetRowData::FMyAssetRowData( int32 InNumber, const FString & InName, UMyAsset * InAsset )
 : Number(InNumber), Name(InName), Asset(InAsset)
{ }

/*=====================================================================*/

void SWeaponTableRow::Construct( const FArguments & InArgs, const TSharedRef<STableViewBase> & OwnerTableView )
{
	this->AssetDataPtr = InArgs._RowData;

	SMultiColumnTableRow::Construct(FSuperRowType::FArguments(), OwnerTableView);
}

TSharedRef<SWidget> SWeaponTableRow::GenerateWidgetForColumn( const FName & InColumnName )
{
	FString Str;
	if (InColumnName == "Number")
		Str = FString::FromInt(AssetDataPtr->Number);
	else if (InColumnName == "Name")
		Str = AssetDataPtr->Name;

	return SNew(STextBlock)
		.Text(FText::FromString(Str));
}

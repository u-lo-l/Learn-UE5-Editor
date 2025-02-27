#pragma once

#include "CoreMinimal.h"
#include "MyAsset_ListRowData.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/SSearchBox.h"

DECLARE_DELEGATE_OneParam(FOnMyAssetItemSelected, TSharedPtr<FMyAssetRowData>);

class SMyAssetListView final : public SCompoundWidget
{
	using ThisClass = SMyAssetListView;
	using FRowDataSPType = TSharedPtr<FMyAssetRowData>;
	using SListViewType = SListView<FRowDataSPType>;
	
public:
	SLATE_BEGIN_ARGS(SMyAssetListView) { }
		SLATE_EVENT(FOnMyAssetItemSelected, OnSelectedItem)
		SLATE_ARGUMENT(TSharedPtr<FMyAssetRowData>, RowData)
	SLATE_END_ARGS()
	void Construct(const FArguments & InArgs);


// ~ Begin Search Box
private:
	void OnTextChanged(const FText& InText);
	void OnTextCommitted(const FText& InText, ETextCommit::Type InType);
	TSharedPtr<SSearchBox> SearchBox;
	FText SearchText;
// ~ End Search Box

	
// ~ Begin List View
public:
	bool HasValidItemsSource() const;
	FRowDataSPType FindRowDataPtrByName(FString InAssetName);
	FRowDataSPType GetFirstItem();
	FRowDataSPType GetFirstSelectedItem();
	void SelectItemByAsset( const UMyAsset* InAsset);
	
private:
	void OnSelectionChanged(FRowDataSPType InDataPtr, ESelectInfo::Type InType);
	TSharedRef<ITableRow> OnGenerateRow(FRowDataSPType InRow, const TSharedRef<STableViewBase>& InTable);
	TSharedPtr<SListViewType> ListView;
	TArray<FRowDataSPType> ListItemsSource;
// ~ End List View

// ~ Begin Info Block
private:
	FText OnGetAssetCount() const;
	TSharedPtr<STextBlock> InfoTextBox;
// ~ End Info Block

	void RefreshAssetList();
	FOnMyAssetItemSelected OnItemSelected;
	
};

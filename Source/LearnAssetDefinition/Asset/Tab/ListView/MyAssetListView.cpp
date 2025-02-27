#include "MyAssetListView.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMyAssetListView::Construct( const FArguments & InArgs )
{
	OnItemSelected = InArgs._OnSelectedItem;
	ListItemsSource.Add(InArgs._RowData);
	
	ChildSlot
	[
		SNew(SVerticalBox)
		
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(2, 0)
		[
			SAssignNew(SearchBox, SSearchBox)
			.SelectAllTextWhenFocused(true)
			.OnTextChanged(this, &ThisClass::OnTextChanged)
			.OnTextCommitted(this, &ThisClass::OnTextCommitted)
		]
		
		+ SVerticalBox::Slot()
		.FillHeight(1)
		[
			SAssignNew(ListView, SListViewType)
			.ListItemsSource(&ListItemsSource)
			.OnGenerateRow(this, &ThisClass::OnGenerateRow)
			.SelectionMode(ESelectionMode::Single)
			.OnSelectionChanged(this, &ThisClass::OnSelectionChanged)
			.HeaderRow
			(
				SNew(SHeaderRow)
				+ SHeaderRow::Column("Number")
					.DefaultLabel(FText::FromString(""))
					.ManualWidth(40)
				+ SHeaderRow::Column("Name")
					.DefaultLabel(FText::FromString("Name"))
			)
		]
		
		+ SVerticalBox::Slot()
		.AutoHeight()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Right)
		.Padding(8, 2)
		[
			SAssignNew(InfoTextBox, STextBlock)
			.Text(this, &ThisClass::OnGetAssetCount)
		]
	];
}

// ~ Begin Search Box
void SMyAssetListView::OnTextChanged( const FText & InText )
{
	GLog->Log("Text Changed");
	if (SearchText.CompareToCaseIgnored(InText) == 0)
		return;

	SearchText = InText;
	RefreshAssetList();
}

void SMyAssetListView::OnTextCommitted( const FText & InText, ETextCommit::Type InType )
{
	GLog->Log("Text Committed");
	OnTextChanged(InText);
}
// ~ End Search Box

// ~ Begin List View
SMyAssetListView::FRowDataSPType SMyAssetListView::FindRowDataPtrByName( FString InAssetName )
{
	GLog->Log("FindRowDataPtrByName");
	for (FRowDataSPType Item : ListItemsSource)
	{
		if (Item->Name == InAssetName)
			return Item;
	}
	return nullptr;
}

bool SMyAssetListView::HasValidItemsSource() const
{
	return ListView->HasValidItemsSource();
}

SMyAssetListView::FRowDataSPType SMyAssetListView::GetFirstItem()
{
	GLog->Log("GetFirstItem");
	ensure(HasValidItemsSource() == true);
	return ListItemsSource[0];
}

// TODO : 하나 반환하는데? 왜지?
SMyAssetListView::FRowDataSPType SMyAssetListView::GetFirstSelectedItem()
{
	GLog->Log("GetFirstSelectedItem");
	TArray<FRowDataSPType> SelectedItems = ListView->GetSelectedItems();

	if (SelectedItems.Num() > 0)
		return SelectedItems[0];

	return nullptr;
}

void SMyAssetListView::SelectItemByAsset( const UMyAsset * InAsset )
{
	GLog->Log("SelectItemByAsset");
	if (HasValidItemsSource() == false)
		return;

	for (const FRowDataSPType Item : ListItemsSource)
	{
		if (Item->Asset == InAsset)
		{
			ListView->SetSelection(Item);
			return;
		}
	}
}

void SMyAssetListView::OnSelectionChanged( FRowDataSPType InDataPtr, ESelectInfo::Type InType )
{
	if (InDataPtr.IsValid() == false)
		return;

	GLog->Log("SelectionChanged");

	if (OnItemSelected.IsBound())
		OnItemSelected.Execute(InDataPtr);
}

TSharedRef<ITableRow> SMyAssetListView::OnGenerateRow( FRowDataSPType InRow, const TSharedRef<STableViewBase> & InTable )
{
	return SNew(SWeaponTableRow, InTable)
			.RowData(InRow);
}
// ~ End List View


// ~ Begin Info Block
FText SMyAssetListView::OnGetAssetCount() const
{
	GLog->Log("OnGetAssetCount");
	const FString & Str = FString::Printf(L"%d Finds", ListItemsSource.Num());

	return FText::FromString(Str);
}
// ~ End Info Block

void SMyAssetListView::RefreshAssetList()
{
	GLog->Log("TODO : Reading MyAssetList");
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION

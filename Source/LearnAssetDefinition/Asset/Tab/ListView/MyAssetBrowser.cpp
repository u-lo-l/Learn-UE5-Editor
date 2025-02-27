// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAssetBrowser.h"

#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "SlateOptMacros.h"
#include "Asset/MyAsset.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMyAssetBrowser::Construct( const FArguments & InArgs )
{
	OnOpenNewAsset = InArgs._OnOpenNewAsset;
	
	FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));

	FAssetPickerConfig Config = CreateAssetPickerConfig();
	this->ChildSlot
	[
		SNew(SBorder)
		.Padding(3)
		.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
		[
			ContentBrowserModule.Get().CreateAssetPicker(Config)
		]
	];
}

void SMyAssetBrowser::OnRequestOpenAssets( const TArray<FAssetData> & SelectedAssets)
{
	GLog->Log("TODO : Config.OnAssetEnterPressed");
	if (SelectedAssets.IsEmpty() == true)
		return ;
	UMyAsset * SelectedAsset = Cast<UMyAsset>(SelectedAssets[0].GetAsset());
	
	OnOpenNewAsset.ExecuteIfBound(SelectedAsset);
}

void SMyAssetBrowser::OnRequestOpenAsset( const FAssetData & AssetData)
{
	GLog->Log("TODO : Config.OnAssetDoubleClicked");
	UMyAsset * SelectedAsset = Cast<UMyAsset>(AssetData.GetAsset());
	OnOpenNewAsset.ExecuteIfBound(SelectedAsset);
}

FReply SMyAssetBrowser::OnKeyDown( const FGeometry & MyGeometry, const FKeyEvent & InKeyEvent )
{
	return SCompoundWidget::OnKeyDown(MyGeometry, InKeyEvent);
}

void SMyAssetBrowser::SelectAsset( const UMyAsset * InAsset )
{
	GLog->Log("TODO : SelectAsset");
	// FAssetData AssetData(InAsset);
	//
	// if (AssetData.IsValid())
	// {
	// 	const TArray<FAssetData> CurrentSelection = GetCurrentSelectionDelegate.Execute();
	//
	// 	if ( !CurrentSelection.Contains(AssetData) )
	// 	{
	// 		TArray<FAssetData> AssetsToSelect;
	// 		AssetsToSelect.Add(AssetData);
	//
	// 		SyncToAssetsDelegate.Execute(AssetsToSelect);
	// 	}
	// }
}

FAssetPickerConfig SMyAssetBrowser::CreateAssetPickerConfig()
{
	FAssetPickerConfig Config;

	Config.Filter.bRecursivePaths = true;
	Config.Filter.ClassPaths.Add(UMyAsset::StaticClass()->GetClassPathName());

	Config.InitialAssetViewType = EAssetViewType::Column;
	Config.bAddFilterUI = true;
	Config.bShowPathInColumnView = true;
	Config.bSortByPathInColumnView = true;

	Config.OnAssetDoubleClicked = FOnAssetDoubleClicked::CreateSP(this, &SMyAssetBrowser::OnRequestOpenAsset);

	Config.OnGetAssetContextMenu = FOnGetAssetContextMenu::CreateLambda([](const TArray<FAssetData>& SelectedAssets) -> TSharedRef<SWidget> {
		GLog->Log("TODO : Config.OnGetAssetContextMenu"); // 우클릭
		return SNew(SBox);
	});
	Config.OnAssetTagWantsToBeDisplayed = FOnShouldDisplayAssetTag::CreateLambda([](FName AssetType, FName TagName)->bool {
		GLog->Log("TODO : Config.OnAssetTagWantsToBeDisplayed");
		return false;
	});
	Config.OnAssetEnterPressed = FOnAssetEnterPressed::CreateSP(this, &SMyAssetBrowser::OnRequestOpenAssets);

	// Config.OnShouldFilterAsset = FOnShouldFilterAsset::CreateLambda([](const FAssetData& InAssetData)->bool {
	// 	GLog->Log("TODO : Config.OnShouldFilterAsset");
	// 	return true;
	// });
	Config.GetCurrentSelectionDelegates.Add(&GetCurrentSelectionDelegate);
	
	Config.SetFilterDelegates.Add(&SetFilterDelegate);
	
	Config.bFocusSearchBoxWhenOpened = false;
	
	// RegisterAdvancedAssetCategory통해 Regist해야함.
	// Config.DefaultFilterMenuExpansion = EAssetTypeCategories::Animation;

	// Config.SaveSettingsName = SettingsIniSection;
	
	TArray<UObject::FAssetRegistryTag> AssetRegistryTags;
	UMyAsset::StaticClass()->GetDefaultObject()->GetAssetRegistryTags(AssetRegistryTags);
	for(UObject::FAssetRegistryTag& AssetRegistryTag : AssetRegistryTags)
	{
		Config.HiddenColumnNames.Add(AssetRegistryTag.Name.ToString());
	}
	Config.HiddenColumnNames.Add(TEXT("Class"));
	Config.HiddenColumnNames.Add(TEXT("Type"));
	
	// ToolTip 필요 없어
	// Config.OnIsAssetValidForCustomToolTip = FOnIsAssetValidForCustomToolTip::CreateLambda([](const FAssetData& AssetData) {
	// 	return AssetData.IsAssetLoaded();
	// });
	// Config.OnGetCustomAssetToolTip = FOnGetCustomAssetToolTip::CreateLambda([](FAssetData& AssetData)->TSharedRef<SToolTip> {
	// 	GLog->Log("TODO : Config.OnGetCustomAssetToolTip");
	// 	return SNew(SToolTip);
	// });
	// Config.OnVisualizeAssetToolTip = FOnVisualizeAssetToolTip::CreateLambda([](const TSharedPtr<SWidget>& TooltipContent, FAssetData& AssetData)->bool {
	// 	GLog->Log("TODO : Config.OnVisualizeAssetToolTip");
	// 	return true;
	// });
	// Config.OnAssetToolTipClosing = FOnAssetToolTipClosing::CreateLambda([]() {
	// 	// Do Nothing
	// });


	return Config;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

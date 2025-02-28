
#include "Tab/Browser/SWeaponDataBrowser.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "SlateOptMacros.h"
#include "Data/WeaponDataAsset.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SWeaponDataBrowser::Construct( const FArguments & InArgs )
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

void SWeaponDataBrowser::OnRequestOpenAssets( const TArray<FAssetData> & SelectedAssets)
{
	if (SelectedAssets.IsEmpty() == true)
		return ;
	UWeaponDataAsset * SelectedAsset = Cast<UWeaponDataAsset>(SelectedAssets[0].GetAsset());
	
	OnOpenNewAsset.ExecuteIfBound(SelectedAsset);
}

void SWeaponDataBrowser::OnRequestOpenAsset( const FAssetData & AssetData)
{
	UWeaponDataAsset * SelectedAsset = Cast<UWeaponDataAsset>(AssetData.GetAsset());
	OnOpenNewAsset.ExecuteIfBound(SelectedAsset);
}

FReply SWeaponDataBrowser::OnKeyDown( const FGeometry & MyGeometry, const FKeyEvent & InKeyEvent )
{
	return SCompoundWidget::OnKeyDown(MyGeometry, InKeyEvent);
}

void SWeaponDataBrowser::SelectAsset( const UWeaponDataAsset * InAsset )
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

FAssetPickerConfig SWeaponDataBrowser::CreateAssetPickerConfig()
{
	FAssetPickerConfig Config;

	Config.Filter.bRecursivePaths = true;
	Config.Filter.ClassPaths.Add(UWeaponDataAsset::StaticClass()->GetClassPathName());

	Config.InitialAssetViewType = EAssetViewType::Column;
	Config.bAddFilterUI = true;
	Config.bShowPathInColumnView = true;
	Config.bSortByPathInColumnView = true;

	Config.OnAssetDoubleClicked = FOnAssetDoubleClicked::CreateSP(this, &SWeaponDataBrowser::OnRequestOpenAsset);

	Config.OnGetAssetContextMenu = FOnGetAssetContextMenu::CreateLambda([](const TArray<FAssetData>& SelectedAssets) -> TSharedRef<SWidget> {
		GLog->Log("TODO : Config.OnGetAssetContextMenu"); // 우클릭
		return SNew(SBox);
	});
	Config.OnAssetTagWantsToBeDisplayed = FOnShouldDisplayAssetTag::CreateLambda([](FName AssetType, FName TagName)->bool {
		GLog->Log("TODO : Config.OnAssetTagWantsToBeDisplayed");
		return false;
	});
	Config.OnAssetEnterPressed = FOnAssetEnterPressed::CreateSP(this, &SWeaponDataBrowser::OnRequestOpenAssets);

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
	UWeaponDataAsset::StaticClass()->GetDefaultObject()->GetAssetRegistryTags(AssetRegistryTags);
	for(UObject::FAssetRegistryTag& AssetRegistryTag : AssetRegistryTags)
	{
		Config.HiddenColumnNames.Add(AssetRegistryTag.Name.ToString());
	}
	Config.HiddenColumnNames.Add(TEXT("Class"));
	Config.HiddenColumnNames.Add(TEXT("Type"));

	return Config;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

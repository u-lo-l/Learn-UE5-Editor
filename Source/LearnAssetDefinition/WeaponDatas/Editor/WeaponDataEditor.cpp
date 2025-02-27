// ReSharper disable CppMemberFunctionMayBeConst
#include "WeaponDataEditor.h"

#include "WeaponDatas/Data/WeaponDataAsset.h"
#include "WeaponDatas/Tab/Browser/SWeaponDataBrowser.h"

const FName FWeaponDataEditor::EditorName = FName("WeaponDataEditor");
const FName FWeaponDataEditor::BrowserTabName = FName("BrowserTab");
const FName FWeaponDataEditor::DetailsTabName = FName("DetailsTab");
const bool FWeaponDataEditor::bCreateDefaultStandaloneMenu = true;
const bool FWeaponDataEditor::bCreateDefaultToolbar = true;
const EToolkitMode::Type FWeaponDataEditor::Mode = EToolkitMode::Standalone;
const FName FWeaponDataEditor::AppIndicator = FName("WeaponDataEditor");
const FName FWeaponDataEditor::LayoutName = FName("WeaponEditor_Layout");
const FName FWeaponDataEditor::ToolkitName = FName("WeaponDataEditorToolkit");
const FString FWeaponDataEditor::WorldCentricPrefix = FString("WeaponDA_");
const FLinearColor FWeaponDataEditor::WorldCentricTabColor = FLinearColor(0.0f, 0.5f, 1.0f);
const TSharedRef<FTabManager::FLayout> FWeaponDataEditor::TabLayout = CreateTabLayout();

TSharedRef<FTabManager::FLayout> FWeaponDataEditor::CreateTabLayout()
{
	TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout(ThisClass::LayoutName)
	-> AddArea(
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
		->Split
		(
			FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.175f)
				->AddTab(BrowserTabName, ETabState::OpenedTab)
				->SetHideTabWell(true)
			)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.825f)
				->AddTab(DetailsTabName, ETabState::OpenedTab)
				->SetHideTabWell(true)
			)
		)
	);
	return Layout;
}

FWeaponDataEditor::FWeaponDataEditor()
	: PropertyEditorModule(FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor"))
{
}


FName FWeaponDataEditor::GetToolkitFName() const
{
	return ThisClass::ToolkitName;
}

FText FWeaponDataEditor::GetToolkitName() const
{
	if (CurrentEditingAsset == nullptr)
		return this->GetBaseToolkitName();
	return GetLabelForObject(CurrentEditingAsset);
}

FText FWeaponDataEditor::GetBaseToolkitName() const
{
	return FText::FromName(ThisClass::ToolkitName);
}

FString FWeaponDataEditor::GetWorldCentricTabPrefix() const
{
	return ThisClass::WorldCentricPrefix;
}

FLinearColor FWeaponDataEditor::GetWorldCentricTabColorScale() const
{
	return ThisClass::WorldCentricTabColor;
}

void FWeaponDataEditor::RegisterTabSpawners( const TSharedRef<FTabManager> & InTabManager )
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	const FOnSpawnTab OnListViewSpawnDelegate = FOnSpawnTab::CreateSP(this, &FWeaponDataEditor::OnSpawnBrowserTab);
	const FOnSpawnTab OnDetailViewSpawnDelegate = FOnSpawnTab::CreateSP(this, &FWeaponDataEditor::OnSpawnDetailTab);

	InTabManager->RegisterTabSpawner(FWeaponDataEditor::BrowserTabName, OnListViewSpawnDelegate)
	.SetDisplayName(FText::FromString("MyAsset Browser"))
	.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Blueprint"))
	.SetMenuType(ETabSpawnerMenuType::Enabled);
	
	InTabManager->RegisterTabSpawner(FWeaponDataEditor::DetailsTabName, OnDetailViewSpawnDelegate)
	.SetDisplayName(FText::FromString("Details"))
	.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Blueprint"));
}

FName FWeaponDataEditor::GetEditorName() const
{
	return ThisClass::EditorName;
}

void FWeaponDataEditor::FocusWindow( UObject * ObjectToFocusOn )
{
	FAssetEditorToolkit::FocusWindow(ObjectToFocusOn);
	CurrentEditingAsset = Cast<UWeaponDataAsset>(ObjectToFocusOn);
	BrowserTab->SelectAsset(CurrentEditingAsset);
	DetailsTab->SetObject(CurrentEditingAsset);
}

void FWeaponDataEditor::OpenMyAssetEditor(UWeaponDataAsset * InAsset)
{
	GLog->Logf(L"Opening FWeaponDataEditor : %s", *InAsset->GetName()); // 한 번 출력되는거 확인함.
	ensureMsgf(InAsset != nullptr, L"Asset Not Valid");

	BrowserTab = SNew(SWeaponDataBrowser)
		.OnOpenNewAsset(this, &ThisClass::OnOpenNewAsset);
	FDetailsViewArgs Args;
	Args.NameAreaSettings = FDetailsViewArgs::ENameAreaSettings::HideNameArea;
	Args.ViewIdentifier = "WeaponDAEditorDetails";
	DetailsTab = PropertyEditorModule.CreateDetailView(Args);
	CurrentEditingAsset = InAsset;
	DetailsTab->SetObject(CurrentEditingAsset);
	
	InitAssetEditor(Mode, nullptr, AppIndicator, TabLayout, true, false, InAsset, true, true);
}

TSharedRef<SDockTab> FWeaponDataEditor::OnSpawnBrowserTab( const FSpawnTabArgs & InArgs )
{
	ensureMsgf(BrowserTab.IsValid(), L"BrowserTab Not Valid");
	return SNew(SDockTab)
	[
		BrowserTab.ToSharedRef()
	];
}

TSharedRef<SDockTab> FWeaponDataEditor::OnSpawnDetailTab( const FSpawnTabArgs & InArgs )
{
	ensureMsgf(DetailsTab.IsValid(), L"DetailsTab Not Valid");
	return SNew(SDockTab)
	[
		DetailsTab.ToSharedRef()	
	];
}

void FWeaponDataEditor::OnOpenNewAsset( UWeaponDataAsset * InAsset )
{
	GLog->Logf(L"Opening FWeaponDataEditor : %s", *InAsset->GetName());
	CurrentEditingAsset = InAsset;
	DetailsTab->SetObject(CurrentEditingAsset);
	FocusWindow(CurrentEditingAsset);
}

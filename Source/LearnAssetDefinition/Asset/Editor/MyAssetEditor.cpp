#include "MyAssetEditor.h"
#include "Asset/MyAsset.h"
#include "Asset/Tab/Details/MyAssetPropertyCustomization.h"
#include "Asset/Tab/ListView/MyAssetBrowser.h"
#include "Asset/Tab/ListView/MyAssetListView.h"

const FName FMyAssetEditor::EditorName = "MyAssetEditor";
const FName FMyAssetEditor::BrowserTabName = FName("BrowserTab");
const FName FMyAssetEditor::DetailsTabName = FName("DetailsTab");
const bool FMyAssetEditor::bCreateDefaultStandaloneMenu = true;
const bool FMyAssetEditor::bCreateDefaultToolbar = true;
const EToolkitMode::Type FMyAssetEditor::Mode = EToolkitMode::Standalone;
const FName FMyAssetEditor::AppIndicator = FName("MyAssetEditor");
const TSharedRef<FTabManager::FLayout> FMyAssetEditor::TabLayout = CreateTabLayout();

TSharedRef<FTabManager::FLayout> FMyAssetEditor::CreateTabLayout()
{
	
	GLog->Log("Creating TabLayout"); // 한 번 출력되는거 확인함.
	
	TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("MyAssetLayout")
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

FName FMyAssetEditor::GetToolkitFName() const
{
	return "MyAssetEditor";
}

FText FMyAssetEditor::GetToolkitName() const
{
	if (CurrentEditingAsset == nullptr)
		return FText::FromString(L"MyAssetEditor");
	return GetLabelForObject(CurrentEditingAsset);
}

FText FMyAssetEditor::GetBaseToolkitName() const
{
	return FText::FromString("MyAssetEditorBase");
}

FString FMyAssetEditor::GetWorldCentricTabPrefix() const
{
	return TEXT("MyAsset: ");
}

FLinearColor FMyAssetEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.0f, 0.5f, 1.0f);
}

void FMyAssetEditor::RegisterTabSpawners( const TSharedRef<FTabManager> & InTabManager )
{
	GLog->Log("RegisterTabSpawners");
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	const FOnSpawnTab OnListViewSpawnDelegate = FOnSpawnTab::CreateSP(this, &FMyAssetEditor::OnSpawnListViewTab);
	const FOnSpawnTab OnDetailViewSpawnDelegate = FOnSpawnTab::CreateSP(this, &FMyAssetEditor::OnSpawnDetailTab);

	InTabManager->RegisterTabSpawner(FMyAssetEditor::BrowserTabName, OnListViewSpawnDelegate)
	.SetDisplayName(FText::FromString("MyAsset Browser"))
	.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Blueprint"))
	.SetMenuType(ETabSpawnerMenuType::Enabled);
	
	InTabManager->RegisterTabSpawner(FMyAssetEditor::DetailsTabName, OnDetailViewSpawnDelegate)
	.SetDisplayName(FText::FromString("Details"))
	.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Blueprint"));
}

FName FMyAssetEditor::GetEditorName() const
{
	return FName("MyAssetEditor");
}

void FMyAssetEditor::FocusWindow( UObject * ObjectToFocusOn )
{
	FAssetEditorToolkit::FocusWindow(ObjectToFocusOn);
	CurrentEditingAsset = Cast<UMyAsset>(ObjectToFocusOn);
	BrowserTab->SelectAsset(CurrentEditingAsset);
	DetailsTab->SetObject(CurrentEditingAsset);
}

void FMyAssetEditor::OnListViewSelectedItem( TSharedPtr<FMyAssetRowData> InRowDataPtr )
{
	GLog->Log("TODO : OnListViewSelectedItem");
}

void FMyAssetEditor::OpenMyAssetEditor(UMyAsset * InAsset)
{
	GLog->Logf(L"Opening FMyAssetEditor : %s", *InAsset->GetName()); // 한 번 출력되는거 확인함.
	ensureMsgf(InAsset != nullptr, L"Asset Not Valid");
	FPropertyEditorModule & PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	BrowserTab = SNew(SMyAssetBrowser)
		.OnOpenNewAsset(this, &ThisClass::OnOpenNewAsset);
	FDetailsViewArgs Args;
	Args.NameAreaSettings = FDetailsViewArgs::ENameAreaSettings::HideNameArea;
	Args.ViewIdentifier = "MyAssetEditorDetails";
	DetailsTab = PropertyEditorModule.CreateDetailView(Args);
	CurrentEditingAsset = InAsset;
	DetailsTab->SetObject(CurrentEditingAsset);
	
	InitAssetEditor(Mode, nullptr, AppIndicator, TabLayout, true, false, InAsset, true, true);
}

TSharedRef<SDockTab> FMyAssetEditor::OnSpawnListViewTab( const FSpawnTabArgs & InArgs )
{
	ensureMsgf(BrowserTab.IsValid(), L"BrowserTab Not Valid");
	return SNew(SDockTab)
	[
		BrowserTab.ToSharedRef()
	];
}

TSharedRef<SDockTab> FMyAssetEditor::OnSpawnDetailTab( const FSpawnTabArgs & InArgs )
{
	ensureMsgf(DetailsTab.IsValid(), L"DetailsTab Not Valid");
	return SNew(SDockTab)
	[
		DetailsTab.ToSharedRef()	
	];
}

void FMyAssetEditor::OnOpenNewAsset( UMyAsset * InAsset )
{
	GLog->Logf(L"Opening FMyAssetEditor : %s", *InAsset->GetName());
	CurrentEditingAsset = InAsset;
	DetailsTab->SetObject(CurrentEditingAsset);
	FocusWindow(CurrentEditingAsset);
}

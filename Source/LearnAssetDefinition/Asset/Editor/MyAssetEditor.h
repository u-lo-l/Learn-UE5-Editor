#pragma once

#include "CoreMinimal.h"
#include "Asset/MyAsset.h"

struct FMyAssetRowData;
class SMyAssetBrowser;

class LEARNASSETDEFINITION_API FMyAssetEditor final
	: public FAssetEditorToolkit
{
	using ThisClass = FMyAssetEditor;
	friend class UMyAssetDefinition;
public:
	void OpenMyAssetEditor(UMyAsset* InAsset);
private:
	FMyAssetEditor() {}
	static TSharedRef<FTabManager::FLayout> CreateTabLayout();
public:
	const static FName EditorName;
private:
	const static bool bCreateDefaultStandaloneMenu;
	const static bool bCreateDefaultToolbar;
	const static EToolkitMode::Type Mode;
	const static FName AppIndicator;
	const static TSharedRef<FTabManager::FLayout> TabLayout;

	const static FName BrowserTabName;
	const static FName DetailsTabName;
public:
	virtual FName GetToolkitFName() const override;
	virtual FText GetToolkitName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual FName GetEditorName() const override;
	virtual void FocusWindow(UObject * ObjectToFocusOn = nullptr) override;

private:
	void OnListViewSelectedItem(TSharedPtr<FMyAssetRowData> InRowDataPtr);
	
private:
	TSharedRef<SDockTab> OnSpawnListViewTab(const FSpawnTabArgs& InArgs);
	TSharedRef<SDockTab> OnSpawnDetailTab(const FSpawnTabArgs& InArgs);

private:
	TSharedPtr<SMyAssetBrowser> BrowserTab = nullptr;
	TSharedPtr<IDetailsView> DetailsTab = nullptr;

	void OnOpenNewAsset(UMyAsset * InAsset);
	TObjectPtr<UMyAsset> CurrentEditingAsset;
};


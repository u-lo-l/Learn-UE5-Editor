#pragma once

class SWeaponDataBrowser;
class UWeaponDataAsset;

class DHWEAPON_API FWeaponDataEditor final
	: public FAssetEditorToolkit
{
	using ThisClass = FWeaponDataEditor;
	friend class UAssetDefinition_WeaponDataAsset;
public:
	void OpenMyAssetEditor(UWeaponDataAsset* InAsset);
private:
	FWeaponDataEditor();
	static TSharedRef<FTabManager::FLayout> CreateTabLayout();
public:
	const static FName EditorName;
private:
	const static bool bCreateDefaultStandaloneMenu;
	const static bool bCreateDefaultToolbar;
	const static FName BrowserTabName;
	const static FName DetailsTabName;
	const static EToolkitMode::Type Mode;
	const static FName AppIndicator;
	const static FName LayoutName;
	const static FName ToolkitName;
	const static FString WorldCentricPrefix;
	const static FLinearColor WorldCentricTabColor;
	const static TSharedRef<FTabManager::FLayout> TabLayout;

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
	TSharedRef<SDockTab> OnSpawnBrowserTab(const FSpawnTabArgs& InArgs);
	TSharedRef<SDockTab> OnSpawnDetailTab(const FSpawnTabArgs& InArgs);
//
private:
	TSharedPtr<SWeaponDataBrowser> BrowserTab = nullptr;
	TSharedPtr<IDetailsView> DetailsTab = nullptr;

	void OnOpenNewAsset(UWeaponDataAsset * InAsset);
	TObjectPtr<UWeaponDataAsset> CurrentEditingAsset;

	FPropertyEditorModule & PropertyEditorModule;
};


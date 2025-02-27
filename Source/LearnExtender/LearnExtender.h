#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FContentBrowserModule;
class FLevelEditorModule;

class FLearnExtenderModule : public IModuleInterface
{
public:
    FLearnExtenderModule();
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    void StartUpMenuBarExtension();
    void StartUpMenuExtension();
    void StartUpToolBarExtension();
    void StartUpContentBrowserExtension();

    void ShutDownMenuBarBarExtension();
    void ShutdownMenuExtension();
    void ShutdownToolBarExtension();
    
    FLevelEditorModule & LevelEditorModule;
    FContentBrowserModule & ContentBrowserModule;
    
    TSharedPtr<FExtender> LevelEditorExtender;

    TArray<TSharedRef<const FExtensionBase>> MenuBarExtensions;
    TArray<TSharedRef<const FExtensionBase>> ToolBarExtensions;
    

    TArray<FString> FolderPathsSelected;
    TArray<FAssetData> AssetsDataSelected;

    void MenuBarExtensionDelegate(FMenuBarBuilder& MenuBarBuilder);

    void AddContentBrowserMenuEntry(FMenuBuilder & MenuBuilder);


    TSharedRef<FExtender> OnExtendPathMenu(const TArray<FString> & SelectedPaths);
    TSharedRef<FExtender> OnExtendAssetMenu(const TArray<FAssetData> & SelectedAssets);
};



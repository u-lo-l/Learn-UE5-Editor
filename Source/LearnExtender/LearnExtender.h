#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

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

    void ShutDownMenuBarBarExtension();
    void ShutdownMenuExtension();
    void ShutdownToolBarExtension();
    
    FLevelEditorModule & LevelEditorModule;
    TSharedPtr<FExtender> Extender;

    TArray<TSharedRef<const FExtensionBase>> MenuBarExtensions;
    TArray<TSharedRef<const FExtensionBase>> ToolBarExtensions;

    void MenuBarExtensionDelegate(FMenuBarBuilder& MenuBarBuilder);
};

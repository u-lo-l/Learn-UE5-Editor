#pragma once

#include "CoreMinimal.h"
#include "IAssetTools.h"
#include "Modules/ModuleManager.h"

class FLearnAssetDefinitionModule final : public IModuleInterface
{
public:
    FLearnAssetDefinitionModule();
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    IAssetTools & AssetTools;
    FPropertyEditorModule & PropertyEditorModule;
};

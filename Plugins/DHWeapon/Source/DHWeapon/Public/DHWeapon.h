// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FDHWeaponModule : public IModuleInterface
{
public:
	FDHWeaponModule();
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
private:
	FPropertyEditorModule & PropertyEditorModule;
};

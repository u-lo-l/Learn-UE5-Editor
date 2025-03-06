// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(Log_DHWeapon, Log, All);

class FDHWeaponModule final : public IModuleInterface
{
public:
	FDHWeaponModule();
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
private:
	FPropertyEditorModule & PropertyEditorModule;
};

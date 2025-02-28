#include "Definition/AssetDefinition_WeaponDataAsset.h"
#include "Data/WeaponDataAsset.h"
#include "Editor/WeaponDataEditor.h"


const FText UAssetDefinition_WeaponDataAsset::CategoryPath = FText::FromString("WeaponDA");
const FText UAssetDefinition_WeaponDataAsset::DisplayName = FText::FromString("WeaponDataAsset") ;
const FLinearColor UAssetDefinition_WeaponDataAsset::AssetColor = FLinearColor(.5f,1,.5f,1);;
TArray<FAssetCategoryPath> UAssetDefinition_WeaponDataAsset::CategoryPaths
{
	FAssetCategoryPath(CategoryPath)
};

void UAssetDefinition_WeaponDataAsset::AddAssetCategoryPath( const FString & Path )
{
	CategoryPaths.Add(FAssetCategoryPath(FText::FromString(Path)));
}

void UAssetDefinition_WeaponDataAsset::AddAssetCategoryPaths( const TArray<FString> & Paths )
{
	for (const FString& Path : Paths)
		CategoryPaths.Add(FAssetCategoryPath(FText::FromString(Path)));
}

FText UAssetDefinition_WeaponDataAsset::GetAssetDisplayName() const
{
	return ThisClass::DisplayName;
}

TSoftClassPtr<> UAssetDefinition_WeaponDataAsset::GetAssetClass() const
{
	return UWeaponDataAsset::StaticClass();
}

FLinearColor UAssetDefinition_WeaponDataAsset::GetAssetColor() const
{
	return ThisClass::AssetColor;
}

TConstArrayView<FAssetCategoryPath> UAssetDefinition_WeaponDataAsset::GetAssetCategories() const
{
	return CategoryPaths;
}

EAssetCommandResult UAssetDefinition_WeaponDataAsset::OpenAssets( const FAssetOpenArgs & OpenArgs ) const
{
	if (OpenArgs.Assets.IsEmpty())
	{
		GLog->Log(TEXT("OpenArgs.Assets is empty"));
		return EAssetCommandResult::Unhandled;
	}

	const FAssetData & AssetToOpen = OpenArgs.Assets[0];

#if WITH_EDITOR
	const bool bForceNewEditor = FSlateApplication::Get().GetModifierKeys().IsShiftDown();
	if (!bForceNewEditor)
	{
		UWeaponDataAsset * CompatibleEditedAsset = FindCompatibleEditedAsset();
		if (CompatibleEditedAsset != nullptr)
		{
			FWeaponDataEditor * ExistingEditor = FindExistingEditor(CompatibleEditedAsset);
			if (ExistingEditor != nullptr)
			{
				ExistingEditor->FocusWindow(AssetToOpen.GetAsset());
				return EAssetCommandResult::Handled;
			}
		}
	}
#endif
	TSharedRef<FWeaponDataEditor> Editor = MakeShareable<FWeaponDataEditor>(new FWeaponDataEditor());
	Editor->OpenMyAssetEditor(Cast<UWeaponDataAsset>(AssetToOpen.GetAsset()));
	return EAssetCommandResult::Handled;
}

UWeaponDataAsset * UAssetDefinition_WeaponDataAsset::FindCompatibleEditedAsset()
{
	UWeaponDataAsset * CompatibleEditedAsset = nullptr;
#if WITH_EDITOR
	TArray<UObject *> AllEditedAssets
		= GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->GetAllEditedAssets();
	for (UObject * EditedAsset : AllEditedAssets)
	{
		if (UWeaponDataAsset * EditedAnimAsset = Cast<UWeaponDataAsset>(EditedAsset))
		{
			CompatibleEditedAsset = EditedAnimAsset;
			break;
		}
	}
#endif
	return CompatibleEditedAsset;
}

FWeaponDataEditor * UAssetDefinition_WeaponDataAsset::FindExistingEditor( UWeaponDataAsset * CompatibleEditedAsset )
{
	TArray<IAssetEditorInstance *> AssetEditors
		= GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->FindEditorsForAsset(CompatibleEditedAsset);
	for (IAssetEditorInstance* ExistingEditor : AssetEditors)
	{
		if (ExistingEditor->GetEditorName() == FWeaponDataEditor::EditorName)
		{
			FWeaponDataEditor * MyEditor = static_cast<FWeaponDataEditor*>(ExistingEditor);
			if (MyEditor != nullptr)
				return MyEditor;
		}
	}
	return nullptr;
}

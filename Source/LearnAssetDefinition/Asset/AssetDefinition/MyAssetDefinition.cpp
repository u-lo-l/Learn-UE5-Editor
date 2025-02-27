#include "MyAssetDefinition.h"
#include "Asset/MyAsset.h"
#include "AssetDefinition.h"
#include "Asset/Editor/MyAssetEditor.h"
#include "Toolkits/IToolkit.h"


TArray<FAssetCategoryPath> UMyAssetDefinition::CategoryPaths
{
	FAssetCategoryPath(FText::FromString("MyCustomCategory")),
};

void UMyAssetDefinition::AddAssetCategoryPath( const FString & Path )
{
	CategoryPaths.Add(FAssetCategoryPath(FText::FromString(Path)));
}

void UMyAssetDefinition::AddAssetCategoryPaths( const TArray<FString> & Paths )
{
	for (const FString& Path : Paths)
		CategoryPaths.Add(FAssetCategoryPath(FText::FromString(Path)));
}

FText UMyAssetDefinition::GetAssetDisplayName() const
{
	return FText::FromString("MyAssetDisplayName");
}

TSoftClassPtr<> UMyAssetDefinition::GetAssetClass() const
{
	return UMyAsset::StaticClass();
}

FLinearColor UMyAssetDefinition::GetAssetColor() const
{
	return FLinearColor(.5f,1,.5f,1);
}

TConstArrayView<FAssetCategoryPath> UMyAssetDefinition::GetAssetCategories() const
{
	return CategoryPaths;
}

EAssetCommandResult UMyAssetDefinition::OpenAssets( const FAssetOpenArgs & OpenArgs ) const
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
		UMyAsset * CompatibleEditedAsset = FindCompatibleEditedAsset();
		if (CompatibleEditedAsset != nullptr)
		{
			FMyAssetEditor * ExistingEditor = FindExistingEditor(CompatibleEditedAsset);
			if (ExistingEditor != nullptr)
			{
				ExistingEditor->FocusWindow(AssetToOpen.GetAsset());
				return EAssetCommandResult::Handled;
			}
		}
	}
#endif
	TSharedRef<FMyAssetEditor> Editor = MakeShareable<FMyAssetEditor>(new FMyAssetEditor());
	Editor->OpenMyAssetEditor(Cast<UMyAsset>(AssetToOpen.GetAsset()));
	return EAssetCommandResult::Handled;
}

UMyAsset * UMyAssetDefinition::FindCompatibleEditedAsset()
{
	UMyAsset * CompatibleEditedAsset = nullptr;
#if WITH_EDITOR
	TArray<UObject *> AllEditedAssets
		= GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->GetAllEditedAssets();
	for (UObject * EditedAsset : AllEditedAssets)
	{
		if (UMyAsset * EditedAnimAsset = Cast<UMyAsset>(EditedAsset))
		{
			CompatibleEditedAsset = EditedAnimAsset;
			break;
		}
	}
#endif
	return CompatibleEditedAsset;
}

FMyAssetEditor * UMyAssetDefinition::FindExistingEditor(UMyAsset * CompatibleEditedAsset)
{
	TArray<IAssetEditorInstance *> AssetEditors
		= GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->FindEditorsForAsset(CompatibleEditedAsset);
	for (IAssetEditorInstance* ExistingEditor : AssetEditors)
	{
		if (ExistingEditor->GetEditorName() == FName("MyAssetEditor"))
		{
			FMyAssetEditor * MyEditor = static_cast<FMyAssetEditor*>(ExistingEditor);
			if (MyEditor != nullptr)
				return MyEditor;
		}
	}
	return nullptr;
}
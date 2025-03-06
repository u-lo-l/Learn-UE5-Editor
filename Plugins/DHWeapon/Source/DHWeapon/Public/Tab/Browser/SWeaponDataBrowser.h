#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "ContentBrowserDelegates.h"

struct FAssetPickerConfig;
class UDH_WeaponDataAsset;

DECLARE_DELEGATE_OneParam(FOnOpenNewWeapoDataAsset, UDH_WeaponDataAsset*);

class DHWEAPON_API SWeaponDataBrowser final : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWeaponDataBrowser) {}
		SLATE_EVENT(FOnOpenNewWeapoDataAsset, OnOpenNewAsset)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct( const FArguments & InArgs );

	void OnRequestOpenAssets(const TArray<FAssetData>& SelectedAssets);

	void OnRequestOpenAsset(const FAssetData& AssetData);

	virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;
	void SelectAsset( const UDH_WeaponDataAsset* InAsset);

	FOnOpenNewWeapoDataAsset OnOpenNewAsset;
private:
	FAssetPickerConfig CreateAssetPickerConfig();

	/** Delegate called to open a new asset for editing */
	
	/** delegate to sync the asset picker to selected assets */
	FSyncToAssetsDelegate SyncToAssetsDelegate;
	FGetCurrentSelectionDelegate GetCurrentSelectionDelegate;

	/** Delegate used to set the AR filter after the fact */
	FSetARFilterDelegate SetFilterDelegate;
};

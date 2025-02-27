#include "MyAssetPropertyCustomization.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "Asset/MyAsset.h"

TSharedRef<IDetailCustomization> FMyAssetPropertyCustomization::MakeInstance()
{
	return MakeShareable(new FMyAssetPropertyCustomization());
}

void FMyAssetPropertyCustomization::CustomizeDetails( IDetailLayoutBuilder & DetailBuilder )
{
	IDetailCategoryBuilder& MyAssetRowCategoryBuilder = DetailBuilder.EditCategory("MyAsset", FText::FromString(" - MyAsset Data"));
	IDetailPropertyRow & MyAssetRow = MyAssetRowCategoryBuilder.AddProperty("MyAsset");
	MyAssetRow.ShouldAutoExpand(true);
}

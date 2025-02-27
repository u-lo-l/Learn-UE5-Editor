#include "MyAssetDataCustomization.h"

#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "IDetailGroup.h"
#include "IPropertyUtilities.h"
#include "Asset/MyAsset.h"

TSharedRef<IPropertyTypeCustomization> FWeaponDataAssetDetailCustomization::MakeInstance()
{
	return MakeShareable(new FWeaponDataAssetDetailCustomization);
}

void FWeaponDataAssetDetailCustomization::CustomizeHeader
(
	TSharedRef<IPropertyHandle> PropertyHandle,
	FDetailWidgetRow & HeaderRow,
	IPropertyTypeCustomizationUtils & CustomizationUtils
)
{

}

void FWeaponDataAssetDetailCustomization::CustomizeChildren
(
	TSharedRef<IPropertyHandle> PropertyHandle,
	IDetailChildrenBuilder & ChildBuilder,
	IPropertyTypeCustomizationUtils & CustomizationUtils
)
{
	GLog->Log(L"CustomizeChildren");
	if (!PropertyHandle->IsValidHandle())
	{
		return;
	}
	
	TSharedRef<IPropertyHandle> UseMontageHandle =
		PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FTestData, bUseMontage)).ToSharedRef();
	bool bUseMontage;
	UseMontageHandle->GetValue(bUseMontage);
	
	TSharedRef<IPropertyHandle> MontageHandle =
		PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FTestData, Montage)).ToSharedRef();
	UObject * AnimMontageObject = nullptr;
	MontageHandle->GetValue(AnimMontageObject);
	MontageHandle->SetOnPropertyValueChanged(FSimpleDelegate::CreateLambda([&CustomizationUtils]() {
		CustomizationUtils.GetPropertyUtilities()->ForceRefresh();
	}));
	UAnimMontage * CurrentAssignedMontage = Cast<UAnimMontage>(AnimMontageObject);
	
	ChildBuilder
	.AddProperty(PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FTestData, Name)).ToSharedRef());

	ChildBuilder
	.AddProperty(PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FTestData, Value)).ToSharedRef());

	IDetailGroup & MontageGroup = ChildBuilder.AddGroup("Montage", FText::FromString("Montage"));

	MontageGroup.SetDisplayMode(EDetailGroupDisplayMode::Group);
	MontageGroup.HeaderRow()
	.NameContent()
	[
		SNew(STextBlock)
		.Text(FText::FromString("Montage"))
		.Font(IDetailLayoutBuilder::GetDetailFont())
	]
	.ValueContent()
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.VAlign(VAlign_Center).HAlign(HAlign_Fill)
		[
			SNew(STextBlock)
			.Text(FText::FromString("Use Montage  "))
			.Font(IDetailLayoutBuilder::GetDetailFont())
		]
		+ SHorizontalBox::Slot()
		.Padding(10)
		[
			SNew(SCheckBox)
			.IsChecked(bUseMontage)
			.OnCheckStateChanged_Lambda([this, &CustomizationUtils, UseMontageHandle](ECheckBoxState State) {
				UseMontageHandle->SetValue(State == ECheckBoxState::Checked);
				CustomizationUtils.GetPropertyUtilities()->ForceRefresh();
			})
		]
	];
	
	
	MontageGroup
	.AddPropertyRow(PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FTestData, Montage)).ToSharedRef())
	.Visibility(bUseMontage == true ? EVisibility::Visible : EVisibility::Hidden);

	
	FDetailWidgetRow & MontageWidgetRow = MontageGroup.AddWidgetRow();
	
	MontageGroup
	.AddPropertyRow(PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FTestData, PlayRate)).ToSharedRef())
	.Visibility(bUseMontage == true ? EVisibility::Visible : EVisibility::Hidden);
	
	MontageWidgetRow
	.NameContent()
	[
		SNew(STextBlock)
		.Text(FText::FromString("Montage Widget:"))
		.Font(IDetailLayoutBuilder::GetDetailFont())
	]
	.ValueContent()
	[
		SNew(STextBlock)
		.Text(FText::FromString("Montage Value"))
		.Font(IDetailLayoutBuilder::GetDetailFont())
	]
	.Visibility(bUseMontage == true && CurrentAssignedMontage != nullptr ? EVisibility::Visible : EVisibility::Hidden);
}

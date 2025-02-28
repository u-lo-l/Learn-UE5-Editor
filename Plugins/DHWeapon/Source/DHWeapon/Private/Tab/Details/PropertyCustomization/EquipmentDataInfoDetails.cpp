#include "Tab/Details/PropertyCustomization/EquipmentDataInfoDetails.h"

#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "IPropertyUtilities.h"
#include "Data/EquipmentData.h"
#include "Style/WeaponDataStyle.h"

TSharedRef<IPropertyTypeCustomization> FEquipmentDataInfoDetails::MakeInstance()
{
	return MakeShareable(new FEquipmentDataInfoDetails);
}

void FEquipmentDataInfoDetails::CustomizeHeader( TSharedRef<IPropertyHandle> PropertyHandle,
	FDetailWidgetRow & HeaderRow,
	IPropertyTypeCustomizationUtils & CustomizationUtils )
{
}

void FEquipmentDataInfoDetails::CustomizeChildren( TSharedRef<IPropertyHandle> PropertyHandle,
	IDetailChildrenBuilder & ChildBuilder,
	IPropertyTypeCustomizationUtils & CustomizationUtils )
{
	if (!PropertyHandle->IsValidHandle())
	{
		return;
	}
	TSharedRef<IPropertyHandle> UseEquipMontageHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FEquipmentData, bUseEquipMontage)).ToSharedRef();
	TSharedRef<IPropertyHandle> EquipMontageHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FEquipmentData, EquipMontage)).ToSharedRef();
	TSharedRef<IPropertyHandle> CanMoveOnEquipHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FEquipmentData, CanMoveOnEquip)).ToSharedRef();
	TSharedRef<IPropertyHandle> UseUnequipMontageHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FEquipmentData, bUseUnequipMontage)).ToSharedRef();
	TSharedRef<IPropertyHandle> UnequipMontageHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FEquipmentData, UnequipMontage)).ToSharedRef();
	TSharedRef<IPropertyHandle> CanMoveOnUnequipHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FEquipmentData, CanMoveOnUnequip)).ToSharedRef();

	bool bUseEquipMontage;
	bool bCanMoveOnEquip;
	bool bUseUnequipMontage;
	bool bCanMoveOnUnequip;
	
	UseEquipMontageHandle->GetValue(bUseEquipMontage);
	CanMoveOnEquipHandle->GetValue(bCanMoveOnEquip);
	UseUnequipMontageHandle->GetValue(bUseUnequipMontage);
	CanMoveOnUnequipHandle->GetValue(bCanMoveOnUnequip);
	
	ChildBuilder.AddCustomRow(FText::FromString("Equip Section"))
	BEGIN_BORDER_NAMECONTENT(FWeaponDataStyle::GetEquipDataBackGroundColor())
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.VAlign(VAlign_Center).AutoHeight()
		[
			SNew(SCheckBox)
			.IsChecked(bUseEquipMontage)
			.OnCheckStateChanged_Lambda([UseEquipMontageHandle, EquipMontageHandle, &CustomizationUtils](ECheckBoxState State)->void {
				UseEquipMontageHandle->SetValue(State == ECheckBoxState::Checked);
				if (State != ECheckBoxState::Checked)
					EquipMontageHandle->SetValue(static_cast<UObject*>(nullptr));
				CustomizationUtils.GetPropertyUtilities()->ForceRefresh();
			})
			[
				SNew(STextBlock)
				.Text(FText::FromString("Use Equip Montage"))
				.Font(IDetailLayoutBuilder::GetDetailFont())
				.ColorAndOpacity(bUseEquipMontage ? FColor::White : FColor(62,62,62))
			]
		]
		+ SVerticalBox::Slot()
		.VAlign(VAlign_Center).AutoHeight()
		[
			WeaponDAEditorHelper::CreateCheckBox
			(
				CanMoveOnEquipHandle,
				FText::FromString("Can Move On Equip"),
				CustomizationUtils
			)
		]
	]
	END_BORDER_NAMECONTENT
	BEGIN_BORDER_VALUECONTENT(FWeaponDataStyle::GetEquipDataBackGroundColor())
	[
		SNew(SBox).MinDesiredWidth(500).MaxDesiredWidth(500)
		.IsEnabled(bUseEquipMontage)
		[
			EquipMontageHandle->CreatePropertyValueWidget()
		]
	]
	END_BORDER_VALUECONTENT;
	ChildBuilder.AddCustomRow(FText::FromString("Unequip Section"))
	BEGIN_BORDER_NAMECONTENT(FWeaponDataStyle::GetEquipDataBackGroundColor())
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot().VAlign(VAlign_Center).AutoHeight()
		[
			SNew(SCheckBox)
			.IsChecked(bUseUnequipMontage)
			.OnCheckStateChanged_Lambda([UseUnequipMontageHandle, UnequipMontageHandle, &CustomizationUtils](ECheckBoxState State)->void {
				UseUnequipMontageHandle->SetValue(State == ECheckBoxState::Checked);
				if (State != ECheckBoxState::Checked)
					UnequipMontageHandle->SetValue(static_cast<UObject*>(nullptr));
				CustomizationUtils.GetPropertyUtilities()->ForceRefresh();
			})
			[
				SNew(STextBlock)
				.Text(FText::FromString("Use Unequip Montage"))
				.Font(IDetailLayoutBuilder::GetDetailFont())
				.ColorAndOpacity(bUseUnequipMontage ? FColor::White : FColor(62,62,62))
			]
		]
		+ SVerticalBox::Slot().VAlign(VAlign_Center).AutoHeight()
		[
			WeaponDAEditorHelper::CreateCheckBox
			(
				CanMoveOnUnequipHandle,
				FText::FromString("Can Move On Unequip"),
				CustomizationUtils
			)
		]
	]
	END_BORDER_NAMECONTENT
	BEGIN_BORDER_VALUECONTENT(FWeaponDataStyle::GetEquipDataBackGroundColor())
	[
		SNew(SBox).MinDesiredWidth(500).MaxDesiredWidth(500)
		.IsEnabled(bUseUnequipMontage)
		[
			UnequipMontageHandle->CreatePropertyValueWidget()
		]
	]
	END_BORDER_VALUECONTENT;
}

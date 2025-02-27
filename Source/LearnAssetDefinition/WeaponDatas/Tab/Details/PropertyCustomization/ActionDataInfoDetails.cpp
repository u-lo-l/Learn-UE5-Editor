// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionDataInfoDetails.h"

#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "IPropertyUtilities.h"
#include "WeaponDatas/Data/ActionData.h"
#include "WeaponDatas/Style/WeaponDataStyle.h"
#include "Widgets/SViewport.h"
#include "Widgets/Layout/SUniformGridPanel.h"


TSharedRef<IPropertyTypeCustomization> FActionDataInfoDetails::MakeInstance()
{
	return MakeShareable(new FActionDataInfoDetails);
}

void FActionDataInfoDetails::CustomizeHeader
(
	TSharedRef<IPropertyHandle> PropertyHandle,
	FDetailWidgetRow & HeaderRow,
	IPropertyTypeCustomizationUtils & CustomizationUtils
)
{}

void FActionDataInfoDetails::CustomizeChildren
(
	TSharedRef<IPropertyHandle> PropertyHandle,
	IDetailChildrenBuilder & ChildBuilder,
	IPropertyTypeCustomizationUtils & CustomizationUtils
)
{
	if (!PropertyHandle->IsValidHandle())
	{
		return;
	}
	TSharedRef<IPropertyHandle> CanMoveHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FActionData, bCanMoveOnAction)).ToSharedRef();
	TSharedRef<IPropertyHandle> FixCameraHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FActionData, bFixCameraOnAction)).ToSharedRef();
	TSharedRef<IPropertyHandle> MontageHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FActionData, ActionMontage)).ToSharedRef(); 
	TSharedRef<IPropertyHandle> DamageDataHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FActionData, DamageData)).ToSharedRef(); 

	bool bCanMoveOnAction;
	bool bShouldFixCameraOnAction;
	CanMoveHandle->GetValue(bCanMoveOnAction);
	FixCameraHandle->GetValue(bShouldFixCameraOnAction);
	
	ChildBuilder.AddCustomRow(FText::FromString("Montage Section"))
	BEGIN_BORDER_NAMECONTENT(FWeaponDataStyle::GetActionDataBackGroundColor())
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.VAlign(VAlign_Center).HAlign(HAlign_Fill).AutoHeight()
		[
			MontageHandle->CreatePropertyValueWidget()
		]
		+ SVerticalBox::Slot()
		.VAlign(VAlign_Center).HAlign(HAlign_Left).AutoHeight()
		[
			SNew(SUniformGridPanel)
			.SlotPadding(FAppStyle::GetMargin("StandardDialog.SlotPadding"))
			.MinDesiredSlotWidth(FAppStyle::GetFloat("StandardDialog.MinDesiredSlotWidth"))
			.MinDesiredSlotHeight(FAppStyle::GetFloat("StandardDialog.MinDesiredSlotHeight"))
			+SUniformGridPanel::Slot(0,0)
			[
				WeaponDAEditorHelper::CreateCheckBox(
					CanMoveHandle,
					FText::FromString("Can Move"),
					CustomizationUtils
				)
			]
			+SUniformGridPanel::Slot(1,0)
			[
				WeaponDAEditorHelper::CreateCheckBox(
					FixCameraHandle,
					FText::FromString("Fix Camera"),
					CustomizationUtils
				)
			]
		]
	]
	END_BORDER_NAMECONTENT
	BEGIN_BORDER_VALUECONTENT(FWeaponDataStyle::GetActionDataBackGroundColor())
	.VAlign(VAlign_Top)
	[
		DamageDataHandle->CreatePropertyValueWidget()
	]
	END_BORDER_VALUECONTENT;

	uint32 DamageDataNum;
	DamageDataHandle->GetNumChildren(DamageDataNum);
	FSimpleDelegate OnDamageDataChanged = FSimpleDelegate::CreateLambda([&CustomizationUtils]() {
		CustomizationUtils.GetPropertyUtilities()->ForceRefresh();
	});
	DamageDataHandle->SetOnPropertyValueChanged(OnDamageDataChanged);
	for (uint32 i = 0; i < DamageDataNum; i++)
	{
		ChildBuilder.AddProperty(DamageDataHandle->GetChildHandle(i).ToSharedRef());
	}
}



#include "WeaponDataStyle.h"

#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "IDetailGroup.h"
#include "IPropertyUtilities.h"
#include "Widgets/Layout/SUniformGridPanel.h"


// FSlateIcon FWeaponDataStyle::EditorIcon;

class IDetailGroup;
TSharedPtr<FSlateBrush> FWeaponDataStyle::ActorDataBackGroundColor
	= MakeShareable(new FSlateColorBrush(FLinearColor(0.5f, 0.9f, 0.3f, .4f)));
TSharedPtr<FSlateBrush> FWeaponDataStyle::EquipDataBackGroundColor
	= MakeShareable(new FSlateColorBrush(FLinearColor(0.3f, 0.4f, 0.6f, .4f)));
TSharedPtr<FSlateBrush> FWeaponDataStyle::ActionDataBackGroundColor
	= MakeShareable(new FSlateColorBrush(FLinearColor(0.7f, 0.5f, 0.2f, .4f)));
TSharedPtr<FSlateBrush> FWeaponDataStyle::DamageDataBackGroundColor
	= MakeShareable(new FSlateColorBrush(FLinearColor(0.5f, 0.2f, 0.2f, .4f)));

TSharedRef<SCheckBox> WeaponDAEditorHelper::CreateCheckBox
(
	const TSharedPtr<IPropertyHandle> & PropertyHandle,
	const FText & CheckBoxLabel,
	IPropertyTypeCustomizationUtils & CustomizationUtils
)
{
	bool bIsChecked = false;
	PropertyHandle->GetValue( bIsChecked );
	return
		SNew(SCheckBox)
		.IsChecked(bIsChecked)
		.OnCheckStateChanged_Lambda([PropertyHandle, &CustomizationUtils](ECheckBoxState State) {
			PropertyHandle->SetValue(State == ECheckBoxState::Checked);
			CustomizationUtils.GetPropertyUtilities()->ForceRefresh();
		})
		[
			SNew(STextBlock)
			.Text(CheckBoxLabel)
			.Font(IDetailLayoutBuilder::GetDetailFont())
			.ColorAndOpacity(bIsChecked ? FColor::White : FColor(62,62,62))
		];
}

TSharedRef<SUniformGridPanel> WeaponDAEditorHelper::CreateVector
(
	const TSharedPtr<IPropertyHandle> & PropertyHandle
)
{
	return 
		SNew(SUniformGridPanel)
		.SlotPadding(FAppStyle::GetMargin("StandardDialog.SlotPadding"))
		.MinDesiredSlotWidth(FAppStyle::GetFloat("StandardDialog.MinDesiredSlotWidth"))
		.MinDesiredSlotHeight(FAppStyle::GetFloat("StandardDialog.MinDesiredSlotHeight"))
		+ SUniformGridPanel::Slot(0, 0)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(5)
			[
				SNew(STextBlock)
				.Text(FText::FromString("X"))
				.Font(IDetailLayoutBuilder::GetDetailFont())
				.ColorAndOpacity(FSlateColor(FLinearColor::Gray))
			]
			+ SHorizontalBox::Slot().MaxWidth(100)
			[
				SNew(SBox).MinDesiredWidth(100)
				[
					PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FVector, X))->CreatePropertyValueWidget()
				]
			]
		]
		+ SUniformGridPanel::Slot(1, 0)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(5)
			[
				SNew(STextBlock)
				.Text(FText::FromString("Y"))
				.Font(IDetailLayoutBuilder::GetDetailFont())
				.ColorAndOpacity(FSlateColor(FLinearColor::Gray))
			]
			+ SHorizontalBox::Slot().MaxWidth(100)
			[
				SNew(SBox).MinDesiredWidth(100)
				[
					PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FVector, Y))->CreatePropertyValueWidget()
				]
			]
		]
		+ SUniformGridPanel::Slot(2, 0)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(5)
			[
				SNew(STextBlock)
				.Text(FText::FromString("Z"))
				.Font(IDetailLayoutBuilder::GetDetailFont())
				.ColorAndOpacity(FSlateColor(FLinearColor::Gray))
			]
			+ SHorizontalBox::Slot().MaxWidth(100)
			[
				SNew(SBox).MinDesiredWidth(100)
				[
					PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FVector, Z))->CreatePropertyValueWidget()
				]
			]
		];
}

void WeaponDAEditorHelper::CustomPropertyArray
(
	const TSharedRef<IPropertyHandle> & PropertyHandle,
	IDetailChildrenBuilder & ChildBuilder
)
{
	uint32 PropertyCount;
	PropertyHandle->GetNumChildren(PropertyCount);
	FText PropertyName = PropertyHandle->GetPropertyDisplayName();
	IDetailGroup & MeshGroup = ChildBuilder.AddGroup(*PropertyName.ToString(),PropertyName);
	MeshGroup.HeaderRow().ShouldAutoExpand(PropertyCount > 0)
	.NameContent().HAlign(HAlign_Fill).VAlign(VAlign_Fill)
	[
		PropertyHandle->CreatePropertyNameWidget()
	]
	.ValueContent().HAlign(HAlign_Fill).VAlign(VAlign_Fill)
	[
		PropertyHandle->CreatePropertyValueWidget()
	];
	for ( uint32 i = 0; i < PropertyCount; i++ )
	{
		MeshGroup.AddWidgetRow()
		.NameContent().HAlign(HAlign_Fill).VAlign(VAlign_Fill)
		[
			PropertyHandle->GetChildHandle(i)->CreatePropertyNameWidget()
		]
		.ValueContent().HAlign(HAlign_Fill).VAlign(VAlign_Fill)
		[
			PropertyHandle->GetChildHandle(i)->CreatePropertyValueWidget()
		];
	}
}

void WeaponDAEditorHelper::CustomPropertyArray(
	const TSharedRef<IPropertyHandle> & PropertyHandle,
	IDetailChildrenBuilder & ChildBuilder,
	FSlateBrush * BorderStyle
)
{
	if (PropertyHandle->AsArray().IsValid() == false)
		return ;
	uint32 PropertyCount;
	PropertyHandle->GetNumChildren(PropertyCount);
	FText PropertyName = PropertyHandle->GetPropertyDisplayName();
	ChildBuilder.AddProperty(PropertyHandle).CustomWidget()
	BEGIN_BORDER_NAMECONTENT(BorderStyle)
	[
		PropertyHandle->CreatePropertyNameWidget()
	]
	END_BORDER_NAMECONTENT
	BEGIN_BORDER_VALUECONTENT(BorderStyle)
	[
		PropertyHandle->CreatePropertyValueWidget()
	]
	END_BORDER_VALUECONTENT;
}

TSharedRef<SBox> WeaponDAEditorHelper::CreateSmallButton( const FOnClicked & OnClickedDelegate, FName IconName )
{
	return
		SNew(SBox)
		.WidthOverride(20).HeightOverride(20)
		.MaxDesiredWidth(20).MaxDesiredHeight(20)
		.MinDesiredWidth(20).MinDesiredHeight(20)
		.VAlign(VAlign_Center).HAlign(HAlign_Center)
		[
			SNew(SButton)
			.ButtonStyle(FAppStyle::Get(), "SimpleButton")
			.OnClicked(OnClickedDelegate)
			.ContentPadding(0)
			[
				SNew(SImage)
				.Image(FAppStyle::Get().GetBrush(IconName))
				.ColorAndOpacity(FLinearColor(1,1,1,1))
			]
		];
}

#include "DamageDataInfoDetails.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "IPropertyUtilities.h"
#include "Components/UniformGridSlot.h"
#include "WeaponDatas/Data/DamageData.h"
#include "WeaponDatas/Style/WeaponDataStyle.h"

TSharedRef<IPropertyTypeCustomization> FDamageDataInfoDetails::MakeInstance()
{
	return MakeShareable(new FDamageDataInfoDetails);
}

void FDamageDataInfoDetails::CustomizeHeader( TSharedRef<IPropertyHandle> PropertyHandle,
	FDetailWidgetRow & HeaderRow,
	IPropertyTypeCustomizationUtils & CustomizationUtils )
{
	bool bIsFinisher;
	bool bIsNonBlockable;
	bool bUseLaunch;
	bool bUseSound;
	bool bUseEffect;
	bool bUseCameraShake;

	TSharedRef<IPropertyHandle> FinisherHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, bIsFinisher)).ToSharedRef();
	TSharedRef<IPropertyHandle> NonBlockableHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, bIsNonBlockable)).ToSharedRef();
	TSharedRef<IPropertyHandle> UseLaunchHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, bUseLaunch)).ToSharedRef();
	TSharedRef<IPropertyHandle> UseSoundHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, bUseSound)).ToSharedRef();
	TSharedRef<IPropertyHandle> UseEffectHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, bUseEffect)).ToSharedRef();
	TSharedRef<IPropertyHandle> UseCameraShakeHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, bUseCameraShake)).ToSharedRef();

	FinisherHandle->GetValue(bIsFinisher);
	NonBlockableHandle->GetValue(bIsNonBlockable);
	UseLaunchHandle->GetValue(bUseLaunch);
	UseSoundHandle->GetValue(bUseSound);
	UseEffectHandle->GetValue(bUseEffect);
	UseCameraShakeHandle->GetValue(bUseCameraShake);

	const int32 Index = PropertyHandle->GetIndexInArray() + 1;
	
	HeaderRow
	BEGIN_BORDER_NAMECONTENT(FWeaponDataStyle::GetDamageDataBackGroundColor())
	[
		SNew(STextBlock)
		.Text(FText::FromString(FString::Printf(L"Damage Data %02d", Index)))
		.Font(IDetailLayoutBuilder::GetDetailFont())
	]
	END_BORDER_NAMECONTENT
	BEGIN_BORDER_VALUECONTENT(FWeaponDataStyle::GetDamageDataBackGroundColor())
	[
		SNew(SUniformGridPanel)
		.SlotPadding(FAppStyle::GetMargin("StandardDialog.SlotPadding"))
		.MinDesiredSlotWidth(FAppStyle::GetFloat("StandardDialog.MinDesiredSlotWidth"))
		.MinDesiredSlotHeight(FAppStyle::GetFloat("StandardDialog.MinDesiredSlotHeight"))
		+SUniformGridPanel::Slot(0,0)
		[
			WeaponDAEditorHelper::CreateCheckBox(
				FinisherHandle,
				FText::FromString("Finisher"),
				CustomizationUtils
			)
		]
		+SUniformGridPanel::Slot(1,0)
		[
			WeaponDAEditorHelper::CreateCheckBox(
				NonBlockableHandle,
				FText::FromString("NonBlockable"),
				CustomizationUtils
			)
		]
		+SUniformGridPanel::Slot(2,0)
		[
			WeaponDAEditorHelper::CreateCheckBox(
				UseLaunchHandle,
				FText::FromString("Launch"),
				CustomizationUtils
			)
		]
		+SUniformGridPanel::Slot(3,0)
		[
			WeaponDAEditorHelper::CreateCheckBox(
				UseSoundHandle,
				FText::FromString("Sound"),
				CustomizationUtils
			)
		]
		+SUniformGridPanel::Slot(4,0)
		[
			WeaponDAEditorHelper::CreateCheckBox(
				UseEffectHandle,
				FText::FromString("Hit Effect"),
				CustomizationUtils
			)
		]
		+SUniformGridPanel::Slot(5,0)
		[
			WeaponDAEditorHelper::CreateCheckBox(
				UseCameraShakeHandle,
				FText::FromString("CameraShake"),
				CustomizationUtils
			)
		]
	]
	END_BORDER_VALUECONTENT;
}

void FDamageDataInfoDetails::CustomizeChildren
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

	DamageSection(PropertyHandle, ChildBuilder);
	LaunchSection(PropertyHandle, ChildBuilder);
	SoundSection(PropertyHandle, ChildBuilder);
	EffectSection(PropertyHandle, ChildBuilder);
	CameraShakeSection(PropertyHandle, ChildBuilder);
}


void FDamageDataInfoDetails::DamageSection
(
	const TSharedRef<IPropertyHandle> & PropertyHandle,
	IDetailChildrenBuilder & ChildBuilder
)
{
	TSharedRef<IPropertyHandle> DamageHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, Damage)).ToSharedRef();
	TSharedRef<IPropertyHandle> FinisherHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, bIsFinisher)).ToSharedRef();
	bool bIsFinisher = false;
	FinisherHandle->GetValue(bIsFinisher);
	
	ChildBuilder.AddCustomRow(FText::FromString("Damage"))
	.Visibility(bIsFinisher == false ? EVisibility::Visible : EVisibility::Hidden)
	BEGIN_BORDER_NAMECONTENT(FWeaponDataStyle::GetDamageDataBackGroundColor())
	[
		DamageHandle->CreatePropertyNameWidget()
	]
	END_BORDER_NAMECONTENT
	BEGIN_BORDER_VALUECONTENT(FWeaponDataStyle::GetDamageDataBackGroundColor())
	[
		SNew(SBox).MinDesiredWidth(200).MaxDesiredWidth(200)
		[
			DamageHandle->CreatePropertyValueWidget()
		]
	]
	END_BORDER_VALUECONTENT;
}

void FDamageDataInfoDetails::LaunchSection
(
	const TSharedRef<IPropertyHandle> & PropertyHandle,
	IDetailChildrenBuilder & ChildBuilder
)
{
	bool bUseLaunch;
	const TSharedRef<IPropertyHandle> UseLaunchHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, bUseLaunch)).ToSharedRef();
	TSharedRef<IPropertyHandle> LaunchPowerHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, LaunchPower)).ToSharedRef();
	TSharedRef<IPropertyHandle> LaunchDirectionHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, LaunchDirection)).ToSharedRef();
	UseLaunchHandle->GetValue(bUseLaunch);
	
	ChildBuilder.AddCustomRow(FText::FromString("Launch"))
	.Visibility(bUseLaunch ? EVisibility::Visible : EVisibility::Hidden)
	BEGIN_BORDER_NAMECONTENT(FWeaponDataStyle::GetDamageDataBackGroundColor())
	[
		SNew(STextBlock)
		.Text(FText::FromString("Launch"))
		.Font(IDetailLayoutBuilder::GetDetailFont())
	]
	END_BORDER_NAMECONTENT
	BEGIN_BORDER_VALUECONTENT(FWeaponDataStyle::GetDamageDataBackGroundColor())
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot().VAlign(VAlign_Center).AutoHeight()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().MaxWidth(100).VAlign(VAlign_Center)
			[
				SNew(SBox).MinDesiredWidth(100)
				[
					LaunchPowerHandle->CreatePropertyNameWidget()
				]
			]
			+ SHorizontalBox::Slot().MaxWidth(400)
			[
				SNew(SBox).MinDesiredWidth(400)
				[
					LaunchPowerHandle->CreatePropertyValueWidget()
				]
			]
		]
		+ SVerticalBox::Slot().VAlign(VAlign_Center).AutoHeight()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().MaxWidth(100).VAlign(VAlign_Center)
			[
				SNew(SBox).MinDesiredWidth(100)
				[
					LaunchDirectionHandle->CreatePropertyNameWidget()
				]
			]
			+ SHorizontalBox::Slot().MaxWidth(400)
			[
				SNew(SBox).MinDesiredWidth(400)
				[
					WeaponDAEditorHelper::CreateVector(LaunchDirectionHandle)
				]
			]
		]
	]
	END_BORDER_VALUECONTENT;
}

void FDamageDataInfoDetails::SoundSection
(
	const TSharedRef<IPropertyHandle> & PropertyHandle,
	IDetailChildrenBuilder & ChildBuilder
)
{
	bool bUseSound;
	TSharedRef<IPropertyHandle> UseSoundHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, bUseSound)).ToSharedRef();
	TSharedRef<IPropertyHandle> SoundHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, Sound)).ToSharedRef();
	UseSoundHandle->GetValue(bUseSound);

	ChildBuilder.AddCustomRow(FText::FromString("Sound"))
	.Visibility(bUseSound ? EVisibility::Visible : EVisibility::Hidden)
	BEGIN_BORDER_NAMECONTENT(FWeaponDataStyle::GetDamageDataBackGroundColor())
	[
		SNew(STextBlock).Text(FText::FromString("Sound"))
		.Font(IDetailLayoutBuilder::GetDetailFont())
	]
	END_BORDER_NAMECONTENT
	BEGIN_BORDER_VALUECONTENT(FWeaponDataStyle::GetDamageDataBackGroundColor())
	[
		SNew(SBox).MinDesiredWidth(500).MaxDesiredWidth(500)
		[
			SoundHandle->CreatePropertyValueWidget()
		]
	]
	END_BORDER_VALUECONTENT;
}

void FDamageDataInfoDetails::EffectSection
(
	const TSharedRef<IPropertyHandle> & PropertyHandle,
	IDetailChildrenBuilder & ChildBuilder
)
{
    bool bUseEffect;
    const TSharedRef<IPropertyHandle> UseEffectHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, bUseEffect)).ToSharedRef();
    TSharedRef<IPropertyHandle> EffectHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, Effect)).ToSharedRef();
    TSharedRef<IPropertyHandle> EffectOffsetHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, EffectOffset)).ToSharedRef();
    TSharedRef<IPropertyHandle> EffectScaleHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, EffectScale)).ToSharedRef();
    UseEffectHandle->GetValue(bUseEffect);

    ChildBuilder.AddCustomRow(FText::FromString("Hit Effect"))
    .Visibility(bUseEffect ? EVisibility::Visible : EVisibility::Hidden)
    BEGIN_BORDER_NAMECONTENT(FWeaponDataStyle::GetDamageDataBackGroundColor())
	[
		SNew(STextBlock).Text(FText::FromString("Hit Effect"))
        .Font(IDetailLayoutBuilder::GetDetailFont())
    ]
	END_BORDER_NAMECONTENT
    BEGIN_BORDER_VALUECONTENT(FWeaponDataStyle::GetDamageDataBackGroundColor())
	[
	    SNew(SVerticalBox)
        + SVerticalBox::Slot().VAlign(VAlign_Center).AutoHeight()
        [
            SNew(SBox).MinDesiredWidth(500).MaxDesiredWidth(500)
            [
                EffectHandle->CreatePropertyValueWidget()
            ]
        ]
        + SVerticalBox::Slot().VAlign(VAlign_Center).AutoHeight()
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot().MaxWidth(100).VAlign(VAlign_Center)
            [
                SNew(SBox).MinDesiredWidth(100)
                [
                    EffectOffsetHandle->CreatePropertyNameWidget()
                ]
            ]
            + SHorizontalBox::Slot().MaxWidth(400)
            [
                SNew(SBox).MinDesiredWidth(400)
                [
                    WeaponDAEditorHelper::CreateVector(EffectOffsetHandle)
                ]
            ]
        ]
        + SVerticalBox::Slot().VAlign(VAlign_Center).AutoHeight()
	        [
	            SNew(SHorizontalBox)
	            + SHorizontalBox::Slot().MaxWidth(100).VAlign(VAlign_Center)
	            [
	                SNew(SBox).MinDesiredWidth(100)
	                [
	                    EffectScaleHandle->CreatePropertyNameWidget()
	                ]
	            ]
	            + SHorizontalBox::Slot().MaxWidth(400)
	            [
	                SNew(SBox).MinDesiredWidth(400)
	                [
	                    WeaponDAEditorHelper::CreateVector(EffectScaleHandle)
	                ]
	            ]
	        ]
	]
	END_BORDER_VALUECONTENT;
}

void FDamageDataInfoDetails::CameraShakeSection
(
	const TSharedRef<IPropertyHandle> & PropertyHandle,
	IDetailChildrenBuilder & ChildBuilder
)
{
	bool bUseCameraShake;
	TSharedRef<IPropertyHandle> UseCameraShakeHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, bUseCameraShake)).ToSharedRef();
	TSharedRef<IPropertyHandle> CameraShakeHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, CameraShake)).ToSharedRef();
	UseCameraShakeHandle->GetValue(bUseCameraShake);

	ChildBuilder.AddCustomRow(FText::FromString("CameraShake"))
	.Visibility(bUseCameraShake ? EVisibility::Visible : EVisibility::Hidden)
	BEGIN_BORDER_NAMECONTENT(FWeaponDataStyle::GetDamageDataBackGroundColor())
	[
			SNew(STextBlock).Text(FText::FromString("CameraShake"))
			.Font(IDetailLayoutBuilder::GetDetailFont())
	]
	END_BORDER_NAMECONTENT
	BEGIN_BORDER_VALUECONTENT(FWeaponDataStyle::GetDamageDataBackGroundColor())
	[
		SNew(SBox).MinDesiredWidth(500).MaxDesiredWidth(500)
		[
			CameraShakeHandle->CreatePropertyValueWidget()
		]
	]
	END_BORDER_VALUECONTENT;
}

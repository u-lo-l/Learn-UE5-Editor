#include "Tab/Details/PropertyCustomization/DamageDataInfoDetails.h"

#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "Components/UniformGridSlot.h"
#include "Data/DamageData.h"
#include "Style/WeaponDataStyle.h"

TSharedRef<IPropertyTypeCustomization> FDamageDataInfoDetails::MakeInstance()
{
	return MakeShareable(new FDamageDataInfoDetails);
}

void FDamageDataInfoDetails::CustomizeHeader( TSharedRef<IPropertyHandle> PropertyHandle,
	FDetailWidgetRow & HeaderRow,
	IPropertyTypeCustomizationUtils & CustomizationUtils )
{
	
	HeaderRow
	BEGIN_BORDER_NAMECONTENT(FWeaponDataStyle::GetDamageDataBackGroundColor())
	[
		this->HeaderNameContent(PropertyHandle,CustomizationUtils)
	]
	END_BORDER_NAMECONTENT
	BEGIN_BORDER_VALUECONTENT(FWeaponDataStyle::GetDamageDataBackGroundColor())
	[
		this->HeaderValueContent(PropertyHandle,CustomizationUtils)
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
	DamageSection(PropertyHandle, ChildBuilder);
	LaunchSection(PropertyHandle, ChildBuilder);
	SoundSection(PropertyHandle, ChildBuilder);
	EffectSection(PropertyHandle, ChildBuilder);
	CameraShakeSection(PropertyHandle, ChildBuilder);
}

TSharedRef<SWidget> FDamageDataInfoDetails::HeaderNameContent
(
	const TSharedRef<IPropertyHandle> & PropertyHandle,
	IPropertyTypeCustomizationUtils & CustomizationUtils
)
{
	const int32 Index = PropertyHandle->GetIndexInArray() + 1;
	return
		SNew(STextBlock)
			.Text(FText::FromString(FString::Printf(L"Damage Data %02d", Index)))
			.Font(IDetailLayoutBuilder::GetDetailFont());
}

TSharedRef<SWidget> FDamageDataInfoDetails::HeaderValueContent
(
	const TSharedRef<IPropertyHandle> & PropertyHandle,
	IPropertyTypeCustomizationUtils & CustomizationUtils
)
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

	return 
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
		];
}


void FDamageDataInfoDetails::DamageSection
(
	const TSharedRef<IPropertyHandle> & PropertyHandle,
	IDetailChildrenBuilder & ChildBuilder
)
{
	TSharedRef<IPropertyHandle> FinisherHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, bIsFinisher)).ToSharedRef();
	bool bIsFinisher = false;
	FinisherHandle->GetValue(bIsFinisher);
	
	ChildBuilder.AddCustomRow(FText::FromString("Damage"))
	.Visibility(bIsFinisher == false ? EVisibility::Visible : EVisibility::Hidden)
	BEGIN_BORDER_NAMECONTENT(FWeaponDataStyle::GetDamageDataBackGroundColor())
	[
		DamageNameContent(PropertyHandle)
	]
	END_BORDER_NAMECONTENT
	BEGIN_BORDER_VALUECONTENT(FWeaponDataStyle::GetDamageDataBackGroundColor())
	[
		DamageValueContent(PropertyHandle)
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
	UseLaunchHandle->GetValue(bUseLaunch);
	
	ChildBuilder.AddCustomRow(FText::FromString("Launch"))
	.Visibility(bUseLaunch ? EVisibility::Visible : EVisibility::Hidden)
	BEGIN_BORDER_NAMECONTENT(FWeaponDataStyle::GetDamageDataBackGroundColor())
	[
		LaunchValueContent(PropertyHandle)
	]
	END_BORDER_NAMECONTENT
	BEGIN_BORDER_VALUECONTENT(FWeaponDataStyle::GetDamageDataBackGroundColor())
	[
		LaunchValueContent(PropertyHandle)
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
	UseSoundHandle->GetValue(bUseSound);

	ChildBuilder.AddCustomRow(FText::FromString("Sound"))
	.Visibility(bUseSound ? EVisibility::Visible : EVisibility::Hidden)
	BEGIN_BORDER_NAMECONTENT(FWeaponDataStyle::GetDamageDataBackGroundColor())
	[
		SoundNameContent(PropertyHandle)
	]
	END_BORDER_NAMECONTENT
	BEGIN_BORDER_VALUECONTENT(FWeaponDataStyle::GetDamageDataBackGroundColor())
	[
		SoundValueContent(PropertyHandle)
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
    UseEffectHandle->GetValue(bUseEffect);

    ChildBuilder.AddCustomRow(FText::FromString("Hit Effect"))
    .Visibility(bUseEffect ? EVisibility::Visible : EVisibility::Hidden)
    BEGIN_BORDER_NAMECONTENT(FWeaponDataStyle::GetDamageDataBackGroundColor())
	[
		EffectNameContent(PropertyHandle)
    ]
	END_BORDER_NAMECONTENT
    BEGIN_BORDER_VALUECONTENT(FWeaponDataStyle::GetDamageDataBackGroundColor())
	[
	    EffectValueContent(PropertyHandle)
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
	UseCameraShakeHandle->GetValue(bUseCameraShake);

	ChildBuilder.AddCustomRow(FText::FromString("CameraShake"))
	.Visibility(bUseCameraShake ? EVisibility::Visible : EVisibility::Hidden)
	BEGIN_BORDER_NAMECONTENT(FWeaponDataStyle::GetDamageDataBackGroundColor())
	[
		CameraShakeNameContent(PropertyHandle)
	]
	END_BORDER_NAMECONTENT
	BEGIN_BORDER_VALUECONTENT(FWeaponDataStyle::GetDamageDataBackGroundColor())
	[
		CameraShakeValueContent(PropertyHandle)
	]
	END_BORDER_VALUECONTENT;
}

TSharedRef<SWidget> FDamageDataInfoDetails::DamageNameContent ( const TSharedRef<IPropertyHandle> & PropertyHandle )
{
	TSharedRef<IPropertyHandle> DamageHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, Damage)).ToSharedRef();
	return DamageHandle->CreatePropertyNameWidget();
}

TSharedRef<SWidget> FDamageDataInfoDetails::DamageValueContent ( const TSharedRef<IPropertyHandle> & PropertyHandle )
{
	TSharedRef<IPropertyHandle> DamageHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, Damage)).ToSharedRef();
	return SNew(SBox).MinDesiredWidth(200).MaxDesiredWidth(200)
	[
		DamageHandle->CreatePropertyValueWidget()
	];
}

TSharedRef<SWidget> FDamageDataInfoDetails::LaunchNameContent ( const TSharedRef<IPropertyHandle> & PropertyHandle )
{
	return SNew(STextBlock)
		.Text(FText::FromString("Launch"))
		.Font(IDetailLayoutBuilder::GetDetailFont());
}

TSharedRef<SWidget> FDamageDataInfoDetails::LaunchValueContent ( const TSharedRef<IPropertyHandle> & PropertyHandle )
{
	TSharedRef<IPropertyHandle> LaunchPowerHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, LaunchPower)).ToSharedRef();
	TSharedRef<IPropertyHandle> LaunchDirectionHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, LaunchDirection)).ToSharedRef();
	return SNew(SVerticalBox)
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
		];
}

TSharedRef<SWidget> FDamageDataInfoDetails::SoundNameContent ( const TSharedRef<IPropertyHandle> & PropertyHandle )
{
	return SNew(STextBlock).Text(FText::FromString("Sound"))
		.Font(IDetailLayoutBuilder::GetDetailFont());
}

TSharedRef<SWidget> FDamageDataInfoDetails::SoundValueContent ( const TSharedRef<IPropertyHandle> & PropertyHandle )
{
	TSharedRef<IPropertyHandle> SoundHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, Sound)).ToSharedRef();

	return SNew(SBox).MinDesiredWidth(500).MaxDesiredWidth(500)
		[
			SoundHandle->CreatePropertyValueWidget()
		];
}

TSharedRef<SWidget> FDamageDataInfoDetails::EffectNameContent ( const TSharedRef<IPropertyHandle> & PropertyHandle )
{
	return SNew(STextBlock).Text(FText::FromString("Hit Effect"))
		.Font(IDetailLayoutBuilder::GetDetailFont());
}

TSharedRef<SWidget> FDamageDataInfoDetails::EffectValueContent ( const TSharedRef<IPropertyHandle> & PropertyHandle )
{
	TSharedRef<IPropertyHandle> EffectHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, Effect)).ToSharedRef();
	TSharedRef<IPropertyHandle> EffectOffsetHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, EffectOffset)).ToSharedRef();
	TSharedRef<IPropertyHandle> EffectScaleHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, EffectScale)).ToSharedRef();
 
	return SNew(SVerticalBox)
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
		];
}

TSharedRef<SWidget> FDamageDataInfoDetails::CameraShakeNameContent ( const TSharedRef<IPropertyHandle> & PropertyHandle )
{
	return SNew(STextBlock).Text(FText::FromString("CameraShake"))
		.Font(IDetailLayoutBuilder::GetDetailFont());
}

TSharedRef<SWidget> FDamageDataInfoDetails::CameraShakeValueContent ( const TSharedRef<IPropertyHandle> & PropertyHandle )
{
	TSharedRef<IPropertyHandle> CameraShakeHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, CameraShake)).ToSharedRef();
	return SNew(SBox).MinDesiredWidth(500).MaxDesiredWidth(500)
		[
			CameraShakeHandle->CreatePropertyValueWidget()
		];
}
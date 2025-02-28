#include "Tab/Details/PropertyCustomization/ActionDataInfoDetails.h"

#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "IPropertyUtilities.h"
#include "Data/ActionData.h"
#include "Style/WeaponDataStyle.h"
#include "Tab/Details/PropertyCustomization/DamageDataInfoDetails.h"
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
	// ~Begin Set-up
	TSharedRef<IPropertyHandle> CanMoveHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FActionData, bCanMoveOnAction)).ToSharedRef();
	TSharedRef<IPropertyHandle> FixCameraHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FActionData, bFixCameraOnAction)).ToSharedRef();
	TSharedRef<IPropertyHandle> MontageHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FActionData, ActionMontage)).ToSharedRef(); 
	TSharedRef<IPropertyHandle> DamageDataHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FActionData, DamageData)).ToSharedRef(); 

	bool bCanMoveOnAction;
	bool bShouldFixCameraOnAction;
	CanMoveHandle->GetValue(bCanMoveOnAction);
	FixCameraHandle->GetValue(bShouldFixCameraOnAction);

	uint32 DamageDataNum;
	DamageDataHandle->GetNumChildren(DamageDataNum);
	FSimpleDelegate OnDamageDataChanged = FSimpleDelegate::CreateLambda([&CustomizationUtils]() {
		CustomizationUtils.GetPropertyUtilities()->ForceRefresh();
	});
	DamageDataHandle->SetOnPropertyValueChanged(OnDamageDataChanged);
	// ~End Set-up

	// ~Begin Damage Data
	TSharedRef<SVerticalBox> DamageDataVBox = SNew(SVerticalBox);
	DamageDataVBox->AddSlot().VAlign(VAlign_Center).MaxHeight(30) // 요소 추가 버튼.
	[
		SNew(SBox).MinDesiredHeight(30).MaxDesiredHeight(30)
		[
			DamageDataHandle->CreatePropertyValueWidget()
		]
	];
	for (uint32 i = 0; i < DamageDataNum; i++)
	{
		TSharedRef<IPropertyHandle> ElementHandle = DamageDataHandle->GetChildHandle(i).ToSharedRef();
		DamageDataVBox->AddSlot().AutoHeight().VAlign(VAlign_Center)
		[
			SNew(SSplitter).Orientation(Orient_Horizontal)
		];
		DamageDataVBox->AddSlot().AutoHeight().VAlign(VAlign_Center)
		[
			SDamageData(ElementHandle, CustomizationUtils)
		];
	}
	// ~End Damage Data
	
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
		DamageDataVBox
	]
	END_BORDER_VALUECONTENT;
}

TSharedRef<SWidget> FActionDataInfoDetails::SDamageData
(
	const TSharedRef<IPropertyHandle> & ElementHandle,
	IPropertyTypeCustomizationUtils & CustomizationUtils
)
{
	bool bIsFinisher;
	bool bUseLaunch;
	bool bUseSound;
	bool bUseEffect;
	bool bUseCameraShake;

	const TSharedRef<IPropertyHandle> FinisherHandle = ElementHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, bIsFinisher)).ToSharedRef();
	const TSharedRef<IPropertyHandle> UseLaunchHandle = ElementHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, bUseLaunch)).ToSharedRef();
	const TSharedRef<IPropertyHandle> UseSoundHandle = ElementHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, bUseSound)).ToSharedRef();
	const TSharedRef<IPropertyHandle> UseEffectHandle = ElementHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, bUseEffect)).ToSharedRef();
	const TSharedRef<IPropertyHandle> UseCameraShakeHandle = ElementHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDamageData, bUseCameraShake)).ToSharedRef();

	FinisherHandle->GetValue(bIsFinisher);
	UseLaunchHandle->GetValue(bUseLaunch);
	UseSoundHandle->GetValue(bUseSound);
	UseEffectHandle->GetValue(bUseEffect);
	UseCameraShakeHandle->GetValue(bUseCameraShake);

	TSharedRef<SVerticalBox> DamageDataBox = SNew(SVerticalBox);

	if (bIsFinisher == false)
	{
		DamageDataBox->AddSlot() [
			SNew(SSeparator).Orientation(Orient_Horizontal).Thickness(3).SeparatorImage(FWeaponDataStyle::GetDamageDataBackGroundColor()).ColorAndOpacity(FLinearColor::Gray)
		];
		DamageDataBox->AddSlot().AutoHeight().Padding(5,0) [
			SNew(SHorizontalBox) + SHorizontalBox::Slot().MaxWidth(120) [
				FDamageDataInfoDetails::DamageNameContent(ElementHandle)
			] + SHorizontalBox::Slot().AutoWidth() [
				FDamageDataInfoDetails::DamageValueContent(ElementHandle)
			]
		];
		
	}
	if (bUseLaunch == true)
	{
		DamageDataBox->AddSlot() [
			SNew(SSeparator).Orientation(Orient_Horizontal).Thickness(3).SeparatorImage(FWeaponDataStyle::GetDamageDataBackGroundColor()).ColorAndOpacity(FLinearColor::Gray)
		];
		DamageDataBox->AddSlot().AutoHeight().Padding(5,0) [
		   SNew(SHorizontalBox) + SHorizontalBox::Slot().MaxWidth(120) [
			   FDamageDataInfoDetails::LaunchNameContent(ElementHandle)
		   ] + SHorizontalBox::Slot().AutoWidth() [
			   FDamageDataInfoDetails::LaunchValueContent(ElementHandle)
		   ]
	   ];
	}
		
	if (bUseSound == true)
	{
		DamageDataBox->AddSlot() [
			SNew(SSeparator).Orientation(Orient_Horizontal).Thickness(3).SeparatorImage(FWeaponDataStyle::GetDamageDataBackGroundColor()).ColorAndOpacity(FLinearColor::Gray)
		];
		DamageDataBox->AddSlot().AutoHeight().Padding(5,0) [
		   SNew(SHorizontalBox) + SHorizontalBox::Slot().MaxWidth(120) [
			   FDamageDataInfoDetails::SoundNameContent(ElementHandle)
		   ] + SHorizontalBox::Slot().AutoWidth() [
			   FDamageDataInfoDetails::SoundValueContent(ElementHandle)
		   ]
	   ];
	}

	if (bUseEffect == true)
	{
		DamageDataBox->AddSlot().Padding(0,10) [
			SNew(SSeparator).Orientation(Orient_Horizontal).Thickness(2)
			.SeparatorImage(FWeaponDataStyle::GetDamageDataBackGroundColor())
			.ColorAndOpacity(FLinearColor::Gray)
		];
		DamageDataBox->AddSlot().AutoHeight().VAlign(VAlign_Fill) [
		   SNew(SHorizontalBox) + SHorizontalBox::Slot().VAlign(VAlign_Center).HAlign(HAlign_Left).MaxWidth(120) [
			   FDamageDataInfoDetails::EffectNameContent(ElementHandle)
		   ] + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Fill).HAlign(HAlign_Left) [
			   FDamageDataInfoDetails::EffectValueContent(ElementHandle)
		   ]
	   ];
	}
	
	if (bUseCameraShake == true)
	{
		DamageDataBox->AddSlot() [
			SNew(SSeparator).Orientation(Orient_Horizontal).Thickness(3).SeparatorImage(FWeaponDataStyle::GetDamageDataBackGroundColor()).ColorAndOpacity(FLinearColor::Gray)
		];
		DamageDataBox->AddSlot().AutoHeight().Padding(5,0) [
		   SNew(SHorizontalBox) + SHorizontalBox::Slot().MaxWidth(120) [
			   FDamageDataInfoDetails::CameraShakeNameContent(ElementHandle)
		   ] + SHorizontalBox::Slot().AutoWidth() [
			   FDamageDataInfoDetails::CameraShakeValueContent(ElementHandle)
		   ]
	   ];
	}
	
	return
		SNew(SBox).HAlign(HAlign_Fill).VAlign(VAlign_Center).Padding(0, 5)
		[
			SNew(SExpandableArea)
			.Style(&FCoreStyle::Get().GetWidgetStyle<FExpandableAreaStyle>("ExpandableArea"))
			.AreaTitle(FText::FromString("Advanced Settings"))
			.BorderImage(FWeaponDataStyle::GetDamageDataBackGroundColor())
			.BodyBorderImage(FWeaponDataStyle::GetDamageDataBackGroundColor())
			.HeaderPadding(2)
			.AllowAnimatedTransition(true)
			.HeaderCursor(EMouseCursor::Hand)
			.AreaTitlePadding(5)
			.Padding(10)
			.HeaderContent()
			[
				SNew(SBox).VAlign(VAlign_Fill).HAlign(HAlign_Fill).Padding(0)
				[
					FDamageDataInfoDetails::HeaderValueContent(ElementHandle, CustomizationUtils)
				]
			]
			.BodyContent()
			[
				SNew(SBox).Padding(5).VAlign(VAlign_Fill).HAlign(HAlign_Fill)
				[
					DamageDataBox
				]
			]
		];
}



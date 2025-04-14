#include "Tab/Details/PropertyCustomization/DHActionDataInfoDetails.h"

#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "IPropertyUtilities.h"
#include "Data/DH_ActionData.h"
#include "Style/WeaponDataStyle.h"
#include "Tab/Details/PropertyCustomization/DamageDataInfoDetails.h"
#include "Widgets/Layout/SUniformGridPanel.h"


TSharedRef<IPropertyTypeCustomization> FDHActionDataInfoDetails::MakeInstance()
{
	return MakeShareable(new FDHActionDataInfoDetails);
}

void FDHActionDataInfoDetails::CustomizeHeader
(
	TSharedRef<IPropertyHandle> PropertyHandle,
	FDetailWidgetRow & HeaderRow,
	IPropertyTypeCustomizationUtils & CustomizationUtils
)
{}

void FDHActionDataInfoDetails::CustomizeChildren
(
	TSharedRef<IPropertyHandle> PropertyHandle,
	IDetailChildrenBuilder & ChildBuilder,
	IPropertyTypeCustomizationUtils & CustomizationUtils
)
{
	// ~Begin Set-up
	TSharedRef<IPropertyHandle> CanMoveHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDH_ActionData, bCanMoveOnAction)).ToSharedRef();
	TSharedRef<IPropertyHandle> FixCameraHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDH_ActionData, bFixCameraOnAction)).ToSharedRef();
	TSharedRef<IPropertyHandle> MontageHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDH_ActionData, ActionMontage)).ToSharedRef(); 
	TSharedRef<IPropertyHandle> DamageDataHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDH_ActionData, DamageData)).ToSharedRef(); 

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
		SNew(SBox).MinDesiredHeight(30).MaxDesiredHeight(30).HAlign(HAlign_Fill).MinDesiredWidth(650)
		[
			DamageDataHandle->CreatePropertyValueWidget()
		]
	];
	for (uint32 i = 0; i < DamageDataNum; i++)
	{
		TSharedRef<IPropertyHandle> ElementHandle = DamageDataHandle->GetChildHandle(i).ToSharedRef();

		FOnClicked OnDeleteItemClicked = FOnClicked::CreateLambda([DamageDataHandle, ElementHandle]()->FReply {
			if (ElementHandle->IsValidHandle() == false)
			{
				GLog->Log("Element Property Not Valid");
				return FReply::Unhandled();
			}
			TSharedPtr<IPropertyHandleArray> ArrayProperty = DamageDataHandle->AsArray();
			if (ArrayProperty.IsValid() == false)
			{
				GLog->Log("Property is NOT Array");
				return FReply::Unhandled();
			}
			const uint32 Index = ElementHandle->GetIndexInArray();
			uint32 ArraySize;
			ArrayProperty->GetNumElements(ArraySize);
			if (ArraySize <= Index)
			{
				GLog->Log("Index Not Valid");
				return FReply::Unhandled();;
			}
			ArrayProperty->DeleteItem(Index);
			return FReply::Handled();
		});
		
		DamageDataVBox->AddSlot().AutoHeight().VAlign(VAlign_Center)
		[
			SNew(SSplitter).Orientation(Orient_Horizontal)
		];
		DamageDataVBox->AddSlot().AutoHeight().VAlign(VAlign_Center)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).HAlign(HAlign_Left)	
			[
				SDamageData(ElementHandle, CustomizationUtils)
			]
			+ SHorizontalBox::Slot().VAlign(VAlign_Fill).AutoWidth().Padding(0,5) [
				SNew(SBorder).BorderImage(FWeaponDataStyle::GetDamageDataBackGroundColor()).Padding(0).VAlign(VAlign_Top)
				[
					WeaponDAEditorHelper::CreateSmallButton(OnDeleteItemClicked, "Icons.X", "Delete Damage Data")
				]
			]
		];
	}
	// ~End Damage Data

	// ~Begin Action Data
	bool bIsArrayElement = PropertyHandle->GetParentHandle().ToSharedRef()->AsArray().IsValid();
	FOnClicked OnDeleteActionDataClicked = FOnClicked::CreateLambda([PropertyHandle]()->FReply {
		if (PropertyHandle->IsValidHandle() == false)
		{
			GLog->Log("Element Property Not Valid");
			return FReply::Unhandled();
		}
		TSharedPtr<IPropertyHandle> ParentHandle = PropertyHandle->GetParentHandle();
		if (ParentHandle.IsValid() == false)
		{
			GLog->Log("Parent Property Not Valid");
			return FReply::Unhandled();
		}
		TSharedPtr<IPropertyHandleArray> ArrayProperty = ParentHandle->AsArray();
		if (ArrayProperty.IsValid() == false)
		{
			GLog->Log("Property is NOT Array");
			return FReply::Unhandled();
		}
		uint32 Index = PropertyHandle->GetIndexInArray();
		uint32 Size;
		ArrayProperty->GetNumElements(Size);
		GLog->Log(FString::Printf(L"Deleting : %d/%d", Index, Size));
		ArrayProperty.ToSharedRef()->DeleteItem(Index);
		return FReply::Handled();
	});
	TSharedRef<SHorizontalBox> ActionData = SNew(SHorizontalBox);
	ActionData->AddSlot().AutoWidth().VAlign(VAlign_Center).HAlign(HAlign_Left)
	[
		DamageDataVBox
	];
	if (bIsArrayElement)
	{
		ActionData->AddSlot().VAlign(VAlign_Top).AutoWidth().Padding(0,5)
		[
			WeaponDAEditorHelper::CreateSmallButton(OnDeleteActionDataClicked, "Icons.X", "Delete Action Data")
		];
	}
	// ~End Action Data
	
	ChildBuilder.AddCustomRow(FText::FromString("Montage Section"))
	BEGIN_BORDER_NAMECONTENT(FWeaponDataStyle::GetActionDataBackGroundColor())
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.VAlign(VAlign_Center).HAlign(HAlign_Fill).AutoHeight()
		[
			MontageHandle->CreatePropertyValueWidget(true)
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
	BEGIN_BORDER_VALUECONTENT(FWeaponDataStyle::GetActionDataBackGroundColor()).VAlign(VAlign_Top)
	[
		ActionData
	]
	END_BORDER_VALUECONTENT;
}

TSharedRef<SWidget> FDHActionDataInfoDetails::SDamageData
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

	const TSharedRef<IPropertyHandle> FinisherHandle = ElementHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDH_DamageData, bIsFinisher)).ToSharedRef();
	const TSharedRef<IPropertyHandle> UseLaunchHandle = ElementHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDH_DamageData, bUseLaunch)).ToSharedRef();
	const TSharedRef<IPropertyHandle> UseSoundHandle = ElementHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDH_DamageData, bUseSound)).ToSharedRef();
	const TSharedRef<IPropertyHandle> UseEffectHandle = ElementHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDH_DamageData, bUseEffect)).ToSharedRef();
	const TSharedRef<IPropertyHandle> UseCameraShakeHandle = ElementHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDH_DamageData, bUseCameraShake)).ToSharedRef();

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
				SNew(SBox).Padding(5).VAlign(VAlign_Fill).HAlign(HAlign_Fill).MinDesiredWidth(600)
				[
					DamageDataBox
				]
			]
		];
}



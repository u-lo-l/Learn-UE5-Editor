#include "Tab/Details/WeaponDataAssetDetailCustomization.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "DHWeaponBase.h"
#include "IDetailGroup.h"
#include "Data/DH_WeaponDataAsset.h"
#include "Style/WeaponDataStyle.h"

FSlateFontInfo FWeaponDataAssetDetailCustomization::GetBoldFont( float InSize )
{
	FSlateFontInfo font = IDetailLayoutBuilder::GetDetailFontBold();
	font.Size = InSize;
	font.OutlineSettings.OutlineColor = FColor::Black;
	font.OutlineSettings.OutlineSize = 2.f;
	return font;
}

FSimpleDelegate FWeaponDataAssetDetailCustomization::OnPropertyChanged( IDetailLayoutBuilder & DetailBuilder )
{
	return FSimpleDelegate::CreateLambda([&DetailBuilder]() {
		DetailBuilder.ForceRefreshDetails();
	});
}



TSharedRef<IDetailCustomization> FWeaponDataAssetDetailCustomization::MakeInstance()
{
	return MakeShareable(new FWeaponDataAssetDetailCustomization());
}

void FWeaponDataAssetDetailCustomization::CustomizeDetails( IDetailLayoutBuilder & DetailBuilder )
{
#pragma region Get Handles;
	TSharedRef<IPropertyHandle> ActorHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDH_WeaponDataAsset, WeaponActors));
	TSharedRef<IPropertyHandle> ActorDataHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDH_WeaponDataAsset, ActorDatas));
	
	TSharedRef<IPropertyHandle> EquipmentClassHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDH_WeaponDataAsset, EquipmentClass));
	TSharedRef<IPropertyHandle> EquipmentHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDH_WeaponDataAsset, EquipmentData));

	TSharedRef<IPropertyHandle> LightActionClassHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDH_WeaponDataAsset, LightActionClass));
	TSharedRef<IPropertyHandle> GuardActionClassHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDH_WeaponDataAsset, GuardActionClass));
	TSharedRef<IPropertyHandle> FinisherActionClassHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDH_WeaponDataAsset, FinisherActionClass));
	TSharedRef<IPropertyHandle> AirActionClassHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDH_WeaponDataAsset, AirActionClass));
	TSharedRef<IPropertyHandle> LightActionHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDH_WeaponDataAsset, LightActions));
	TSharedRef<IPropertyHandle> GuardActionHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDH_WeaponDataAsset, GuardAction));
	TSharedRef<IPropertyHandle> FinisherActionHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDH_WeaponDataAsset, Finisher));
	TSharedRef<IPropertyHandle> AirActionHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDH_WeaponDataAsset, AirActions));

	DetailBuilder.HideProperty(ActorHandle);
	DetailBuilder.HideProperty(ActorDataHandle);
	
	DetailBuilder.HideProperty(EquipmentClassHandle);
	DetailBuilder.HideProperty(LightActionClassHandle);
	DetailBuilder.HideProperty(GuardActionClassHandle);
	DetailBuilder.HideProperty(FinisherActionClassHandle);
	DetailBuilder.HideProperty(AirActionClassHandle);
	
	DetailBuilder.HideProperty(EquipmentHandle);
	DetailBuilder.HideProperty(LightActionHandle);
	DetailBuilder.HideProperty(GuardActionHandle);
	DetailBuilder.HideProperty(FinisherActionHandle);
	DetailBuilder.HideProperty(AirActionHandle);
#pragma endregion Get Handles
	
	IDetailCategoryBuilder& WeaponActorDataCategory = DetailBuilder.EditCategory("WeaponActorData", FText::FromString("Weapon Actor Data"));
	
	// Weapon Actor 섹션
	CreateActorCategory(WeaponActorDataCategory, DetailBuilder, ActorHandle, ActorDataHandle,"Weapon Actor");
	
	// EquipmentData 섹션
	CreateEquipmentCategory(WeaponActorDataCategory, DetailBuilder, EquipmentClassHandle, EquipmentHandle, "Equipment");
	
	// Action 섹션
	CreateActionCategory(WeaponActorDataCategory, DetailBuilder, LightActionClassHandle, LightActionHandle, "LightActions");
	CreateActionCategory(WeaponActorDataCategory, DetailBuilder, GuardActionClassHandle, GuardActionHandle, "GuardActions");
	CreateActionCategory(WeaponActorDataCategory, DetailBuilder, FinisherActionClassHandle, FinisherActionHandle, "FinisherActions");
	CreateActionCategory(WeaponActorDataCategory, DetailBuilder, AirActionClassHandle, AirActionHandle, "AirActions");
}

void FWeaponDataAssetDetailCustomization::CreateActorCategory
(
	IDetailCategoryBuilder & DetailCategoryBuilder,
	IDetailLayoutBuilder & DetailBuilder,
	const TSharedRef<IPropertyHandle> & InActorHandle,
	const TSharedRef<IPropertyHandle> & InActorDataHandle,
	const FString & InCategoryName )
{
	uint32 ActorArraySize;
	uint32 DataArraySize;
	InActorHandle->AsArray()->GetNumElements(ActorArraySize);
	InActorDataHandle->AsArray()->GetNumElements(DataArraySize);
	if (ActorArraySize != DataArraySize)
	{
		InActorHandle->AsArray()->EmptyArray();
		InActorDataHandle->AsArray()->EmptyArray();
		ActorArraySize = 0;
		DataArraySize = 0;
	}
	InActorHandle->SetOnPropertyValueChanged(OnPropertyChanged(DetailBuilder));
	InActorHandle->SetOnChildPropertyValueChanged(OnPropertyChanged(DetailBuilder));
	
	FOnClicked OnAddItemClicked = FOnClicked::CreateLambda([InActorHandle, InActorDataHandle, &DetailBuilder]()->FReply {
		InActorDataHandle->AsArray()->AddItem();
		InActorHandle->AsArray()->AddItem();
		DetailBuilder.ForceRefreshDetails();
		return FReply::Handled();
	});
	FOnClicked OnClearArrayClicked = FOnClicked::CreateLambda([InActorHandle, InActorDataHandle, &DetailBuilder]()->FReply {
		InActorDataHandle->AsArray()->EmptyArray();
		InActorHandle->AsArray()->EmptyArray();
		DetailBuilder.ForceRefreshDetails();
		return FReply::Handled();
	});
	
	IDetailGroup & ActorGroup = DetailCategoryBuilder.AddGroup(*InCategoryName, FText::FromString(InCategoryName));
	ActorGroup.HeaderRow()
	BEGIN_BORDER_NAMECONTENT(FWeaponDataStyle::GetActorDataBackGroundColor())
	[
        SNew(STextBlock)
        	.Text(FText::FromString(FString(L"Weapon Actor") + (ActorArraySize > 1 ? L"s" : L"  ")))
        	.Font(IDetailLayoutBuilder::GetDetailFont())
        	.ColorAndOpacity(FColor::White)
	]
	END_BORDER_NAMECONTENT
	BEGIN_BORDER_VALUECONTENT(FWeaponDataStyle::GetActorDataBackGroundColor())
	[
		SNew(SHorizontalBox) + SHorizontalBox::Slot().Padding(5,0).AutoWidth().VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString(FString::Printf(L"%d Array element", ActorArraySize) + (ActorArraySize > 1 ? L"s" : L" ")))
			.Font(IDetailLayoutBuilder::GetDetailFont())
			.ColorAndOpacity(FColor::White)
		]
		+ SHorizontalBox::Slot().Padding(5,0)
		[
			WeaponDAEditorHelper::CreateSmallButton(OnAddItemClicked,"Icons.PlusCircle", "Add Element")
		]
		+ SHorizontalBox::Slot().Padding(5,0)
		[
			WeaponDAEditorHelper::CreateSmallButton(OnClearArrayClicked,"Icons.Delete", "Empty Array")
		]
		+ SHorizontalBox::Slot().Padding(5,0)
		[
			WeaponDAEditorHelper::CreateSmallButton(FOnClicked::CreateLambda([&DetailBuilder]()->FReply {
				DetailBuilder.ForceRefreshDetails();
				return FReply::Handled();
			}),"Icons.Refresh", "Refresh")
		]
	]
	END_BORDER_VALUECONTENT;
	InActorHandle->AsArray()->GetNumElements(ActorArraySize);
	for (uint32 i = 0; i < ActorArraySize; i++)
	{
		TSharedRef<IPropertyHandle> ChildActorHandle = InActorHandle->GetChildHandle(i).ToSharedRef();
		TSharedRef<IPropertyHandle> ChildDataHandle = InActorDataHandle->GetChildHandle(i).ToSharedRef();
		UClass * SelectedClass = nullptr;
		ChildActorHandle->GetValue(reinterpret_cast<UObject *&>(SelectedClass));
		
		FOnClicked OnDeleteItemClicked = FOnClicked::CreateLambda([ChildDataHandle, ChildActorHandle]()->FReply {
			if (ChildActorHandle->IsValidHandle() == false || ChildDataHandle->IsValidHandle() == false)
				return FReply::Unhandled();
			uint32 Index = ChildDataHandle->GetIndexInArray();
			ChildDataHandle->GetParentHandle()->AsArray()->DeleteItem(Index);
			Index = ChildActorHandle->GetIndexInArray();
			ChildActorHandle->GetParentHandle()->AsArray()->DeleteItem(Index);
			return FReply::Handled();
		});

		ActorGroup.AddWidgetRow()
		BEGIN_BORDER_NAMECONTENT(FWeaponDataStyle::GetActorDataBackGroundColor())
		[
			SNew(SHorizontalBox)
			 + SHorizontalBox::Slot().HAlign(HAlign_Center).AutoWidth().VAlign(VAlign_Center).Padding(5,0)
			[
				SNew(SBox).MinDesiredWidth(250).MaxDesiredWidth(250) [
					ChildActorHandle->CreatePropertyValueWidget(false)
				]
			] + SHorizontalBox::Slot().HAlign(HAlign_Center).AutoWidth().VAlign(VAlign_Center).Padding(5,0)
			[
				SNew(SBox).Padding(0).VAlign(VAlign_Fill).HAlign(HAlign_Fill)
				.IsEnabled(SelectedClass != nullptr)
				[
					WeaponDAEditorHelper::CreateSmallButton(
						FOnClicked::CreateLambda([SelectedClass]()->FReply {
							if (SelectedClass && SelectedClass->ClassGeneratedBy)
							{
								if (UBlueprint * Blueprint = Cast<UBlueprint>(SelectedClass->ClassGeneratedBy))
								{
									UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>();
									AssetEditorSubsystem->FindEditorForAsset(Blueprint, true);
									AssetEditorSubsystem->OpenEditorForAsset(Blueprint);
									return FReply::Handled();
								}
							}
							return FReply::Unhandled();
						}),
					"Icons.Edit",
					"Open BP_WeaponActor"
					)
				]
			] + SHorizontalBox::Slot().HAlign(HAlign_Center).AutoWidth().VAlign(VAlign_Center).Padding(5,0)
			[
				WeaponDAEditorHelper::CreateSmallButton(
					OnDeleteItemClicked,
				"Icons.X",
				"Delete Weapon Actor"
				)
			]
		]
		END_BORDER_NAMECONTENT
		BEGIN_BORDER_VALUECONTENT(FWeaponDataStyle::GetActorDataBackGroundColor())
		[
			CreateActorInfo(ChildActorHandle, ChildDataHandle)
		]
		END_BORDER_VALUECONTENT;
	}
}

void FWeaponDataAssetDetailCustomization::CreateEquipmentCategory
(
	IDetailCategoryBuilder & DetailCategoryBuilder,
	IDetailLayoutBuilder & DetailBuilder,
	const TSharedRef<IPropertyHandle> & InClassHandle,
	const TSharedRef<IPropertyHandle> & InEquipmentHandle,
	const FString & InCategoryName
)
{
	InClassHandle->SetOnPropertyValueChanged(OnPropertyChanged(DetailBuilder));
	
	UObject * Temp = nullptr;
	InClassHandle->GetValue(Temp);
	const bool HasActionClass = Temp != nullptr;

	TSharedRef<SHorizontalBox> EquipmentHeaderValueContent = SNew(SHorizontalBox);
	{
		EquipmentHeaderValueContent->AddSlot().AutoWidth().HAlign(HAlign_Left) [
			InClassHandle->CreatePropertyValueWidget(true)
		];
		EquipmentHeaderValueContent->AddSlot().AutoWidth().HAlign(HAlign_Left).VAlign(VAlign_Center).FillWidth(1.0f).Padding(2.0f,0,0,0) [
			SNew(STextBlock)
				.Text(FText::FromString(TEXT("Equipment   Class   Not   Assigned")))
				.Font(GetBoldFont())
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FLinearColor(0.5f,0.1f,0.1f, 1.f))
				.Visibility(HasActionClass ? EVisibility::Hidden : EVisibility::Visible )
		];
	}
	
	IDetailGroup & EquipmentGroup = DetailCategoryBuilder.AddGroup(*InCategoryName, FText::FromString(InCategoryName));
	EquipmentGroup.HeaderRow()
	BEGIN_BORDER_NAMECONTENT(FWeaponDataStyle::GetEquipDataBackGroundColor())
	[
		InClassHandle->CreatePropertyNameWidget()
	]
	END_BORDER_NAMECONTENT
	BEGIN_BORDER_VALUECONTENT(FWeaponDataStyle::GetEquipDataBackGroundColor())
	[
		EquipmentHeaderValueContent
	]
	END_BORDER_VALUECONTENT
	;
	
	EquipmentGroup.AddPropertyRow(InEquipmentHandle)
		.DisplayName(FText::FromString(InCategoryName))
		.IsEnabled(HasActionClass)
		.ShowPropertyButtons(HasActionClass);
}

void FWeaponDataAssetDetailCustomization::CreateActionCategory
(
	IDetailCategoryBuilder & DetailCategoryBuilder,
	IDetailLayoutBuilder & DetailBuilder,
	const TSharedRef<IPropertyHandle> & InClassHandle,
	const TSharedRef<IPropertyHandle> & InActionHandle,
	const FString & InCategoryName
)
{
	InClassHandle->SetOnPropertyValueChanged(OnPropertyChanged(DetailBuilder));
	
	UObject * Temp = nullptr;
	InClassHandle->GetValue(Temp);
	const bool HasActionClass = Temp != nullptr;
	TSharedRef<SHorizontalBox> ActionHeaderValueContent = SNew(SHorizontalBox);
	{
		ActionHeaderValueContent->AddSlot().AutoWidth().HAlign(HAlign_Left) [
		   InClassHandle->CreatePropertyValueWidget()
	   ];
		ActionHeaderValueContent->AddSlot().AutoWidth().HAlign(HAlign_Left).VAlign(VAlign_Center).FillWidth(1.0f).Padding(2.0f,0,0,0) [
			SNew(STextBlock)
				.Text(FText::FromString(TEXT("Action   Class   Not   Assigned")))
				.Font(GetBoldFont())
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FLinearColor(0.5f,0.1f,0.1f, 1.f))
				.Visibility(HasActionClass ? EVisibility::Hidden : EVisibility::Visible )
		];
		if (InActionHandle->AsArray() != nullptr)
		{
			ActionHeaderValueContent->AddSlot().AutoWidth().HAlign(HAlign_Right).FillWidth(1.0f) [
				InActionHandle->CreatePropertyValueWidget(HasActionClass)
			];
		}
	}
	
	IDetailGroup & ActionGroup = DetailCategoryBuilder.AddGroup(*InCategoryName, FText::FromString(InCategoryName), false, true);
	ActionGroup.HeaderRow()
	BEGIN_BORDER_NAMECONTENT(FWeaponDataStyle::GetActionDataBackGroundColor())
	[
		InClassHandle->CreatePropertyNameWidget()
	]
	END_BORDER_NAMECONTENT
	BEGIN_BORDER_VALUECONTENT(FWeaponDataStyle::GetActionDataBackGroundColor())
	[
		SNew(SBox).HAlign(HAlign_Fill).VAlign(VAlign_Center).MinDesiredWidth(700)
		[
			ActionHeaderValueContent
		]
	]
	END_BORDER_VALUECONTENT
	;

	if (HasActionClass == false)
		return;
	
	if (InActionHandle->AsArray() != nullptr)
	{
		uint32 ArraySize;
		InActionHandle->AsArray()->GetNumElements(ArraySize);
		for (uint32 i = 0 ; i < ArraySize ; i++)
		{
			ActionGroup.AddPropertyRow(InActionHandle->AsArray()->GetElement(i))
				.DisplayName(FText::FromString(InCategoryName))
				.IsEnabled(HasActionClass)
				.ShowPropertyButtons(true);
		}
		InActionHandle->AsArray()->SetOnNumElementsChanged(OnPropertyChanged(DetailBuilder));
	}
	else
	{
		 ActionGroup.AddPropertyRow(InActionHandle)
			.DisplayName(FText::FromString(InCategoryName))
			.IsEnabled(HasActionClass)
			.ShowPropertyButtons(true);
	}
}

TSharedRef<SVerticalBox> FWeaponDataAssetDetailCustomization::CreateActorInfo
(
	const TSharedRef<IPropertyHandle> & InActorPropertyHandle,
	const TSharedRef<IPropertyHandle> & InActorDataHandle
)
{
	TSharedRef<SVerticalBox> ActorDetailInfoBox = SNew(SVerticalBox);

	UObject * SelectedObject;
	InActorPropertyHandle->GetValue(SelectedObject);
	UClass * SelectedClass = Cast<UClass>(SelectedObject);
	if (SelectedClass == nullptr)
	{
		ActorDetailInfoBox->AddSlot().AutoHeight()[
			SNew(STextBlock)
				.Text(FText::FromString("Actor   Class   Not   Assigned"))
				.Font(GetBoldFont())
				.ColorAndOpacity(FLinearColor(0.5f,0.1f,0.1f, 1.f))
				.Visibility(SelectedObject == nullptr ? EVisibility::Visible : EVisibility::Hidden)
		];
		return ActorDetailInfoBox;
	}

	TSharedPtr<IPropertyHandle> MeshPropertyHandle = InActorDataHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDH_WeaponActorData, MeshNames));
	TSharedPtr<IPropertyHandle> MeshSocketPropertyHandle = InActorDataHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDH_WeaponActorData, MeshSocketNames));
	TSharedRef<IPropertyHandleArray> MeshArrayHandle = MeshPropertyHandle->AsArray().ToSharedRef();
	TSharedRef<IPropertyHandleArray> MeshSocketArrayHandle = MeshSocketPropertyHandle->AsArray().ToSharedRef();
	FindRootMeshComponents(SelectedClass, MeshArrayHandle, MeshSocketArrayHandle);
	AddRootMeshesSlate(ActorDetailInfoBox, MeshArrayHandle, MeshSocketArrayHandle);

	TSharedPtr<IPropertyHandle> ColliderPropertyHandle = InActorDataHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDH_WeaponActorData, ColliderNames));
	TSharedPtr<IPropertyHandle> ColliderSocketPropertyHandle = InActorDataHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDH_WeaponActorData, ColliderSocketNames));
	TSharedRef<IPropertyHandleArray> ColliderArrayHandle = ColliderPropertyHandle->AsArray().ToSharedRef();
	TSharedRef<IPropertyHandleArray> ColliderSocketArrayHandle = ColliderSocketPropertyHandle->AsArray().ToSharedRef();
	FindRootColliderComponents(SelectedClass, ColliderArrayHandle, ColliderSocketArrayHandle);
	AddRootCollidersSlate(ActorDetailInfoBox, ColliderArrayHandle, ColliderSocketArrayHandle);

	return ActorDetailInfoBox;
}

void FWeaponDataAssetDetailCustomization::FindRootMeshComponents
(
	UClass * InClass,
	const TSharedRef<IPropertyHandleArray> & InMeshArrayHandle,
	const TSharedRef<IPropertyHandleArray> & InMeshDataArrayHandle
)
{
	if (InClass == nullptr)
		return ;

	TArray<UMeshComponent*> NativeMeshComponents;
	TArray<UMeshComponent*> BlueprintMeshComponents;
	WeaponDAEditorHelper::GetNativeRootComponents<UMeshComponent>(InClass, NativeMeshComponents);
	WeaponDAEditorHelper::GetBlueprintRootComponents<UMeshComponent>(InClass, BlueprintMeshComponents);
	
	TSet<FName> MeshComponentNamesTable;
	for (const UMeshComponent * Mesh : NativeMeshComponents)
		MeshComponentNamesTable.Add(Mesh->GetFName());
	for (const UMeshComponent * Mesh : BlueprintMeshComponents)
		MeshComponentNamesTable.Add(Mesh->GetFName());
	
	uint32 MeshesSize = 0;
	uint32 MeshSocketsSize = 0;
	InMeshArrayHandle->GetNumElements(MeshesSize);
	InMeshDataArrayHandle->GetNumElements(MeshSocketsSize);
	if (MeshesSize != MeshSocketsSize)
	{
		InMeshArrayHandle->EmptyArray();
		InMeshDataArrayHandle->EmptyArray();
	}

	TSet<FName> SavedMeshNames;
	for (int32 i = MeshesSize - 1 ; i >= 0; i--)
	{
		FName MeshName;
		InMeshArrayHandle->GetElement(i)->GetValue(MeshName);
		if (MeshComponentNamesTable.Contains(MeshName) == false)
			InMeshArrayHandle->DeleteItem(i);
		else
			SavedMeshNames.Add(MeshName);
	}
		
	for (const FName & MeshFName : MeshComponentNamesTable)
	{
		FString MeshName = MeshFName.ToString().Replace(TEXT("_GEN_VARIABLE"), TEXT(""));
		if (SavedMeshNames.Contains(FName(MeshName)) == true)
			continue;
		uint32 AppendedIndex = 0;
		InMeshArrayHandle->GetNumElements(AppendedIndex);
		InMeshArrayHandle->AddItem();
		InMeshDataArrayHandle->AddItem();
		InMeshArrayHandle->GetElement(AppendedIndex)->SetValue(FName(MeshName));
		InMeshDataArrayHandle->GetElement(AppendedIndex)->SetValue(NAME_None);
	}
}

void FWeaponDataAssetDetailCustomization::AddRootMeshesSlate
(
	const TSharedRef<SVerticalBox> & InVerticalBox,
	const TSharedRef<IPropertyHandleArray> & InMeshArrayHandle,
	const TSharedRef<IPropertyHandleArray> & InMeshDataArrayHandle
)
{
	uint32 MeshesSize;
	uint32 MeshSocketsSize;
	InMeshArrayHandle->GetNumElements(MeshesSize);
	InMeshDataArrayHandle->GetNumElements(MeshSocketsSize);
	if (MeshSocketsSize != MeshesSize)
	{
		InMeshArrayHandle->EmptyArray();
		InMeshDataArrayHandle->EmptyArray();
		MeshesSize = 0;
		MeshSocketsSize = 0;
	}
	if (MeshesSize == 0)
		return ;
	
	InVerticalBox->AddSlot().HAlign(HAlign_Fill).VAlign(VAlign_Center).Padding(0,5,0, 0)
	[
		SNew(SSeparator).Orientation(Orient_Horizontal)
	];
	InVerticalBox->AddSlot().HAlign(HAlign_Fill).AutoHeight().VAlign(VAlign_Center)
	[
		SNew(SHorizontalBox) + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(0) [
			SNew(SBox).MinDesiredWidth(200).MaxDesiredWidth(200).HAlign(HAlign_Center).VAlign(VAlign_Bottom).Padding(0,2.5f) [
				SNew(STextBlock).Text(FText::FromString("Mesh Name")).Font(GetBoldFont(7.5f))
			]
		] + SHorizontalBox::Slot().Padding(0).HAlign(HAlign_Center).VAlign(VAlign_Fill).FillWidth(1.0f) [
			SNew(SSeparator).Orientation(Orient_Vertical).Thickness(0.5f)
		] + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(0) [
			SNew(SBox).MinDesiredWidth(200).MaxDesiredWidth(200).HAlign(HAlign_Center).VAlign(VAlign_Bottom).Padding(0,2.5f) [
				SNew(STextBlock).Text(FText::FromString("Socket Name")).Font(GetBoldFont(7.5f))
			]
		]
	];
	InVerticalBox->AddSlot().HAlign(HAlign_Fill).VAlign(VAlign_Center).Padding(0)
	[
		SNew(SSeparator).Orientation(Orient_Horizontal)
	];
	for (uint32 i = 0 ;i < MeshesSize; i++)
	{
		InVerticalBox->AddSlot().HAlign(HAlign_Fill).AutoHeight().Padding(0)
		[
			SNew(SHorizontalBox) + SHorizontalBox::Slot().AutoWidth().Padding(0) [
				SNew(SBox).IsEnabled(false).MinDesiredWidth(200).MaxDesiredWidth(200).HAlign(HAlign_Fill).Padding(5,2.5f) [
					InMeshArrayHandle->GetElement(i)->CreatePropertyValueWidget(false)
				]
			] + SHorizontalBox::Slot().Padding( 0).HAlign(HAlign_Center).VAlign(VAlign_Fill).FillWidth(1.0f) [
				SNew(SSeparator).Orientation(Orient_Vertical).Thickness(0.5f)
			]  + SHorizontalBox::Slot().AutoWidth().Padding(0) [
				SNew(SBox).MinDesiredWidth(200).MaxDesiredWidth(200).HAlign(HAlign_Fill).Padding(5,2.5f) [
					InMeshDataArrayHandle->GetElement(i)->CreatePropertyValueWidget(false)
				]
			]
		];
	}
	InVerticalBox->AddSlot().HAlign(HAlign_Fill)
	[
		SNew(SSpacer)
	];
}

void FWeaponDataAssetDetailCustomization::FindRootColliderComponents
(
		UClass * InClass,
		const TSharedRef<IPropertyHandleArray> & InColliderArrayHandle,
		const TSharedRef<IPropertyHandleArray> & InColliderDataArrayHandle
)
{
	if (InClass == nullptr)
		return ;

	TArray<UShapeComponent*> NativeShapeComponents;
	TArray<UShapeComponent*> BlueprintShapeComponents;
	WeaponDAEditorHelper::GetNativeRootComponents<UShapeComponent>(InClass, NativeShapeComponents);
	WeaponDAEditorHelper::GetBlueprintRootComponents<UShapeComponent>(InClass, BlueprintShapeComponents);
	
	TSet<FName> ColliderComponentNamesTable;
	
	for (UShapeComponent * Shape : NativeShapeComponents)
		ColliderComponentNamesTable.Add(Shape->GetFName());
	for (UShapeComponent * Shape : BlueprintShapeComponents)
		ColliderComponentNamesTable.Add(Shape->GetFName());
	
	uint32 MeshesSize = 0;
	uint32 MeshSocketsSize = 0;
	InColliderArrayHandle->GetNumElements(MeshesSize);
	InColliderDataArrayHandle->GetNumElements(MeshSocketsSize);
	if (MeshesSize != MeshSocketsSize)
	{
		InColliderArrayHandle->EmptyArray();
		InColliderDataArrayHandle->EmptyArray();
	}

	TSet<FName> SavedMeshNames;
	for (int32 i = MeshesSize - 1 ; i >= 0; i--)
	{
		FName MeshName;
		InColliderArrayHandle->GetElement(i)->GetValue(MeshName);
		if (ColliderComponentNamesTable.Contains(MeshName) == false)
			InColliderArrayHandle->DeleteItem(i);
		else
			SavedMeshNames.Add(MeshName);
	}
	for (const FName & ColliderFName : ColliderComponentNamesTable)
	{
		FString ColliderName = ColliderFName.ToString().Replace(TEXT("_GEN_VARIABLE"), TEXT(""));
		if (SavedMeshNames.Contains(FName(ColliderName)) == true)
			continue;
		uint32 AppendedIndex = 0;
		InColliderArrayHandle->GetNumElements(AppendedIndex);
		InColliderArrayHandle->AddItem();
		InColliderDataArrayHandle->AddItem();
		InColliderArrayHandle->GetElement(AppendedIndex)->SetValue(FName(ColliderName));
		InColliderDataArrayHandle->GetElement(AppendedIndex)->SetValue(NAME_None);
	}
}


void FWeaponDataAssetDetailCustomization::AddRootCollidersSlate
(
	const TSharedRef<SVerticalBox> & InVerticalBox,
	const TSharedRef<IPropertyHandleArray> & InColliderArrayHandle,
	const TSharedRef<IPropertyHandleArray> & InColliderDataArrayHandle
)
{
	uint32 CollidersSize;
	uint32 ColliderSocketsSize;
	InColliderArrayHandle->GetNumElements(CollidersSize);
	InColliderDataArrayHandle->GetNumElements(ColliderSocketsSize);
	GLog->Log(FString::Printf(L"%u | %u", CollidersSize, ColliderSocketsSize));
	if (ColliderSocketsSize != CollidersSize)
	{
		InColliderArrayHandle->EmptyArray();
		InColliderDataArrayHandle->EmptyArray();
		CollidersSize = 0;
		ColliderSocketsSize = 0;
	}
	if (CollidersSize == 0)
		return;
	
	InVerticalBox->AddSlot().HAlign(HAlign_Fill).VAlign(VAlign_Center).Padding(0,5,0, 0)
	[
		SNew(SSeparator).Orientation(Orient_Horizontal)
	];
	InVerticalBox->AddSlot().HAlign(HAlign_Fill).AutoHeight().VAlign(VAlign_Center)
	[
		SNew(SHorizontalBox) + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(0) [
			SNew(SBox).MinDesiredWidth(200).MaxDesiredWidth(200).HAlign(HAlign_Center).VAlign(VAlign_Bottom).Padding(0,2.5f) [
				SNew(STextBlock).Text(FText::FromString("Collider Name")).Font(GetBoldFont(7.5f))
			]
		] + SHorizontalBox::Slot().Padding(0).HAlign(HAlign_Center).VAlign(VAlign_Fill).FillWidth(1.0f) [
			SNew(SSeparator).Orientation(Orient_Vertical).Thickness(0.5f)
		] + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(0) [
			SNew(SBox).MinDesiredWidth(200).MaxDesiredWidth(200).HAlign(HAlign_Center).VAlign(VAlign_Bottom).Padding(0,2.5f) [
				SNew(STextBlock).Text(FText::FromString("Socket Name")).Font(GetBoldFont(7.5f))
			]
		]
	];
	InVerticalBox->AddSlot().HAlign(HAlign_Fill).VAlign(VAlign_Center).Padding(0)
	[
		SNew(SSeparator).Orientation(Orient_Horizontal)
	];
	for (uint32 i = 0 ;i < CollidersSize; i++)
	{
		InVerticalBox->AddSlot().HAlign(HAlign_Fill).AutoHeight().Padding(0)
		[
			SNew(SHorizontalBox) + SHorizontalBox::Slot().AutoWidth().Padding(0) [
				SNew(SBox).IsEnabled(false).MinDesiredWidth(200).MaxDesiredWidth(200).HAlign(HAlign_Fill).Padding(5,2.5f) [
					InColliderArrayHandle->GetElement(i)->CreatePropertyValueWidget(false)
				]
			] + SHorizontalBox::Slot().Padding( 0).HAlign(HAlign_Center).VAlign(VAlign_Fill).FillWidth(1.0f) [
				SNew(SSeparator).Orientation(Orient_Vertical).Thickness(0.5f)
			]  + SHorizontalBox::Slot().AutoWidth().Padding(0) [
				SNew(SBox).MinDesiredWidth(200).MaxDesiredWidth(200).HAlign(HAlign_Fill).Padding(5,2.5f) [
					InColliderDataArrayHandle->GetElement(i)->CreatePropertyValueWidget(false)
				]
			]
		];
	}
	InVerticalBox->AddSlot().HAlign(HAlign_Fill)
	[
		SNew(SSpacer)
	];
}
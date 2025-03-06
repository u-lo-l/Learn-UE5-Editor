
#include "Tab/Details/PropertyCustomization/ActorDataInfoDetails.h"

#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "IDetailGroup.h"
#include "IPropertyUtilities.h"
#include "Data/DH_WeaponActorData.h"
#include "Style/WeaponDataStyle.h"

TSharedRef<IPropertyTypeCustomization> FActorDataInfoDetails::MakeInstance()
{
	return MakeShareable(new FActorDataInfoDetails);
}

void FActorDataInfoDetails::CustomizeHeader( TSharedRef<IPropertyHandle> PropertyHandle,
	FDetailWidgetRow & HeaderRow,
	IPropertyTypeCustomizationUtils & CustomizationUtils )
{
}

void FActorDataInfoDetails::CustomizeChildren( TSharedRef<IPropertyHandle> PropertyHandle,
	IDetailChildrenBuilder & ChildBuilder,
	IPropertyTypeCustomizationUtils & CustomizationUtils )
{
}

// void FActorDataInfoDetails::MeshSection
// (
// 	TSharedRef<IPropertyHandle> PropertyHandle,
// 	IDetailChildrenBuilder & ChildBuilder,
// 	IPropertyTypeCustomizationUtils & CustomizationUtils
// )
// {
// 	TSharedRef<IPropertyHandle> WeaponMeshHandle
// 		= PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDH_WeaponActorData, WeaponMeshes)).ToSharedRef();
// 	TSharedRef<IPropertyHandle> SocketNameHandle
// 		= PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDH_WeaponActorData, SocketNameToAttachMesh)).ToSharedRef();
//
// 	FOnClicked OnAddItemClicked = FOnClicked::CreateLambda([WeaponMeshHandle, SocketNameHandle, &CustomizationUtils]()->FReply {
// 		WeaponMeshHandle->AsArray()->AddItem();
// 		SocketNameHandle->AsArray()->AddItem();
// 		CustomizationUtils.GetPropertyUtilities()->ForceRefresh();
// 		return FReply::Handled();
// 	});
//
// 	FOnClicked OnClearArrayClicked = FOnClicked::CreateLambda([WeaponMeshHandle, SocketNameHandle, &CustomizationUtils]()->FReply {
// 		WeaponMeshHandle->AsArray()->EmptyArray();
// 		SocketNameHandle->AsArray()->EmptyArray();
// 		CustomizationUtils.GetPropertyUtilities()->ForceRefresh();
// 		return FReply::Handled();
// 	});
// 	
// 	
// 	IDetailGroup & MeshGroup = ChildBuilder.AddGroup("Mesh", FText::FromString("Mesh"));
//
// 	uint32 MeshCount;
// 	WeaponMeshHandle->GetNumChildren(MeshCount);
// 	
// 	MeshGroup.HeaderRow()
// 	BEGIN_BORDER_NAMECONTENT(FWeaponDataStyle::GetActorDataBackGroundColor())
// 	[
// 		SNew(STextBlock)
// 		.Text(FText::FromString(FString(L"Weapon Mesh") + (MeshCount > 1 ? L"es" : L"  ")))
// 		.Font(IDetailLayoutBuilder::GetDetailFont())
// 		.ColorAndOpacity(FColor::White)
// 	]
// 	END_BORDER_NAMECONTENT
// 	BEGIN_BORDER_VALUECONTENT(FWeaponDataStyle::GetActorDataBackGroundColor())
// 	[
// 		SNew(SHorizontalBox) + SHorizontalBox::Slot().Padding(5,0).AutoWidth().VAlign(VAlign_Center)
// 		[
// 			SNew(STextBlock)
// 			.Text(FText::FromString(FString::Printf(L"%d Array element", MeshCount) + (MeshCount > 1 ? L"s" : L" ")))
// 			.Font(IDetailLayoutBuilder::GetDetailFont())
// 			.ColorAndOpacity(FColor::White)
// 		]
// 		+ SHorizontalBox::Slot().Padding(5,0)
// 		[
// 			WeaponDAEditorHelper::CreateSmallButton(OnAddItemClicked,"Icons.PlusCircle")
// 		]
// 		+ SHorizontalBox::Slot().Padding(5,0)
// 		[
// 			WeaponDAEditorHelper::CreateSmallButton(OnClearArrayClicked,"Icons.Delete")
// 		]
// 	]
// 	END_BORDER_VALUECONTENT;
// 	
// 	for (uint32 i = 0; i < MeshCount; i++)
// 	{
// 		TSharedRef<IPropertyHandle> ChildHandle = WeaponMeshHandle->GetChildHandle(i).ToSharedRef();
// 		FOnClicked OnDeleteItemClicked = FOnClicked::CreateLambda([WeaponMeshHandle, SocketNameHandle, ChildHandle, &CustomizationUtils]()->FReply {
// 			if (ChildHandle->IsValidHandle() == false)
// 				return FReply::Unhandled();
// 			uint32 Index = ChildHandle->GetIndexInArray();
// 			WeaponMeshHandle->AsArray()->DeleteItem(Index);
// 			SocketNameHandle->AsArray()->DeleteItem(Index);
// 			CustomizationUtils.GetPropertyUtilities()->ForceRefresh();
// 			return FReply::Handled();
// 		});
//
// 		MeshGroup.AddWidgetRow()
// 		BEGIN_BORDER_NAMECONTENT(FWeaponDataStyle::GetActorDataBackGroundColor())
// 		[
// 			SNew(SVerticalBox)
// 			+ SVerticalBox::Slot().VAlign(VAlign_Center).HAlign(HAlign_Left)
// 			[
// 				SNew(STextBlock)
// 				.Text(FText::FromString(FString::Printf(L"Mesh %d", i + 1)))
// 				.Font(IDetailLayoutBuilder::GetDetailFont())
// 				.ColorAndOpacity(FLinearColor(0.6f,0.6f,0.6f,1))
// 			]
// 			+ SVerticalBox::Slot().VAlign(VAlign_Center).HAlign(HAlign_Left).Padding(0,0,0,1)
// 			[
// 				SNew(STextBlock)
// 				.Text(FText::FromString("Socket Name To Attach"))
// 				.Font(IDetailLayoutBuilder::GetDetailFont())
// 				.ColorAndOpacity(FColor::White)
// 			]
// 			+ SVerticalBox::Slot().VAlign(VAlign_Center).HAlign(HAlign_Left).AutoHeight()
// 			[
// 				SNew(SBox).MinDesiredWidth(150).MaxDesiredWidth(150)
// 				[
// 					SocketNameHandle->GetChildHandle(i)->CreatePropertyValueWidget(false)
// 				]
// 			]
// 		]
// 		END_BORDER_NAMECONTENT
// 		BEGIN_BORDER_VALUECONTENT(FWeaponDataStyle::GetActorDataBackGroundColor())
// 		[
// 			SNew(SHorizontalBox)
// 			+ SHorizontalBox::Slot()
// 			[
// 				SNew(SBox).MinDesiredWidth(500).MaxDesiredWidth(500)
// 				[
// 					WeaponMeshHandle->GetChildHandle(i)->CreatePropertyValueWidget(false)
// 				]
// 			]
// 			+ SHorizontalBox::Slot()
// 			[
// 				WeaponDAEditorHelper::CreateSmallButton(OnDeleteItemClicked,"Icons.X")
// 			]
// 		]
// 		END_BORDER_VALUECONTENT;
// 	}
// }

// void FActorDataInfoDetails::ColliderSection
// (
// 	TSharedRef<IPropertyHandle> PropertyHandle,
// 	IDetailChildrenBuilder & ChildBuilder,
// 	IPropertyTypeCustomizationUtils & CustomizationUtils
// )
// {
// 	TSharedRef<IPropertyHandle> ColliderHandle
// 		= PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDH_WeaponActorData, Colliders)).ToSharedRef();
// 	ChildBuilder.AddProperty(ColliderHandle).ShowPropertyButtons(true);
// }

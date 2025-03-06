#pragma once

#include "CoreMinimal.h"
#include "Components/ShapeComponent.h"
#include "Engine/SCS_Node.h"
#include "Engine/SimpleConstructionScript.h"

class SUniformGridPanel;
class IDetailLayoutBuilder;

#define BEGIN_BORDER_NAMECONTENT(BACKGROUND)\
.NameContent().HAlign(HAlign_Fill).VAlign(VAlign_Fill)\
[\
	SNew(SBorder).BorderImage(BACKGROUND)\
	.HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(10,0,0,0)

#define END_BORDER_NAMECONTENT \
]

#define BEGIN_BORDER_CUSTOMNAMECONTENT(BACKGROUND)\
.CustomNameContent().HAlign(HAlign_Fill).VAlign(VAlign_Fill)\
[\
SNew(SBorder).BorderImage(BACKGROUND)\
.HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(10,0,0,0)

#define END_BORDER_CUSTOMNAMECONTENT \
]

#define BEGIN_BORDER_VALUECONTENT(BACKGROUND)\
	.ValueContent().HAlign(HAlign_Fill).VAlign(VAlign_Fill)\
	[\
		SNew(SBorder).BorderImage(BACKGROUND)\
		.HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(10,0,0,0)
#define END_BORDER_VALUECONTENT ]

#define BEGIN_BORDER_CUSTOMVALUECONTENT(BACKGROUND)\
	.CustomValueContent().HAlign(HAlign_Fill).VAlign(VAlign_Fill)\
	[\
		SNew(SBorder).BorderImage(BACKGROUND)\
		.HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(10,0,0,0)
#define END_BORDER_CUSTOMVALUECONTENT ]

class DHWEAPON_API FWeaponDataStyle
{
public:
	static FSlateBrush * GetActorDataBackGroundColor() {return ActorDataBackGroundColor.Get();}
	static FSlateBrush * GetEquipDataBackGroundColor() {return EquipDataBackGroundColor.Get();}
	static FSlateBrush * GetActionDataBackGroundColor() {return ActionDataBackGroundColor.Get();}
	static FSlateBrush * GetDamageDataBackGroundColor() {return DamageDataBackGroundColor.Get();}
private :
	// static FSlateIcon EditorIcon;
	
	static TSharedPtr<FSlateBrush> ActorDataBackGroundColor;
	static TSharedPtr<FSlateBrush> EquipDataBackGroundColor;
	static TSharedPtr<FSlateBrush> ActionDataBackGroundColor;
	static TSharedPtr<FSlateBrush> DamageDataBackGroundColor;
};

namespace WeaponDAEditorHelper
{
	TSharedRef<SCheckBox> CreateCheckBox(
		const TSharedPtr<IPropertyHandle>& PropertyHandle,
		const FText& CheckBoxLabel,
		IPropertyTypeCustomizationUtils & CustomizationUtils
	);

	TSharedRef<SUniformGridPanel> CreateVector(
		const TSharedPtr<IPropertyHandle>& PropertyHandle
	);

	void CustomPropertyArray(
		const TSharedRef<IPropertyHandle> & PropertyHandle,
		IDetailChildrenBuilder & ChildBuilder
	);
	void CustomPropertyArray(
		const TSharedRef<IPropertyHandle> & PropertyHandle,
		IDetailChildrenBuilder & ChildBuilder,
		FSlateBrush * BorderStyle
	);

	TSharedRef<SBox> CreateSmallButton(
		const FOnClicked & OnClickedDelegate,
		FName IconName,
		const FString & Tooltip = "" 
	);

	template <class T>
	void GetNativeRootComponents(UClass * InClass, TArray<T*> & OutComponents)
	{
		OutComponents.Empty();
		AActor * CDO = Cast<AActor>(InClass->GetDefaultObject());
		if (CDO == nullptr)
			return ;
		CDO->GetComponents<T>(OutComponents);
		int32 ArrayCount = OutComponents.Num();
		for (int32 i = ArrayCount - 1; i >= 0; --i)
		{
			USceneComponent * Parent = OutComponents[i]->GetAttachParent();
			if (Parent == nullptr || Parent->GetAttachParent() != nullptr)
				OutComponents.RemoveAt(i);
		}
	}

	template <class T>
	void GetBlueprintRootComponents(UClass * InClass, TArray<T*> & OutComponents)
	{
		OutComponents.Empty();
		UBlueprintGeneratedClass* BPGC = Cast<UBlueprintGeneratedClass>(InClass);
		if (BPGC == nullptr)
			return;
		const TArray<USCS_Node*>& ActorBlueprintNodes = BPGC->SimpleConstructionScript->GetRootNodes();
		for (USCS_Node* Node : ActorBlueprintNodes)
		{
			if (Node->ComponentClass->IsChildOf(T::StaticClass()))
			{
				if (T* Component = Cast<T>(Node->ComponentTemplate))
				{
					OutComponents.Add(Component);
				}
			}
		}
	}
}
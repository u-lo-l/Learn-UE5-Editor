#pragma once

#include "CoreMinimal.h"

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

class LEARNASSETDEFINITION_API FWeaponDataStyle
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
		FName IconName
	);
}
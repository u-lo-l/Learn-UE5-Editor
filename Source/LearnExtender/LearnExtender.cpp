#include "LearnExtender.h"
#include "LevelEditor.h"
#include "Modules/ModuleManager.h"
#include "Widgets/Input/SSlider.h"

using EExtensionHook::Position;

#define LOCTEXT_NAMESPACE "FLearnExtenderModule"

FLearnExtenderModule::FLearnExtenderModule()
	: LevelEditorModule(FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor"))
{
}

void FLearnExtenderModule::StartupModule()
{
	GLog->Log("LearnExtenderModule is Starting");
	Extender = MakeShareable(new FExtender);
    
	StartUpMenuBarExtension();
	StartUpMenuExtension();
	StartUpToolBarExtension();
}

void FLearnExtenderModule::ShutdownModule()
{
	GLog->Log("LearnExtenderModule is Finishing");
	ShutdownMenuExtension();
	ShutDownMenuBarBarExtension();
	ShutdownToolBarExtension();
    
	if (Extender.IsValid())
		Extender.Reset();
}

void FLearnExtenderModule::StartUpMenuBarExtension()
{
	FMenuBarExtensionDelegate MenubarExtensionDelegate;
	MenubarExtensionDelegate.BindRaw(this, &FLearnExtenderModule::MenuBarExtensionDelegate);
    
	MenuBarExtensions.Add(Extender->AddMenuBarExtension("Help", Position::After, nullptr, MenubarExtensionDelegate));
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(Extender);
}

void FLearnExtenderModule::StartUpMenuExtension()
{
	    FMenuExtensionDelegate Delegate;
    Delegate.BindLambda([](FMenuBuilder & MenuBuilder)->void {
        
        MenuBuilder.AddMenuSeparator("MenuSeparator");
        MenuBuilder.AddMenuEntry(
            FText::FromString("MenuEntry"),
            FText::FromString("Tooltip for MenuEntry"),
            FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Blueprint"),
            FUIAction(FExecuteAction::CreateLambda([] ()->void {
                UE_LOG(LogTemp, Log, TEXT("MenuEntry Clicked"))
            })),
            "MenuEntry"
        );
        MenuBuilder.AddSeparator("Separator");
        
        MenuBuilder.BeginSection("SubMenuSection", FText::FromString("Section SubMenu"));
        FNewMenuDelegate SubMenuDelegate; //DECLARE_DELEGATE_OneParam( FNewMenuDelegate, class FMenuBuilder& )
        SubMenuDelegate.BindLambda([] (FMenuBuilder & InMenuBuilder)->void {
            UE_LOG(LogTemp, Log, TEXT("SubMenu Clicked"));
            InMenuBuilder.AddMenuEntry(
                FText::FromString("Menu In SubMenu"),
                FText::FromString("Menu In SubMenu"),
                FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Blueprint"),
                FUIAction(FExecuteAction::CreateLambda([] ()->void {
                    UE_LOG(LogTemp, Log, TEXT("Menu In SubMenu Clicked"))
                })),
                "MenuInSubMenu"
            );
        });
        MenuBuilder.AddSubMenu(
            FText::FromString("SubMenu"),
            FText::FromString("Tooltip for SubMenu"),
            SubMenuDelegate,
            true,
            FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Blueprint"),
            true,
            "SubMenu"
        );
        MenuBuilder.EndSection();
        
        MenuBuilder.BeginSection("WrapperSubMenuSection", FText::FromString("Section SubMenu"));
        FOnGetContent WrapperSubMenuDelegate; // DECLARE_DELEGATE_RetVal(TSharedRef<SWidget>, FOnGetContent)
        WrapperSubMenuDelegate.BindLambda([] ()->TSharedRef<SWidget> {
            UE_LOG(LogTemp, Log, TEXT("WrapperSubMenu Clicked"));
            return SNew(SButton).Text(FText::FromString("WrapperSubMenu Button"));
        });
        MenuBuilder.AddWrapperSubMenu(
           FText::FromString("WrapperSubMenu"),
           FText::FromString("Tooltip for WrapperSubMenu"),
           WrapperSubMenuDelegate,
           FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Blueprint")
        );
        MenuBuilder.EndSection();

        MenuBuilder.BeginSection("WidgetSection", FText::FromString("Section Widget"));
        MenuBuilder.AddWidget(
            SNew(SVerticalBox) + SVerticalBox::Slot()
            .AutoHeight()
            [
                SNew(SSlider)
                .OnValueChanged_Lambda([](float NewValue) {
                    UE_LOG(LogTemp, Log, TEXT("Slider1 Value: %f"), NewValue);
                })
                .MinValue(0.0f)
                .MaxValue(100.0f)
                .Value(50.0f)
            ] + SVerticalBox::Slot()
            .AutoHeight()
            [
                SNew(SSlider)
                .OnValueChanged_Lambda([](float NewValue) {
                    UE_LOG(LogTemp, Log, TEXT("Slider2 Value: %f"), NewValue);
                })
                .MinValue(0.0f)
                .MaxValue(100.0f)
                .Value(50.0f)
            ]+ SVerticalBox::Slot()
            .AutoHeight()
            [
                SNew(SSlider)
                .OnValueChanged_Lambda([](float NewValue) {
                    UE_LOG(LogTemp, Log, TEXT("Slider3 Value: %f"), NewValue);
                })
                .MinValue(0.0f)
                .MaxValue(100.0f)
                .Value(50.0f)
            ],
            FText::FromString("VerticalBox"),
            true,
            true,
            FText::FromString("Tooltip for VerticalBox")
        );
        MenuBuilder.AddWidget(
            SNew(SHorizontalBox) + SHorizontalBox::Slot()
            .AutoWidth()
            [
                SNew(SCheckBox).OnCheckStateChanged_Lambda([](ECheckBoxState NewState) {
                    if (NewState == ECheckBoxState::Checked) {
                        UE_LOG(LogTemp, Log, TEXT("Checkbox1 Checked"));
                    } else {
                        UE_LOG(LogTemp, Log, TEXT("Checkbox1 Unchecked"));
                    }
                })
            ] + SHorizontalBox::Slot()
            .AutoWidth()
            [
                SNew(SCheckBox).OnCheckStateChanged_Lambda([](ECheckBoxState NewState) {
                    if (NewState == ECheckBoxState::Checked) {
                        UE_LOG(LogTemp, Log, TEXT("Checkbox2 Checked"));
                    } else {
                        UE_LOG(LogTemp, Log, TEXT("Checkbox2 Unchecked"));
                    }
                })
            ] + SHorizontalBox::Slot()
            .AutoWidth()
            [
                SNew(SCheckBox).OnCheckStateChanged_Lambda([](ECheckBoxState NewState) {
                    if (NewState == ECheckBoxState::Checked) {
                        UE_LOG(LogTemp, Log, TEXT("Checkbox3 Checked"));
                    } else {
                        UE_LOG(LogTemp, Log, TEXT("Checkbox3 Unchecked"));
                    }
                })
            ],
            FText::FromString("Horizontal Box"),
            true,
            true,
            FText::FromString("Tooltip for Horizontal Box")
        );
        MenuBuilder.EndSection();
    });

    Extender->AddMenuExtension("MenuElement01", Position::After,nullptr, Delegate);
    LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(Extender);
}

void FLearnExtenderModule::StartUpToolBarExtension()
{
	    GLog->Log("StartUpToolBarExtension");
    FToolBarExtensionDelegate Delegate; // DECLARE_DELEGATE_OneParam( FToolBarExtensionDelegate, class FToolBarBuilder& )
    Delegate.BindLambda([](FToolBarBuilder & InToolBarBuilder) {
        InToolBarBuilder.AddSeparator();
        InToolBarBuilder.AddToolBarButton(
            FUIAction(FExecuteAction::CreateLambda([] ()->void {
                    UE_LOG(LogTemp, Log, TEXT("Toolbar Button Clicked"))
            })),
            "ToolbarButton",
            FText::FromString("ToolbarButton"),
            FText::FromString("Tooltip for ToolbarButton"),
            FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Blueprint")
        );
        InToolBarBuilder.AddSeparator();
        FOnGetContent ComboButtonDelegate; //DECLARE_DELEGATE_RetVal(TSharedRef<SWidget>,FOnGetContent)
        ComboButtonDelegate.BindLambda([]()->TSharedRef<SWidget> {
            FMenuBuilder MenuBuilder(true, nullptr);
            MenuBuilder.AddMenuEntry(
               FText::FromString("Option 1"),
               FText::FromString("Option 1 Tooltip"),
               FSlateIcon(),
               FUIAction(FExecuteAction::CreateLambda([]() {
                   UE_LOG(LogTemp, Log, TEXT("Option 1 Selected"));
               }))
            );
            MenuBuilder.AddMenuEntry(
               FText::FromString("Option 2"),
               FText::FromString("Option 2 Tooltip"),
               FSlateIcon(),
               FUIAction(FExecuteAction::CreateLambda([]() {
                   UE_LOG(LogTemp, Log, TEXT("Option 2 Selected"));
               }))
            );
            return MenuBuilder.MakeWidget();
        });
        InToolBarBuilder.AddComboButton(
            FUIAction(),
            ComboButtonDelegate,
            FText::FromString("SimpleToolbarComboButton"),
            FText::FromString("Tooltip for SimpleToolbarComboButton"),
            FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Blueprint"),
            false
        );
        // InToolBarBuilder.AddToolBarButton();
        // InToolBarBuilder.AddToolBarWidget();
        // InToolBarBuilder.AddWidget();
        
    });
    Extender->AddToolBarExtension(
        "Play",
        EExtensionHook::After,
        MakeShareable(new FUICommandList()),
        Delegate
    );
    LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(Extender);
}

void FLearnExtenderModule::ShutDownMenuBarBarExtension()
{
}

void FLearnExtenderModule::ShutdownMenuExtension()
{
}

void FLearnExtenderModule::ShutdownToolBarExtension()
{
}

void FLearnExtenderModule::MenuBarExtensionDelegate( FMenuBarBuilder & MenuBarBuilder )
{
	FNewMenuDelegate PullDownDelegate;
	PullDownDelegate.BindLambda([](FMenuBuilder & MenuBuilder)->void {
		MenuBuilder.AddMenuEntry(
			FText::FromString("Test MenuElement01"),
			FText::FromString("Tooltip for Test MenuElement01"),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Blueprint"),
			FUIAction(FExecuteAction::CreateLambda([]()->void {
				UE_LOG(LogTemp, Log, TEXT("Hello MenuElement01"))
		})),
		"MenuElement01"
	);
});
    
	MenuBarBuilder.AddPullDownMenu(
		FText::FromString("Menu01"),
		FText::FromString("Tool Tip For Custom Menu1"),
		PullDownDelegate,
		"Menu01",
		"CUSTOM MENU01"
	);

	const FNewMenuDelegate EmptyDelegate;
	MenuBarBuilder.AddPullDownMenu(
		FText::FromString("Menu01_1"),
		FText::FromString("Tool Tip For Custom Menu1_!"),
		EmptyDelegate,
		"Menu01_1",
		"CUSTOM MENU01_1"
	);
	MenuBarBuilder.AddMenuEntry(
		FText::FromString("Test MenuBarBuilder_AddMenuEntry"),
			FText::FromString("Tooltip for Test MenuBarBuilder_AddMenuEntry"),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Blueprint"),
			FUIAction(FExecuteAction::CreateLambda([]()->void {
				UE_LOG(LogTemp, Log, TEXT("Hello MenuBarBuilder_AddMenuEntry"))
	})),
	"MenuBarBuilder_AddMenuEntry"
);
    
	FOnGetContent InMenuContentGeneratorDelegate;
	InMenuContentGeneratorDelegate.BindLambda([]()->TSharedRef<SWidget> {
		return
			SNew(SButton).Text(FText::FromString("TestButton"));
	});
	MenuBarBuilder.AddPullDownMenu(
		FText::FromString("Menu02"),
		FText::FromString("Tool Tip For Custom Menu2"),
		InMenuContentGeneratorDelegate,
		"Menu02",
		"CUSTOM MENU02"
	);
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FLearnExtenderModule, LearnExtender)
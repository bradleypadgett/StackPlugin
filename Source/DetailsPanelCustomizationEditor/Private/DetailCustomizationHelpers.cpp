#include "DetailCustomizationHelpers.h"
#include "PropertyEditorModule.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"

namespace DetailCustomizationHelpers
{
    void RegisterDetailCustomization(FPropertyEditorModule& PropertyModule, const FString& ClassName, TSharedRef<IDetailCustomization> CustomizationInstance)
    {
        PropertyModule.RegisterCustomClassLayout(*ClassName, FOnGetDetailCustomizationInstance::CreateLambda([CustomizationInstance]() { return CustomizationInstance; }));
    }

    void AddCenteredButton(IDetailCategoryBuilder& Category, const FString& ButtonText, TFunction<FReply()> OnClick)
    {
        Category.AddCustomRow(FText::FromString(ButtonText))
            .WholeRowContent()
            [
                SNew(SHorizontalBox)
                    + SHorizontalBox::Slot()
                    .HAlign(HAlign_Center)
                    .VAlign(VAlign_Center)
                    .FillWidth(1.0f)
                    [
                        SNew(SButton)
                            .ContentPadding(FMargin(20.0f, 10.0f))
                            .HAlign(HAlign_Center)
                            .VAlign(VAlign_Center)
                            .Text(FText::FromString(ButtonText))
                            .OnClicked_Lambda(OnClick)
                    ]
            ];
    }

    void AddCenteredButton(IDetailCategoryBuilder& Category, const FString& ButtonText, UObject* Object, UFunction* Function)
    {
        Category.AddCustomRow(FText::FromString(ButtonText))
            .WholeRowContent()
            [
                SNew(SHorizontalBox)
                    + SHorizontalBox::Slot()
                    .HAlign(HAlign_Center)
                    .VAlign(VAlign_Center)
                    .FillWidth(1.0f)
                    [
                        SNew(SButton)
                            .ContentPadding(FMargin(20.0f, 10.0f))
                            .HAlign(HAlign_Center)
                            .VAlign(VAlign_Center)
                            .Text(FText::FromString(ButtonText))
                            .OnClicked_Lambda([Object, Function]()
                            {
                                if (Object && Function)
                                {
                                    Object->ProcessEvent(Function, nullptr);
                                }
                                return FReply::Handled();
                            })
                    ]
            ];
    }
}

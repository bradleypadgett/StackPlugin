#include "DetailCustomizationHelpers.h"
#include "PropertyEditorModule.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"

namespace DetailCustomizationHelpers
{
    TArray<FDetailCustomizationEntry>& GetCustomizationRegistry()
    {
        static TArray<FDetailCustomizationEntry> Registry;
        return Registry;
    }

    void RegisterCustomization(const FString& ClassName, TFunction<TSharedRef<IDetailCustomization>()> Factory)
    {
        GetCustomizationRegistry().Add(FDetailCustomizationEntry(ClassName, Factory));
    }

    void RegisterAllCustomizations(FPropertyEditorModule& PropertyModule)
    {
        for (const FDetailCustomizationEntry& Entry : GetCustomizationRegistry())
        {
            PropertyModule.RegisterCustomClassLayout(
                *Entry.ClassName,
                FOnGetDetailCustomizationInstance::CreateLambda(Entry.CustomizationFactory)
            );
        }
    }

    void AddCenteredButton(IDetailCategoryBuilder& Category, const FString& ButtonText, TFunction<FReply()> OnClick, TFunction<bool()> IsEnabled)
    {
        Category.AddCustomRow(FText::FromString(ButtonText))
            .WholeRowContent()
            [
                SNew(SHorizontalBox)
                    + SHorizontalBox::Slot()
                    .HAlign(HAlign_Center)
                    [
                        SNew(SButton)
                            .Text(FText::FromString(ButtonText))
                            .OnClicked_Lambda([OnClick]() { return OnClick(); })
                            .IsEnabled_Lambda([IsEnabled]()
                                {
                                    if (IsEnabled)
                                    {
                                        return IsEnabled();
                                    }
                                    return true; // Default to enabled if no function provided
                                })
                    ]
            ];
    }
}

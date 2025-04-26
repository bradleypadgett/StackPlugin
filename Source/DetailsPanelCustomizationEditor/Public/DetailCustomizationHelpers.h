#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class IDetailCategoryBuilder;
class FPropertyEditorModule;

#ifndef DETAILCUSTOMIZATIONHELPERS_API
#define DETAILCUSTOMIZATIONHELPERS_API DETAILSPANELCUSTOMIZATIONEDITOR_API
#endif

namespace DetailCustomizationHelpers
{

    struct FDetailCustomizationEntry
    {
        FString ClassName;
        TFunction<TSharedRef<IDetailCustomization>()> CustomizationFactory;

        FDetailCustomizationEntry(const FString& InClassName, TFunction<TSharedRef<IDetailCustomization>()> InFactory)
            : ClassName(InClassName), CustomizationFactory(InFactory)
        {
        }
    };

    DETAILSPANELCUSTOMIZATIONEDITOR_API TArray<FDetailCustomizationEntry>& GetCustomizationRegistry();

    DETAILSPANELCUSTOMIZATIONEDITOR_API void RegisterCustomization(const FString& ClassName, TFunction<TSharedRef<IDetailCustomization>()> Factory);

    DETAILSPANELCUSTOMIZATIONEDITOR_API void RegisterAllCustomizations(FPropertyEditorModule& PropertyModule);

    DETAILSPANELCUSTOMIZATIONEDITOR_API void AddCenteredButton(IDetailCategoryBuilder& Category, const FString& ButtonText, TFunction<FReply()> OnClick, TFunction<bool()> IsEnabled = nullptr);

}

// Auto-register macro
#define REGISTER_DETAIL_CUSTOMIZATION(ClassType, CustomizationType) \
namespace DetailCustomizationHelpers_Internal \
{ \
    struct FAutoRegister##CustomizationType \
    { \
        FAutoRegister##CustomizationType() \
        { \
            DetailCustomizationHelpers::RegisterCustomization(ClassType::StaticClass()->GetName(), []() { return MakeShared<CustomizationType>(); }); \
        } \
    }; \
    static FAutoRegister##CustomizationType AutoRegister_##CustomizationType; \
}

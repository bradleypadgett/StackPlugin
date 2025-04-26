#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class IDetailCategoryBuilder;
class FPropertyEditorModule;


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

    DETAILSCUSTOMIZATIONEDITOR_API TArray<FDetailCustomizationEntry>& GetCustomizationRegistry();

    DETAILSCUSTOMIZATIONEDITOR_API void RegisterCustomization(const FString& ClassName, TFunction<TSharedRef<IDetailCustomization>()> Factory);

    DETAILSCUSTOMIZATIONEDITOR_API void RegisterAllCustomizations(FPropertyEditorModule& PropertyModule);

    DETAILSCUSTOMIZATIONEDITOR_API void AddCenteredButton(IDetailCategoryBuilder& Category, const FString& ButtonText, TFunction<FReply()> OnClick, TFunction<bool()> IsEnabled = nullptr);

}

//Auto-register macro
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

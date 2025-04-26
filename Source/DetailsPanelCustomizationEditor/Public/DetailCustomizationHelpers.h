#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class IDetailCategoryBuilder;
class FPropertyEditorModule;

namespace DetailCustomizationHelpers
{
    DETAILSCUSTOMIZATIONEDITOR_API void RegisterDetailCustomization(FPropertyEditorModule& PropertyModule, const FString& ClassName, TSharedRef<IDetailCustomization> CustomizationInstance);

    void AddCenteredButton(IDetailCategoryBuilder& Category, const FString& ButtonText, TFunction<FReply()> OnClick);

    void AddCenteredButton(IDetailCategoryBuilder& Category, const FString& ButtonText, UObject* Object, UFunction* Function);
}
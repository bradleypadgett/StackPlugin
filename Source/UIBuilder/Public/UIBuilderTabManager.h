#pragma once
#include "CoreMinimal.h"



class FBlueprintEditor;
class SGraphEditor;
class UUIBuilderBlueprintExtension;

/*
 * Manages tab layout, mode switching, and UI logic.
 */
class FUIBuilderTabManager : public TSharedFromThis<FUIBuilderTabManager>
{
public:

    static void HandleGraphMode(FBlueprintEditor* InBlueprintEditor, UUIBuilderBlueprintExtension* InBlueprintExtension, FName InNewMode);
    static void CaptureGraphLayout(FBlueprintEditor* InBlueprintEditor, UUIBuilderBlueprintExtension* InBlueprintExtension);
    static void StoreOpenedGraphTabs(FBlueprintEditor* InBlueprintEditor, UUIBuilderBlueprintExtension* InBlueprintExtension);
    static void CloseStoredGraphTabs(FBlueprintEditor* InBlueprintEditor, UUIBuilderBlueprintExtension* InBlueprintExtension);
    static void ApplyGraphLayout(FBlueprintEditor* InBlueprintEditor, UUIBuilderBlueprintExtension* InBlueprintExtension);

    static void HandleDesignerMode(FBlueprintEditor* InBlueprintEditor, UUIBuilderBlueprintExtension* InBlueprintExtension, FName InNewMode);
    static void CaptureDesignerLayout(FBlueprintEditor* InBlueprintEditor, UUIBuilderBlueprintExtension* InBlueprintExtension);
    static void StoreOpenedDesignerTabs(FBlueprintEditor* InBlueprintEditor, UUIBuilderBlueprintExtension* InBlueprintExtension);
    static void CloseStoredDesignerTabs(FBlueprintEditor* InBlueprintEditor, UUIBuilderBlueprintExtension* InBlueprintExtension);
    static void ApplyDesignerLayout(FBlueprintEditor* InBlueprintEditor, UUIBuilderBlueprintExtension* InBlueprintExtension);

private:

    static TArray<FName> GetOpenTabIDs(TSharedPtr<FTabManager> InTabManager, const TArray<FName>& InKnownTabs);

    static void CloseTabIfOpen(TSharedPtr<FTabManager> InTabManager, FName InTabId);

};

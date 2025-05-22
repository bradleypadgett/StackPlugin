#pragma once



class UUIBuilderBlueprintExtension;
class UUIBuilderGraph; 
class FSpawnTabArgs;
class FUIDesignerBlueprintEditor;
class FBlueprintEditor;
class FUIDesignerMode;

/*
 * Helper class for managing tab layout + registration
 */
class FUIDesignerTabs : public TSharedFromThis<FUIDesignerTabs>
{
public:

    static void RegisterDesignerModeTabs(FUIDesignerBlueprintEditor* InBlueprint, TSharedPtr<FTabManager> InTabManager);
    static TSharedRef<FTabManager::FLayout> CreateDefaultLayout();

private:

    static void RegisterDefaultTabs(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory);

    static void RegisterGraphEditor(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory, UUIBuilderBlueprintExtension* InExtension);
    static void RegisterPreviewTab(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory);
    static void RegisterSelectionTab(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory);
    static void RegisterVariableTab(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory);
};

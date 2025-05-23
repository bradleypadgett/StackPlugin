#pragma once



class UPanelDesignerBlueprintExtension;
class UPanelDesignerGraph; 
class FSpawnTabArgs;
class FPanelDesignerBlueprintEditor;
class FBlueprintEditor;
class FPanelDesignerMode;

/*
 * Helper class for managing tab layout + registration
 */
class FPanelDesignerTabs : public TSharedFromThis<FPanelDesignerTabs>
{
public:

    static void RegisterDesignerModeTabs(FPanelDesignerBlueprintEditor* InBlueprint, TSharedPtr<FTabManager> InTabManager);
    static TSharedRef<FTabManager::FLayout> CreateDefaultLayout();

private:

    static void RegisterDefaultTabs(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory);

    static void RegisterGraphEditor(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory, UPanelDesignerBlueprintExtension* InExtension);
    static void RegisterPreviewTab(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory);
    static void RegisterSelectionTab(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory);
    static void RegisterVariableTab(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory);
};

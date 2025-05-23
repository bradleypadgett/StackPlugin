#pragma once



class UPanelDesignerBlueprintExtension;
class FPanelDesignerBlueprintEditor;

/*
 *  Static helper class for managing tab layout + registration
 */
class FPanelDesignerTabs : public TSharedFromThis<FPanelDesignerTabs>
{
public:

    static void RegisterDesignerModeTabs(FPanelDesignerBlueprintEditor* InBlueprint, TSharedPtr<FTabManager> InTabManager);

private:

    static void RegisterDefaultTabs(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory);

    static void RegisterGraphEditor(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory, UPanelDesignerBlueprintExtension* InExtension);
    static void RegisterPreviewTab(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory);
    static void RegisterSelectionTab(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory);
    static void RegisterVariableTab(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory);

public:

    static TSharedRef<FTabManager::FLayout> CreateDefaultLayout();
};
#pragma once
#include "Internationalization/Internationalization.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"
#include "Internationalization/Text.h"
#include "Templates/SharedPointer.h"

#define LOCTEXT_NAMESPACE "StackBlueprint"



struct FSlateBrush;

class SDockTab;
class SGraphEditor;
class SWidget;
class UBlueprint;
class UStackBlueprintExtension;
class FStackBlueprintEditor;



struct FDesignerGraphSummoner : public FWorkflowTabFactory
{
public:
    FDesignerGraphSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp);

    virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;

    virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override
    {
        return LOCTEXT("DesignerTooltip", ":)");
    }
};

struct FSelectionSummoner : public FWorkflowTabFactory
{
public:
    FSelectionSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp);

    virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;

    virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override
    {
        return LOCTEXT("SelectionTooltip", ":)");
    }
};

struct FVariableSummoner : public FWorkflowTabFactory
{
public:
    FVariableSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp);

    virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;

    virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override
    {
        return LOCTEXT("VariableTooltip", "hi");
    }
};

struct FPaletteSummoner: public FWorkflowTabFactory
{
public:
    FPaletteSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp);

    virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;

    virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override
    {
        return LOCTEXT("PaletteTooltip", "yo");
    }
};

struct FPreviewSummoner : public FWorkflowTabFactory
{
public:
    FPreviewSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp);

    virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;

    virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override
    {
        return LOCTEXT("PreviewTooltip", "yo");
    }
};



#undef LOCTEXT_NAMESPACE
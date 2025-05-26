#pragma once
#include "BlueprintEditor.h"
#include "Delegates/Delegate.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph/EdGraphSchema.h"
#include "Engine/TimelineTemplate.h"
#include "HAL/PlatformMath.h"
#include "Internationalization/Internationalization.h"
#include "Internationalization/Text.h"
#include "Math/Vector2D.h"
#include "Misc/Attribute.h"
#include "Misc/Guid.h"
#include "Templates/SharedPointer.h"
#include "UObject/Object.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"
#include "WorkflowOrientedApp/WorkflowUObjectDocuments.h"

#define LOCTEXT_NAMESPACE "PanelDesigner"



struct FSlateBrush;

class SDockTab;
class SGraphEditor;
class SWidget;
class UBlueprint;
class UPanelDesignerExtension;
class FPanelDesignerEditor;



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
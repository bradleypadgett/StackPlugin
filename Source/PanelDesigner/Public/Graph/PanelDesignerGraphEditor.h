#pragma once
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"



class UPanelDesignerGraph;

/*
* Slate widget that renders the editable graph itself
* Useful for Adding toolbars, dropdowns, or buttons above graph.
* Can swap between graph views/layouts
* Can control padding/layout
* 
* Can add runtime previews here
*/
class SPanelDesignerGraphEditor : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SPanelDesignerGraphEditor) : _GraphToEdit(nullptr) {} // Optional default
        SLATE_ARGUMENT(UPanelDesignerGraph*, GraphToEdit)
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

private:
    UPanelDesignerGraph* GraphBeingEdited;

    TSharedPtr<SGraphEditor> GraphEditor;

};

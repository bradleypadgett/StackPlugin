#pragma once
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"



class UUIBuilderGraph;

/*
* Slate widget that renders the editable graph itself
* Useful for Adding toolbars, dropdowns, or buttons above graph.
* Can swap between graph views/layouts
* Can control padding/layout
* 
* Can add runtime previews here
*/
class SUIBuilderGraphWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SUIBuilderGraphWidget) : _GraphToEdit(nullptr) {} // Optional default
        SLATE_ARGUMENT(UUIBuilderGraph*, GraphToEdit)
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

private:
    UUIBuilderGraph* GraphBeingEdited;

    TSharedPtr<SGraphEditor> GraphEditor;

};

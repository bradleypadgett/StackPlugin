#pragma once
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"



class UUIBuilderGraph;

/*
* Slate widget that renders the editable graph itself
*/
class SUIBuilderGraphEditor : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SUIBuilderGraphEditor) : _GraphToEdit(nullptr) {} // Optional default
        SLATE_ARGUMENT(UUIBuilderGraph*, GraphToEdit)
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

private:
    UUIBuilderGraph* GraphBeingEdited;

    TSharedPtr<SGraphEditor> GraphEditor;

};

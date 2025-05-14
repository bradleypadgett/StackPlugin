#pragma once
#include "WorkflowOrientedApp/ApplicationMode.h"



class FBlueprintEditor;

class FReplicatedBlueprintEditorMode : public FApplicationMode
{
public:

	FReplicatedBlueprintEditorMode(TSharedPtr<FBlueprintEditor> InEditor);

private:

	TWeakPtr<FBlueprintEditor> WeakEditor;

};

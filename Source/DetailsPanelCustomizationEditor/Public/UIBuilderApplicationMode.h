#pragma once
#include "CoreMinimal.h"
#include "WorkflowOrientedApp/ApplicationMode.h"

class FBlueprintEditor;
class FExtender;
class FTabManager;

class FUIBuilderApplicationMode : public FApplicationMode
{
public:
    FUIBuilderApplicationMode(TSharedPtr<FBlueprintEditor> InEditor);

    virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;
    virtual TSharedPtr<FExtender> GetToolBarExtender() const;

private:
    TWeakPtr<FBlueprintEditor> BlueprintEditor;
    TSharedPtr<FExtender> ToolbarExtender;
};

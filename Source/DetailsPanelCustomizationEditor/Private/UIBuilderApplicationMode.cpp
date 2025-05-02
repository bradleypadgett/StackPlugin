#include "UIBuilderApplicationMode.h"



FUIBuilderApplicationMode::FUIBuilderApplicationMode(TSharedPtr<FBlueprintEditor> InEditor) : FApplicationMode("UIBuilderDesigner"), BlueprintEditor(InEditor)
{
    ToolbarExtender = MakeShared<FExtender>();
    // Set up toolbar buttons here later
}

void FUIBuilderApplicationMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
    // Register tabs here (GraphTab, PreviewTab, etc.)
}

TSharedPtr<FExtender> FUIBuilderApplicationMode::GetToolBarExtender() const
{
    return ToolbarExtender;
}
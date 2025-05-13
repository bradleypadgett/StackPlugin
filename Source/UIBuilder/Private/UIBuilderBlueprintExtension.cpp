#include "UIBuilderBlueprintExtension.h"
#include "UIBuilderTabManager.h"
#include "Graph/UIBuilderGraph.h"
#include "EdGraph/EdGraph.h"
#include "EditorSubsystem.h"
#include "Subsystems/AssetEditorSubsystem.h"
#include "BlueprintEditor.h"
#include "GraphEditor.h"



void UUIBuilderBlueprintExtension::PostInitProperties()
{
    Super::PostInitProperties();

    OwningBlueprint = GetTypedOuter<UBlueprint>();
    if (OwningBlueprint)
    {
        EnsureUIBuilderGraph();
    }
}


// Creates and serializes UIBuilderGraph into owning blueprint if it doesn't have one
void UUIBuilderBlueprintExtension::EnsureUIBuilderGraph()
{
    if (UIBuilderGraph) return;

    for (UEdGraph* Graph : OwningBlueprint->FunctionGraphs)
    {
        if (UUIBuilderGraph* Found = Cast<UUIBuilderGraph>(Graph))
        {
            UIBuilderGraph = Found;
            return;
        }
    }

    UIBuilderGraph = NewObject<UUIBuilderGraph>(OwningBlueprint, TEXT("UIBuilderGraph"));
    OwningBlueprint->FunctionGraphs.Add(UIBuilderGraph);
    OwningBlueprint->Modify();
    
}

void UUIBuilderBlueprintExtension::SetCurrentMode(FName InMode)
{
    UE_LOG(LogTemp, Warning, TEXT("📣 SetCurrentMode called with: %s"), *InMode.ToString());
    if (CurrentMode != InMode)
    {
        FBlueprintEditor* Editor = static_cast<FBlueprintEditor*>(
            GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->FindEditorForAsset(OwningBlueprint, false));

        if (Editor) {
            CurrentMode = InMode;
            if (CurrentMode == "Designer")
            {
                FUIBuilderTabManager::HandleDesignerMode(Editor, this, CurrentMode);
            }
            else if (CurrentMode == "Graph")
            {
                FUIBuilderTabManager::HandleGraphMode(Editor, this, CurrentMode);
            }
        }
    }
}
